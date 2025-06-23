################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/bsp/reg_test.c 

OBJS += \
./src/bsp/reg_test.o 

C_DEPS += \
./src/bsp/reg_test.d 


# Each subdirectory must supply rules for building sources it contributes
src/bsp/%.o: ../src/bsp/%.c src/bsp/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imc -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -DLSCC_STDIO_UART_APB -I"D:\Propel_Study\I2C_SPI_Programming_singlecore\Workspace\I2C_SPI_GPIO/src" -I"D:\Propel_Study\I2C_SPI_Programming_singlecore\Workspace\I2C_SPI_GPIO/src/bsp" -I"D:\Propel_Study\I2C_SPI_Programming_singlecore\Workspace\I2C_SPI_GPIO/src/bsp/driver" -I"D:\Propel_Study\I2C_SPI_Programming_singlecore\Workspace\I2C_SPI_GPIO/src/bsp/driver/gpio" -I"D:\Propel_Study\I2C_SPI_Programming_singlecore\Workspace\I2C_SPI_GPIO/src/bsp/driver/i2c_controller" -I"D:\Propel_Study\I2C_SPI_Programming_singlecore\Workspace\I2C_SPI_GPIO/src/bsp/driver/riscv_mc" -I"D:\Propel_Study\I2C_SPI_Programming_singlecore\Workspace\I2C_SPI_GPIO/src/bsp/driver/spi_controller" -I"D:\Propel_Study\I2C_SPI_Programming_singlecore\Workspace\I2C_SPI_GPIO/src/bsp/driver/uart" -std=gnu11 --specs=picolibc.specs -DPICOLIBC_INTEGER_PRINTF_SCANF -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


