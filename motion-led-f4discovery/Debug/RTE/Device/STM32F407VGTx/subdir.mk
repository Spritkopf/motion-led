################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/STM32_FW_Packs/CMSIS_Eclipse/Keil/STM32F4xx_DFP/2.11.0/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c \
D:/STM32_FW_Packs/CMSIS_Eclipse/Keil/STM32F4xx_DFP/2.11.0/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c \
D:/STM32_FW_Packs/CMSIS_Eclipse/Keil/STM32F4xx_DFP/2.11.0/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c \
D:/STM32_FW_Packs/CMSIS_Eclipse/Keil/STM32F4xx_DFP/2.11.0/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.c \
D:/STM32_FW_Packs/CMSIS_Eclipse/Keil/STM32F4xx_DFP/2.11.0/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c \
D:/STM32_FW_Packs/CMSIS_Eclipse/Keil/STM32F4xx_DFP/2.11.0/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c \
D:/STM32_FW_Packs/CMSIS_Eclipse/Keil/STM32F4xx_DFP/2.11.0/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c \
D:/STM32_FW_Packs/CMSIS_Eclipse/Keil/STM32F4xx_DFP/2.11.0/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c \
D:/STM32_FW_Packs/CMSIS_Eclipse/Keil/STM32F4xx_DFP/2.11.0/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c \
D:/STM32_FW_Packs/CMSIS_Eclipse/Keil/STM32F4xx_DFP/2.11.0/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.c \
D:/STM32_FW_Packs/CMSIS_Eclipse/Keil/STM32F4xx_DFP/2.11.0/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.c \
../RTE/Device/STM32F407VGTx/system_stm32f4xx.c 

S_UPPER_SRCS += \
../RTE/Device/STM32F407VGTx/startup_stm32f407xx.S 

OBJS += \
./RTE/Device/STM32F407VGTx/startup_stm32f407xx.o \
./RTE/Device/STM32F407VGTx/stm32f4xx_hal.o \
./RTE/Device/STM32F407VGTx/stm32f4xx_hal_cortex.o \
./RTE/Device/STM32F407VGTx/stm32f4xx_hal_dma.o \
./RTE/Device/STM32F407VGTx/stm32f4xx_hal_dma_ex.o \
./RTE/Device/STM32F407VGTx/stm32f4xx_hal_gpio.o \
./RTE/Device/STM32F407VGTx/stm32f4xx_hal_pwr.o \
./RTE/Device/STM32F407VGTx/stm32f4xx_hal_pwr_ex.o \
./RTE/Device/STM32F407VGTx/stm32f4xx_hal_rcc.o \
./RTE/Device/STM32F407VGTx/stm32f4xx_hal_rcc_ex.o \
./RTE/Device/STM32F407VGTx/stm32f4xx_hal_tim.o \
./RTE/Device/STM32F407VGTx/stm32f4xx_hal_tim_ex.o \
./RTE/Device/STM32F407VGTx/system_stm32f4xx.o 

S_UPPER_DEPS += \
./RTE/Device/STM32F407VGTx/startup_stm32f407xx.d 

C_DEPS += \
./RTE/Device/STM32F407VGTx/stm32f4xx_hal.d \
./RTE/Device/STM32F407VGTx/stm32f4xx_hal_cortex.d \
./RTE/Device/STM32F407VGTx/stm32f4xx_hal_dma.d \
./RTE/Device/STM32F407VGTx/stm32f4xx_hal_dma_ex.d \
./RTE/Device/STM32F407VGTx/stm32f4xx_hal_gpio.d \
./RTE/Device/STM32F407VGTx/stm32f4xx_hal_pwr.d \
./RTE/Device/STM32F407VGTx/stm32f4xx_hal_pwr_ex.d \
./RTE/Device/STM32F407VGTx/stm32f4xx_hal_rcc.d \
./RTE/Device/STM32F407VGTx/stm32f4xx_hal_rcc_ex.d \
./RTE/Device/STM32F407VGTx/stm32f4xx_hal_tim.d \
./RTE/Device/STM32F407VGTx/stm32f4xx_hal_tim_ex.d \
./RTE/Device/STM32F407VGTx/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
RTE/Device/STM32F407VGTx/%.o: ../RTE/Device/STM32F407VGTx/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU Assembler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mlittle-endian -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -x assembler-with-cpp -D_RTE_ -DSTM32F407xx -I"D:/STM32_FW_Packs/CMSIS_Eclipse/ARM/CMSIS/5.0.1/CMSIS/Include" -I"D:/STM32_FW_Packs/CMSIS_Eclipse/Keil/STM32F4xx_DFP/2.11.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/STM32_FW_Packs/CMSIS_Eclipse/Keil/STM32F4xx_DFP/2.11.0/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/STM32_FW_Packs/CMSIS_Eclipse/Keil/STM32F4xx_DFP/2.11.0/MDK/Templates/Inc" -I"D:\temp\porjec\motion-led-f4discovery/RTE" -I"D:\temp\porjec\motion-led-f4discovery/RTE/Device/STM32F407VGTx" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

