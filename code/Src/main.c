/*

 ******************************************************************************
 TODO: add license
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_hal.h"
#include "adc.h"
#include "gpio.h"
#include "pwm.h"
#include "encoder.h"
#include "motion_sensor.h"
#include "colorwheel.h"
#include "settings.h"
#include "rgb_led.h"
#include "light_sensor.h"

#define COLOR_HOLD_TIME				5000	/* time the light stays on (in ms) */
#define COLOR_FADE_TIME				3000	/* time the light takes to fade in and out (in ms) */
#define COLOR_FADE_FREQ				50		/* update rate when fading (in Hz) */

#define COLOR_FADE_STEP_DURATION 	(1000/COLOR_FADE_FREQ)
#define COLOR_FADE_MAX_STEPS 		(COLOR_FADE_TIME / COLOR_FADE_STEP_DURATION)

#define COLOR_SELECT_TIMEOUT				5000   /* timeout in color selection mode (when nothing is done, color resets to last values)*/
#define COLOR_SELECT_HUE_INCREMENT			5      /* the step size the hue changes when selecting the color by rotating the encoder */
#define COLOR_SELECT_BRIGHTNESS_INCREMENT	0.02   /* the step size the brightness changes when selecting the color by rotating the encoder */

/* type for states of state machine */
typedef enum {
    STATE_SLEEP = 0,
    STATE_WAKEUP = 1,
    STATE_COLOR_FADE_IN = 2,
    STATE_COLOR_HOLD = 3,
    STATE_COLOR_FADE_OUT = 4,
    STATE_COLOR_SET_HUE = 5,
    STATE_COLOR_SET_BRIGHTNESS = 6,
    STATE_COLOR_SAVE_VALUES = 7,
} state_t;

/* Private variables ---------------------------------------------------------*/

int8_t flag_encoder_rotation = 0; /* flag for encoder rotation (1=cw ; -1=ccw ; 0=nothing) */
uint8_t flag_encoder_button_pressed = 0; /* flag for encoder button press */
uint8_t flag_wakeup = 0; /* this flag will be set on motion detector interrupt */

state_t state = STATE_SLEEP;

uint32_t state_timeout_tick_start = 0;
uint32_t color_fade_current_step = 0;
uint32_t color_target_angle = 0;
float color_target_brightness = 0.0f;

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

void rotation_cb(uint8_t direction); /* callback for encoder rotation */
void button_cb(void); /* callback for button press */
void motion_cb(void); /* callback for motion detected */

