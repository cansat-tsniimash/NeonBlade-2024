################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/I2C_crutch/i2c-crutch.c 

OBJS += \
./Drivers/I2C_crutch/i2c-crutch.o 

C_DEPS += \
./Drivers/I2C_crutch/i2c-crutch.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/I2C_crutch/%.o: ../Drivers/I2C_crutch/%.c Drivers/I2C_crutch/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/huinya/NeoN_BlVdE/lib-tsniimash-master" -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-I2C_crutch

clean-Drivers-2f-I2C_crutch:
	-$(RM) ./Drivers/I2C_crutch/i2c-crutch.d ./Drivers/I2C_crutch/i2c-crutch.o

.PHONY: clean-Drivers-2f-I2C_crutch

