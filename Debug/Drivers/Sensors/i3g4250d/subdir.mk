################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Sensors/i3g4250d/gyro.c \
../Drivers/Sensors/i3g4250d/i3g4250d_reg.c 

OBJS += \
./Drivers/Sensors/i3g4250d/gyro.o \
./Drivers/Sensors/i3g4250d/i3g4250d_reg.o 

C_DEPS += \
./Drivers/Sensors/i3g4250d/gyro.d \
./Drivers/Sensors/i3g4250d/i3g4250d_reg.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Sensors/i3g4250d/%.o Drivers/Sensors/i3g4250d/%.su: ../Drivers/Sensors/i3g4250d/%.c Drivers/Sensors/i3g4250d/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I"C:/Users/yevge/STM32CubeIDE/workspace_1.10.1/reaction-wheel/Drivers/Sensors" -I"C:/Users/yevge/STM32CubeIDE/workspace_1.10.1/reaction-wheel/Core/Lib" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-Sensors-2f-i3g4250d

clean-Drivers-2f-Sensors-2f-i3g4250d:
	-$(RM) ./Drivers/Sensors/i3g4250d/gyro.d ./Drivers/Sensors/i3g4250d/gyro.o ./Drivers/Sensors/i3g4250d/gyro.su ./Drivers/Sensors/i3g4250d/i3g4250d_reg.d ./Drivers/Sensors/i3g4250d/i3g4250d_reg.o ./Drivers/Sensors/i3g4250d/i3g4250d_reg.su

.PHONY: clean-Drivers-2f-Sensors-2f-i3g4250d