int main(void) {

    /* MCU Configuration----------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* Configure the system clock */
    SystemClock_Config();

    settings_init();
    color_target_angle = config_bank.angle;
    color_target_brightness = config_bank.brightness;
    rgb_led_current_color.angle = 0; /* blue for tests */
    rgb_led_current_color.brightness = 0.0f;

    /* Initialize remaining gpio pins for lower power consumption */
    MX_GPIO_Init();

    /* init RGB LED strip */
    rgb_led_init();

    /* init rotary encoder */
    encoder_init();
    encoder_set_rotation_callback(rotation_cb);
    encoder_set_button_callback(button_cb);
    encoder_start();

    motion_sensor_init(motion_cb);

    light_sensor_init();

    /* Infinite loop */
    while (1) {

        /* enter state machine */
        switch (state) {
        case STATE_SLEEP:
        {
            /* wait for the flag set by interrupt
             * note: while loop is temporary, use __WFI in the future...
             */

            HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);

            state = STATE_WAKEUP;

            break;
        }

        case STATE_WAKEUP:
        {
            /*re-configure system clock since it was disabled in low-power mode */
            SystemClock_Config();

            /* only proceed if it is actually dark outside, otherwise stay in sleep mode */
            if ((flag_wakeup == 1) && (light_sensor_check_ambient_light() == 0)) {

                /* prepare fade in */
                rgb_led_current_color.angle = color_target_angle;
                state_timeout_tick_start = HAL_GetTick();
                color_fade_current_step = 0;
                state = STATE_COLOR_FADE_IN;
            }
            else {
                /* go back to sleep */
                state = STATE_SLEEP;
            }

            break;
        }

        case STATE_COLOR_FADE_IN:
        {
            if ((HAL_GetTick() - state_timeout_tick_start) >= COLOR_FADE_STEP_DURATION) {
                rgb_led_current_color.brightness = color_target_brightness
                        * (float) ((float) color_fade_current_step
                                / (float) COLOR_FADE_MAX_STEPS);
                rgb_led_update_color();
                color_fade_current_step++;
                state_timeout_tick_start = HAL_GetTick();
            }

            if (color_fade_current_step >= COLOR_FADE_MAX_STEPS) {
                /* fading finished */
                rgb_led_current_color.brightness = color_target_brightness;
                rgb_led_update_color();

                /* prepare hold */
                state_timeout_tick_start = HAL_GetTick();
                state = STATE_COLOR_HOLD;
            }

            break;
        }

        case STATE_COLOR_HOLD:
        {
            if ((HAL_GetTick() - state_timeout_tick_start) >= COLOR_HOLD_TIME) {
                /* prepare fade out */
                state_timeout_tick_start = HAL_GetTick();
                color_fade_current_step = COLOR_FADE_MAX_STEPS;
                state = STATE_COLOR_FADE_OUT;
            }
            break;
        }
        case STATE_COLOR_FADE_OUT:
        {
            if ((HAL_GetTick() - state_timeout_tick_start)
                    >= COLOR_FADE_STEP_DURATION) {
                rgb_led_current_color.brightness = color_target_brightness
                        * (float) ((float) color_fade_current_step / (float) COLOR_FADE_MAX_STEPS);
                rgb_led_update_color();
                color_fade_current_step--;
                state_timeout_tick_start = HAL_GetTick();
            }

            if (color_fade_current_step == 0) {
                /* fading finished */
                rgb_led_current_color.brightness = 0;
                rgb_led_update_color();
                state_timeout_tick_start = 0;
                state = STATE_SLEEP;
            }
            break;
        }
        case STATE_COLOR_SET_HUE:
        {
            if (flag_encoder_rotation == 1) {
                flag_encoder_rotation = 0;
                state_timeout_tick_start = HAL_GetTick();
                if (rgb_led_current_color.angle > 350) {
                    rgb_led_current_color.angle = 0;
                }
                rgb_led_current_color.angle += COLOR_SELECT_HUE_INCREMENT;
                rgb_led_update_color();
            }
            if (flag_encoder_rotation == -1) {
                flag_encoder_rotation = 0;
                state_timeout_tick_start = HAL_GetTick();
                if (rgb_led_current_color.angle < COLOR_SELECT_HUE_INCREMENT) {
                    rgb_led_current_color.angle = 360;
                }
                rgb_led_current_color.angle -= COLOR_SELECT_HUE_INCREMENT;
                rgb_led_update_color();
            }
            if (flag_encoder_button_pressed == 1) {
                flag_encoder_button_pressed = 0;
                state_timeout_tick_start = HAL_GetTick();
                state = STATE_COLOR_SET_BRIGHTNESS;

                /* blink once to signal confirmation */
                rgb_led_current_color.brightness = 0.0;
                rgb_led_update_color();
                HAL_Delay(100);
                rgb_led_current_color.brightness = color_target_brightness;
                rgb_led_update_color();
            }
            if ((HAL_GetTick() - state_timeout_tick_start)
                    >= COLOR_SELECT_TIMEOUT) {
                rgb_led_current_color.brightness = 0.0;
                rgb_led_update_color();
                state = STATE_SLEEP;
            }
            break;
        }
        case STATE_COLOR_SET_BRIGHTNESS:
        {
            if (flag_encoder_rotation == 1) {
                flag_encoder_rotation = 0;
                state_timeout_tick_start = HAL_GetTick();
                if (rgb_led_current_color.brightness >= 1.0f) {
                    rgb_led_current_color.brightness = 1.0f;
                }
                rgb_led_current_color.brightness +=
                COLOR_SELECT_BRIGHTNESS_INCREMENT;
                rgb_led_update_color();
            }
            if (flag_encoder_rotation == -1) {
                flag_encoder_rotation = 0;
                state_timeout_tick_start = HAL_GetTick();
                if (rgb_led_current_color.brightness
                        < COLOR_SELECT_BRIGHTNESS_INCREMENT) {
                    rgb_led_current_color.brightness = 0.0;
                }
                rgb_led_current_color.brightness -=
                COLOR_SELECT_BRIGHTNESS_INCREMENT;
                rgb_led_update_color();
            }
            if (flag_encoder_button_pressed == 1) {
                flag_encoder_button_pressed = 0;
                state = STATE_COLOR_SAVE_VALUES;
            }
            if ((HAL_GetTick() - state_timeout_tick_start)
                    >= COLOR_SELECT_TIMEOUT) {
                rgb_led_current_color.brightness = 0.0;
                rgb_led_update_color();
                state = STATE_SLEEP;
            }
            break;
            case STATE_COLOR_SAVE_VALUES:
            {
                color_target_angle = rgb_led_current_color.angle;
                color_target_brightness = rgb_led_current_color.brightness;

                /* save in EEPROM */
                config_bank.angle = color_target_angle;
                config_bank.brightness = color_target_brightness;
                settings_save();

                /* blink twice to signal confirmation */
                rgb_led_current_color.brightness = 0.0;
                rgb_led_update_color();
                HAL_Delay(100);
                rgb_led_current_color.brightness = color_target_brightness;
                rgb_led_update_color();
                HAL_Delay(150);
                rgb_led_current_color.brightness = 0.0;
                rgb_led_update_color();
                HAL_Delay(100);
                rgb_led_current_color.brightness = color_target_brightness;
                rgb_led_update_color();
                HAL_Delay(150);
                rgb_led_current_color.brightness = 0.0;
                rgb_led_update_color();

                state = STATE_SLEEP;
                break;
            }
        }
        default:
            state = STATE_SLEEP;
            break;
        }

        /* evaluate button press */
        if (flag_encoder_button_pressed == 1) {
            if ((state != STATE_COLOR_SET_HUE)
                    && (state != STATE_COLOR_SET_BRIGHTNESS)) {
                flag_encoder_button_pressed = 0;
                /* turn on LED and enter color selection mode */
                rgb_led_current_color.brightness = color_target_brightness;
                rgb_led_current_color.angle = color_target_angle;
                rgb_led_update_color();
                state_timeout_tick_start = HAL_GetTick();
                state = STATE_COLOR_SET_HUE;
            }

        }

    }

}