RTE/Device/STM32F407VGTx/stm32f4xx_hal.o: D:/STM32_FW_Packs/CMSIS_Eclipse/Keil/STM32F4xx_DFP/2.11.0/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mlittle-endian -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -D_RTE_ -DSTM32F407xx -I"D:/STM32_FW_Packs/CMSIS_Eclipse/ARM/CMSIS/5.0.1/CMSIS/Include" -I"D:\temp\porjec\motion-led-f4discovery\inc" -I"D:/STM32_FW_Packs/CMSIS_Eclipse/Keil/STM32F4xx_DFP/2.11.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/STM32_FW_Packs/CMSIS_Eclipse/Keil/STM32F4xx_DFP/2.11.0/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/STM32_FW_Packs/CMSIS_Eclipse/Keil/STM32F4xx_DFP/2.11.0/MDK/Templates/Inc" -I"D:\temp\porjec\motion-led-f4discovery/RTE" -I"D:\temp\porjec\motion-led-f4discovery/RTE/Device/STM32F407VGTx" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

RTE/Device/STM32F407VGTx/stm32f4xx_hal_cortex.o: D:/STM32_FW_Packs/CMSIS_Eclipse/Keil/STM32F4xx_DFP/2.11.0/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mlittle-endian -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -D_RTE_ -DSTM32F407xx -I"D:/STM32_FW_Packs/CMSIS_Eclipse/ARM/CMSIS/5.0.1/CMSIS/Include" -I"D:\temp\porjec\motion-led-f4discovery\inc" -I"D:/STM32_FW_Packs/CMSIS_Eclipse/Keil/STM32F4xx_DFP/2.11.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/STM32_FW_Packs/CMSIS_Eclipse/Keil/STM32F4xx_DFP/2.11.0/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/STM32_FW_Packs/CMSIS_Eclipse/Keil/STM32F4xx_DFP/2.11.0/MDK/Templates/Inc" -I"D:\temp\porjec\motion-led-f4discovery/RTE" -I"D:\temp\porjec\motion-led-f4discovery/RTE/Device/STM32F407VGTx" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

RTE/Device/STM32F407VGTx/stm32f4xx_hal_dma.o: D:/STM32_FW_Packs/CMSIS_Eclipse/Keil/STM32F4xx_DFP/2.11.0/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mlittle-endian -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -D_RTE_ -DSTM32F407xx -I"D:/STM32_FW_Packs/CMSIS_Eclipse/ARM/CMSIS/5.0.1/CMSIS/Include" -I"D:\temp\porjec\motion-led-f4discovery\inc" -I"D:/STM32_FW_Packs/CMSIS_Eclipse/Keil/STM32F4xx_DFP/2.11.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/STM32_FW_Packs/CMSIS_Eclipse/Keil/STM32F4xx_DFP/2.11.0/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/STM32_FW_Packs/CMSIS_Eclipse/Keil/STM32F4xx_DFP/2.11.0/MDK/Templates/Inc" -I"D:\temp\porjec\motion-led-f4discovery/RTE" -I"D:\temp\porjec\motion-led-f4discovery/RTE/Device/STM32F407VGTx" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

RTE/Device/STM32F407VGTx/stm32f4xx_hal_dma_ex.o: D:/STM32_FW_Packs/CMSIS_Eclipse/Keil/STM32F4xx_DFP/2.11.0/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mlittle-endian -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -D_RTE_ -DSTM32F407xx -I"D:/STM32_FW_Packs/CMSIS_Eclipse/ARM/CMSIS/5.0.1/CMSIS/Include" -I"D:\temp\porjec\motion-led-f4discovery\inc" -I"D:/STM32_FW_Packs/CMSIS_Eclipse/Keil/STM32F4xx_DFP/2.11.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/STM32_FW_Packs/CMSIS_Eclipse/Keil/STM32F4xx_DFP/2.11.0/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/STM32_FW_Packs/CMSIS_Eclipse/Keil/STM32F4xx_DFP/2.11.0/MDK/Templates/Inc" -I"D:\temp\porjec\motion-led-f4discovery/RTE" -I"D:\temp\porjec\motion-led-f4discovery/RTE/Device/STM32F407VGTx" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

