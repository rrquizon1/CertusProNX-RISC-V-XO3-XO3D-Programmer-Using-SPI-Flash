################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/bsp/driver/uart/subdir.mk
-include src/bsp/driver/spi_controller/subdir.mk
-include src/bsp/driver/riscv_mc/subdir.mk
-include src/bsp/driver/i2c_controller/subdir.mk
-include src/bsp/driver/gpio/subdir.mk
-include src/bsp/subdir.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
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


BUILD_ARTIFACT_NAME := I2C_SPI_GPIO
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_LIST += \
I2C_SPI_GPIO.lst \

SECONDARY_SIZE += \
I2C_SPI_GPIO.siz \

SECONDARY_MEMORY += \
I2C_SPI_GPIO.mem \


# All Target
all: main-build

# Main-build Target
main-build: I2C_SPI_GPIO.elf secondary-outputs

# Tool invocations
I2C_SPI_GPIO.elf: $(OBJS) $(USER_OBJS) makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU RISC-V Cross C Linker'
	riscv-none-embed-gcc -march=rv32imc -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -T "D:/Propel_Study/I2C_SPI_Programming_singlecore/Workspace/I2C_SPI_GPIO/src/linker.ld" -nostartfiles -Xlinker --gc-sections -Wl,-Map,"I2C_SPI_GPIO.map" --specs=picolibc.specs -DPICOLIBC_INTEGER_PRINTF_SCANF -o "I2C_SPI_GPIO.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

I2C_SPI_GPIO.lst: I2C_SPI_GPIO.elf makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Invoking: GNU RISC-V Cross Create Listing'
	riscv-none-embed-objdump --source --all-headers --demangle --line-numbers --wide "I2C_SPI_GPIO.elf" > "I2C_SPI_GPIO.lst"
	@echo 'Finished building: $@'
	@echo ' '

I2C_SPI_GPIO.siz: I2C_SPI_GPIO.elf makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Invoking: GNU RISC-V Cross Print Size'
	riscv-none-embed-size --format=berkeley "I2C_SPI_GPIO.elf"
	@echo 'Finished building: $@'
	@echo ' '

I2C_SPI_GPIO.mem: I2C_SPI_GPIO.elf makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Invoking: Lattice Create Memory Deployment'
	riscv-none-embed-objcopy -O binary --gap-fill 0 "I2C_SPI_GPIO.elf" "I2C_SPI_GPIO.bin"; srec_cat "I2C_SPI_GPIO.bin" -Binary -byte-swap 4 -DISable Header -Output "I2C_SPI_GPIO.mem" -MEM 32
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(SECONDARY_MEMORY)$(OBJS)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS) I2C_SPI_GPIO.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_LIST) $(SECONDARY_SIZE) $(SECONDARY_MEMORY)

.PHONY: all clean dependents main-build

-include ../makefile.targets
