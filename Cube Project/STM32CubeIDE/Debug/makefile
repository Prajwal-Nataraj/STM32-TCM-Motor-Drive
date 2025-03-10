################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Middlewares/MotorControl/subdir.mk
-include Drivers/STM32G4xx_HAL_Driver/subdir.mk
-include Drivers/CMSIS/subdir.mk
-include Application/User/subdir.mk
-include Application/Startup/subdir.mk
-include subdir.mk
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

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
TCM\ PI\ Tuning.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
TCM\ PI\ Tuning.list \

OBJCOPY_BIN += \
TCM\ PI\ Tuning.bin \


# All Target
all: TCM\ PI\ Tuning.elf secondary-outputs

# Tool invocations
TCM\ PI\ Tuning.elf: $(OBJS) $(USER_OBJS) C:\Users\PNataraj.AMETEK-AD\OneDrive\ -\ AMETEK\ Inc\Original\ Files\GitKraken\TCM\ PI\ Tuning\Cube\ Project\STM32CubeIDE\STM32G474RETX_FLASH.ld
	arm-none-eabi-gcc -o "TCM PI Tuning.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\PNataraj.AMETEK-AD\OneDrive - AMETEK Inc\Original Files\GitKraken\TCM PI Tuning\Cube Project\STM32CubeIDE\STM32G474RETX_FLASH.ld" --specs=nosys.specs -Wl,-Map="TCM PI Tuning.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -u _printf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

TCM\ PI\ Tuning.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "TCM PI Tuning.list"
	@echo 'Finished building: $@'
	@echo ' '

TCM\ PI\ Tuning.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "TCM PI Tuning.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