RTE/Device/STM32F407VGTx/stm32f4xx_hal_gpio.o: D:/STM32_FW_Packs/CMSIS_Eclipse/Keil/STM32F4xx_DFP/2.11.0/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mlittle-endian -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -D_RTE_ -DSTM32F407xx -I"D:/STM32_FW_Packs/CMSIS_Eclipse/ARM/CMSIS/5.0.1/CMSIS/Include" -I"D:\temp\porjec\motion-led-f4discovery\inc" -I"D:/STM32_FW_Packs/CMSIS_Eclipse/Keil/STM32F4xx_DFP/2.11.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/STM32_FW_Packs/CMSIS_Eclipse/Keil/STM32F4xx_DFP/2.11.0/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/STM32_FW_Packs/CMSIS_Eclipse/Keil/STM32F4xx_DFP/2.11.0/MDK/Templates/Inc" -I"D:\temp\porjec\motion-led-f4discovery/RTE" -I"D:\temp\porjec\motion-led-f4discovery/RTE/Device/STM32F407VGTx" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

RTE/Device/STM32F407VGTx/stm32f4xx_hal_pwr.o: D:/STM32_FW_Packs/CMSIS_Eclipse/Keil/STM32F4xx_DFP/2.11.0/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mlittle-endian -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -D_RTE_ -DSTM32F407xx -I"D:/STM32_FW_Packs/CMSIS_Eclipse/ARM/CMSIS/5.0.1/CMSIS/Include" -I"D:\temp\porjec\motion-led-f4discovery\inc" -I"D:/STM32_FW_Packs/CMSIS_Eclipse/Keil/STM32F4xx_DFP/2.11.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/STM32_FW_Packs/CMSIS_Eclipse/Keil/STM32F4xx_DFP/2.11.0/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/STM32_FW_Packs/CMSIS_Eclipse/Keil/STM32F4xx_DFP/2.11.0/MDK/Templates/Inc" -I"D:\temp\porjec\motion-led-f4discovery/RTE" -I"D:\temp\porjec\motion-led-f4discovery/RTE/Device/STM32F407VGTx" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

RTE/Device/STM32F407VGTx/stm32f4xx_hal_pwr_ex.o: D:/STM32_FW_Packs/CMSIS_Eclipse/Keil/STM32F4xx_DFP/2.11.0/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mlittle-endian -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -D_RTE_ -DSTM32F407xx -I"D:/STM32_FW_Packs/CMSIS_Eclipse/ARM/CMSIS/5.0.1/CMSIS/Include" -I"D:\temp\porjec\motion-led-f4discovery\inc" -I"D:/STM32_FW_Packs/CMSIS_Eclipse/Keil/STM32F4xx_DFP/2.11.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/STM32_FW_Packs/CMSIS_Eclipse/Keil/STM32F4xx_DFP/2.11.0/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/STM32_FW_Packs/CMSIS_Eclipse/Keil/STM32F4xx_DFP/2.11.0/MDK/Templates/Inc" -I"D:\temp\porjec\motion-led-f4discovery/RTE" -I"D:\temp\porjec\motion-led-f4discovery/RTE/Device/STM32F407VGTx" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

RTE/Device/STM32F407VGTx/stm32f4xx_hal_rcc.o: D:/STM32_FW_Packs/CMSIS_Eclipse/Keil/STM32F4xx_DFP/2.11.0/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mlittle-endian -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -D_RTE_ -DSTM32F407xx -I"D:/STM32_FW_Packs/CMSIS_Eclipse/ARM/CMSIS/5.0.1/CMSIS/Include" -I"D:\temp\porjec\motion-led-f4discovery\inc" -I"D:/STM32_FW_Packs/CMSIS_Eclipse/Keil/STM32F4xx_DFP/2.11.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/STM32_FW_Packs/CMSIS_Eclipse/Keil/STM32F4xx_DFP/2.11.0/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/STM32_FW_Packs/CMSIS_Eclipse/Keil/STM32F4xx_DFP/2.11.0/MDK/Templates/Inc" -I"D:\temp\porjec\motion-led-f4discovery/RTE" -I"D:\temp\porjec\motion-led-f4discovery/RTE/Device/STM32F407VGTx" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

