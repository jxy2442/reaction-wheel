################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Lib/sched/badsched.c 

OBJS += \
./Core/Lib/sched/badsched.o 

C_DEPS += \
./Core/Lib/sched/badsched.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Lib/sched/%.o Core/Lib/sched/%.su: ../Core/Lib/sched/%.c Core/Lib/sched/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Lib-2f-sched

clean-Core-2f-Lib-2f-sched:
	-$(RM) ./Core/Lib/sched/badsched.d ./Core/Lib/sched/badsched.o ./Core/Lib/sched/badsched.su

.PHONY: clean-Core-2f-Lib-2f-sched

