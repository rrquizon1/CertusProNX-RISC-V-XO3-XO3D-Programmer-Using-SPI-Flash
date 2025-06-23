################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/data.c \
../src/i2c_program.c \
../src/main.c \
../src/utils.c 

OBJS += \
./src/data.o \
./src/i2c_program.o \
./src/main.o \
./src/utils.o 

C_DEPS += \
./src/data.d \
./src/i2c_program.d \
./src/main.d \
./src/utils.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imc -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -DLSCC_STDIO_UART_APB -I"D:\Propel_Study\I2C_SPI_Programming_singlecore\Workspace\I2C_SPI_GPIO/src" -I"D:\Propel_Study\I2C_SPI_Programming_singlecore\Workspace\I2C_SPI_GPIO/src/bsp" -I"D:\Propel_Study\I2C_SPI_Programming_singlecore\Workspace\I2C_SPI_GPIO/src/bsp/driver" -I"D:\Propel_Study\I2C_SPI_Programming_singlecore\Workspace\I2C_SPI_GPIO/src/bsp/driver/gpio" -I"D:\Propel_Study\I2C_SPI_Programming_singlecore\Workspace\I2C_SPI_GPIO/src/bsp/driver/i2c_controller" -I"D:\Propel_Study\I2C_SPI_Programming_singlecore\Workspace\I2C_SPI_GPIO/src/bsp/driver/riscv_mc" -I"D:\Propel_Study\I2C_SPI_Programming_singlecore\Workspace\I2C_SPI_GPIO/src/bsp/driver/spi_controller" -I"D:\Propel_Study\I2C_SPI_Programming_singlecore\Workspace\I2C_SPI_GPIO/src/bsp/driver/uart" -std=gnu11 --specs=picolibc.specs -DPICOLIBC_INTEGER_PRINTF_SCANF -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


