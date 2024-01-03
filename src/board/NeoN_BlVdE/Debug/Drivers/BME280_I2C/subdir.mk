################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BME280_I2C/bme280.c \
../Drivers/BME280_I2C/its_bme280.c 

OBJS += \
./Drivers/BME280_I2C/bme280.o \
./Drivers/BME280_I2C/its_bme280.o 

C_DEPS += \
./Drivers/BME280_I2C/bme280.d \
./Drivers/BME280_I2C/its_bme280.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BME280_I2C/%.o: ../Drivers/BME280_I2C/%.c Drivers/BME280_I2C/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/NeonBlade(Git)/src/lib-tsniimash/stm32f4" -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BME280_I2C

clean-Drivers-2f-BME280_I2C:
	-$(RM) ./Drivers/BME280_I2C/bme280.d ./Drivers/BME280_I2C/bme280.o ./Drivers/BME280_I2C/its_bme280.d ./Drivers/BME280_I2C/its_bme280.o

.PHONY: clean-Drivers-2f-BME280_I2C

