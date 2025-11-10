################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/UI/UI_SetTime.c 

OBJS += \
./Core/Src/UI/UI_SetTime.o 

C_DEPS += \
./Core/Src/UI/UI_SetTime.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/UI/%.o Core/Src/UI/%.su Core/Src/UI/%.cyclo: ../Core/Src/UI/%.c Core/Src/UI/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103x6 -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-UI

clean-Core-2f-Src-2f-UI:
	-$(RM) ./Core/Src/UI/UI_SetTime.cyclo ./Core/Src/UI/UI_SetTime.d ./Core/Src/UI/UI_SetTime.o ./Core/Src/UI/UI_SetTime.su

.PHONY: clean-Core-2f-Src-2f-UI