RTE/Device/STM32F407VGTx/stm32f4xx_hal_rcc_ex.o: D:/STM32_FW_Packs/CMSIS_Eclipse/Keil/STM32F4xx_DFP/2.11.0/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mlittle-endian -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -D_RTE_ -DSTM32F407xx -I"D:/STM32_FW_Packs/CMSIS_Eclipse/ARM/CMSIS/5.0.1/CMSIS/Include" -I"D:\temp\porjec\motion-led-f4discovery\inc" -I"D:/STM32_FW_Packs/CMSIS_Eclipse/Keil/STM32F4xx_DFP/2.11.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/STM32_FW_Packs/CMSIS_Eclipse/Keil/STM32F4xx_DFP/2.11.0/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/STM32_FW_Packs/CMSIS_Eclipse/Keil/STM32F4xx_DFP/2.11.0/MDK/Templates/Inc" -I"D:\temp\porjec\motion-led-f4discovery/RTE" -I"D:\temp\porjec\motion-led-f4discovery/RTE/Device/STM32F407VGTx" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

RTE/Device/STM32F407VGTx/stm32f4xx_hal_tim.o: D:/STM32_FW_Packs/CMSIS_Eclipse/Keil/STM32F4xx_DFP/2.11.0/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mlittle-endian -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -D_RTE_ -DSTM32F407xx -I"D:/STM32_FW_Packs/CMSIS_Eclipse/ARM/CMSIS/5.0.1/CMSIS/Include" -I"D:\temp\porjec\motion-led-f4discovery\inc" -I"D:/STM32_FW_Packs/CMSIS_Eclipse/Keil/STM32F4xx_DFP/2.11.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/STM32_FW_Packs/CMSIS_Eclipse/Keil/STM32F4xx_DFP/2.11.0/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/STM32_FW_Packs/CMSIS_Eclipse/Keil/STM32F4xx_DFP/2.11.0/MDK/Templates/Inc" -I"D:\temp\porjec\motion-led-f4discovery/RTE" -I"D:\temp\porjec\motion-led-f4discovery/RTE/Device/STM32F407VGTx" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

RTE/Device/STM32F407VGTx/stm32f4xx_hal_tim_ex.o: D:/STM32_FW_Packs/CMSIS_Eclipse/Keil/STM32F4xx_DFP/2.11.0/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mlittle-endian -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -D_RTE_ -DSTM32F407xx -I"D:/STM32_FW_Packs/CMSIS_Eclipse/ARM/CMSIS/5.0.1/CMSIS/Include" -I"D:\temp\porjec\motion-led-f4discovery\inc" -I"D:/STM32_FW_Packs/CMSIS_Eclipse/Keil/STM32F4xx_DFP/2.11.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/STM32_FW_Packs/CMSIS_Eclipse/Keil/STM32F4xx_DFP/2.11.0/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/STM32_FW_Packs/CMSIS_Eclipse/Keil/STM32F4xx_DFP/2.11.0/MDK/Templates/Inc" -I"D:\temp\porjec\motion-led-f4discovery/RTE" -I"D:\temp\porjec\motion-led-f4discovery/RTE/Device/STM32F407VGTx" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

RTE/Device/STM32F407VGTx/%.o: ../RTE/Device/STM32F407VGTx/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mlittle-endian -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -D_RTE_ -DSTM32F407xx -I"D:/STM32_FW_Packs/CMSIS_Eclipse/ARM/CMSIS/5.0.1/CMSIS/Include" -I"D:\temp\porjec\motion-led-f4discovery\inc" -I"D:/STM32_FW_Packs/CMSIS_Eclipse/Keil/STM32F4xx_DFP/2.11.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/STM32_FW_Packs/CMSIS_Eclipse/Keil/STM32F4xx_DFP/2.11.0/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/STM32_FW_Packs/CMSIS_Eclipse/Keil/STM32F4xx_DFP/2.11.0/MDK/Templates/Inc" -I"D:\temp\porjec\motion-led-f4discovery/RTE" -I"D:\temp\porjec\motion-led-f4discovery/RTE/Device/STM32F407VGTx" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