/** System Clock Configuration (generated by CubeMX)
 */
void SystemClock_Config(void) {

    RCC_OscInitTypeDef RCC_OscInitStruct;
    RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /* enable clock for PWR peripheral */
    __HAL_RCC_PWR_CLK_ENABLE();

    /**Configure the main internal regulator output voltage 
     */
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks 
     */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = 16;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL3;
    RCC_OscInitStruct.PLL.PLLDIV = RCC_PLL_DIV4;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    }

    /**Initializlight_sensores the CPU, AHB and APB busses clocks
     */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
            | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK) {
    }

    /**Configure the Systick interrupt time 
     */
    HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);

    /**Configure the Systick 
     */
    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

    /* SysTick_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

void rotation_cb(uint8_t direction) {
    if (direction) {
        flag_encoder_rotation = 1;
    }
    else {
        flag_encoder_rotation = -1;
    }
}

void button_cb(void) {
    flag_encoder_button_pressed = 1;
}

void motion_cb(void) {
    flag_wakeup = 1;
}

/* Interrupt callback for GPIO interrupts */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    if (GPIO_Pin == ENCODER_BTN_PIN) {
        encoder_button_interrupt_handler();
    }

    if (GPIO_Pin == MOTION_SENSOR_GPIO_PIN) {
        motion_sensor_interrupt_handler();
    }
}
