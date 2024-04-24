################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include stm32f4/stm32f4/nRF24L01_PL/src/subdir.mk
-include stm32f4/stm32f4/Shift_Register/src/subdir.mk
-include stm32f4/stm32f4/Photorezistor/src/subdir.mk
-include stm32f4/stm32f4/LSM6DS3/src/subdir.mk
-include stm32f4/stm32f4/LIS3MDL/src/subdir.mk
-include stm32f4/stm32f4/DWT_Delay/src/subdir.mk
-include stm32f4/stm32f4/ATGM336H/src/subdir.mk
-include stm32f4/stm32f4/ATGM336H/minmea/subdir.mk
-include stm32f4/stm32f4/AD5593/subdir.mk
-include TDC-GP21/TDC21_UPPER_API/subdir.mk
-include TDC-GP21/TDC21_LOVVER_API/subdir.mk
-include Middlewares/Third_Party/FatFs/src/option/subdir.mk
-include Middlewares/Third_Party/FatFs/src/subdir.mk
-include FATFS/Target/subdir.mk
-include FATFS/App/subdir.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include Drivers/I2C_crutch/subdir.mk
-include Drivers/BME280_I2C/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include Application/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := NeoN_BlVdE
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
NeoN_BlVdE.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
NeoN_BlVdE.list \

OBJCOPY_BIN += \
NeoN_BlVdE.bin \


# All Target
all: main-build

# Main-build Target
main-build: NeoN_BlVdE.elf secondary-outputs

# Tool invocations
NeoN_BlVdE.elf: $(OBJS) $(USER_OBJS) C:\huinya\NeoN_BlVdE\NeonBlade-2024\src\board\NeoN_BlVdE\STM32F411CEUX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "NeoN_BlVdE.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\huinya\NeoN_BlVdE\NeonBlade-2024\src\board\NeoN_BlVdE\STM32F411CEUX_FLASH.ld" --specs=nosys.specs -Wl,-Map="NeoN_BlVdE.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -u _printf_float -u _scanf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

NeoN_BlVdE.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "NeoN_BlVdE.list"
	@echo 'Finished building: $@'
	@echo ' '

NeoN_BlVdE.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "NeoN_BlVdE.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) NeoN_BlVdE.bin NeoN_BlVdE.elf NeoN_BlVdE.list default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
