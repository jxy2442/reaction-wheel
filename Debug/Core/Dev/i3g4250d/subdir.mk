################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Dev/i3g4250d/gyro.c \
../Core/Dev/i3g4250d/i3g4250d_reg.c 

OBJS += \
./Core/Dev/i3g4250d/gyro.o \
./Core/Dev/i3g4250d/i3g4250d_reg.o 

C_DEPS += \
./Core/Dev/i3g4250d/gyro.d \
./Core/Dev/i3g4250d/i3g4250d_reg.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Dev/i3g4250d/%.o Core/Dev/i3g4250d/%.su: ../Core/Dev/i3g4250d/%.c Core/Dev/i3g4250d/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Dev-2f-i3g4250d

clean-Core-2f-Dev-2f-i3g4250d:
	-$(RM) ./Core/Dev/i3g4250d/gyro.d ./Core/Dev/i3g4250d/gyro.o ./Core/Dev/i3g4250d/gyro.su ./Core/Dev/i3g4250d/i3g4250d_reg.d ./Core/Dev/i3g4250d/i3g4250d_reg.o ./Core/Dev/i3g4250d/i3g4250d_reg.su

.PHONY: clean-Core-2f-Dev-2f-i3g4250d

