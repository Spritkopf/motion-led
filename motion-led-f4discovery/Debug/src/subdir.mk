################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/main.c 

OBJS += \
./src/main.o 

C_DEPS += \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mlittle-endian -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -D_RTE_ -DSTM32F407xx -I"D:/STM32_FW_Packs/CMSIS_Eclipse/ARM/CMSIS/5.0.1/CMSIS/Include" -I"D:\temp\porjec\motion-led-f4discovery\inc" -I"D:/STM32_FW_Packs/CMSIS_Eclipse/Keil/STM32F4xx_DFP/2.11.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/STM32_FW_Packs/CMSIS_Eclipse/Keil/STM32F4xx_DFP/2.11.0/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/STM32_FW_Packs/CMSIS_Eclipse/Keil/STM32F4xx_DFP/2.11.0/MDK/Templates/Inc" -I"D:\temp\porjec\motion-led-f4discovery/RTE" -I"D:\temp\porjec\motion-led-f4discovery/RTE/Device/STM32F407VGTx" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


