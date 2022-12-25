################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Sensors/lis3mdl/lis3mdl_reg.c \
../Drivers/Sensors/lis3mdl/mag.c 

OBJS += \
./Drivers/Sensors/lis3mdl/lis3mdl_reg.o \
./Drivers/Sensors/lis3mdl/mag.o 

C_DEPS += \
./Drivers/Sensors/lis3mdl/lis3mdl_reg.d \
./Drivers/Sensors/lis3mdl/mag.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Sensors/lis3mdl/%.o Drivers/Sensors/lis3mdl/%.su: ../Drivers/Sensors/lis3mdl/%.c Drivers/Sensors/lis3mdl/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I"C:/Users/yevge/STM32CubeIDE/workspace_1.10.1/reaction-wheel/Drivers/Sensors" -I"C:/Users/yevge/STM32CubeIDE/workspace_1.10.1/reaction-wheel/Core/Lib" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-Sensors-2f-lis3mdl

clean-Drivers-2f-Sensors-2f-lis3mdl:
	-$(RM) ./Drivers/Sensors/lis3mdl/lis3mdl_reg.d ./Drivers/Sensors/lis3mdl/lis3mdl_reg.o ./Drivers/Sensors/lis3mdl/lis3mdl_reg.su ./Drivers/Sensors/lis3mdl/mag.d ./Drivers/Sensors/lis3mdl/mag.o ./Drivers/Sensors/lis3mdl/mag.su

.PHONY: clean-Drivers-2f-Sensors-2f-lis3mdl

