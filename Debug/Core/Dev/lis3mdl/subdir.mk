################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Dev/lis3mdl/lis3mdl_reg.c \
../Core/Dev/lis3mdl/mag.c 

OBJS += \
./Core/Dev/lis3mdl/lis3mdl_reg.o \
./Core/Dev/lis3mdl/mag.o 

C_DEPS += \
./Core/Dev/lis3mdl/lis3mdl_reg.d \
./Core/Dev/lis3mdl/mag.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Dev/lis3mdl/%.o Core/Dev/lis3mdl/%.su: ../Core/Dev/lis3mdl/%.c Core/Dev/lis3mdl/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Dev-2f-lis3mdl

clean-Core-2f-Dev-2f-lis3mdl:
	-$(RM) ./Core/Dev/lis3mdl/lis3mdl_reg.d ./Core/Dev/lis3mdl/lis3mdl_reg.o ./Core/Dev/lis3mdl/lis3mdl_reg.su ./Core/Dev/lis3mdl/mag.d ./Core/Dev/lis3mdl/mag.o ./Core/Dev/lis3mdl/mag.su

.PHONY: clean-Core-2f-Dev-2f-lis3mdl

