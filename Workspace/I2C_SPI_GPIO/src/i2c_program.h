/*
 * data.h
 *
 *  Created on: Mar 9, 2025
 *      Author: Rhodz
 */

#ifndef INC_I2C_PROGRAM_H_
#define INC_I2C_PROGRAM_H_

void i2c_device_id(struct i2cm_instance *i2c_master,uint8_t addr);
void i2c_isc_enable_sram(struct i2cm_instance *i2c_master,uint8_t addr);
void i2c_isc_erase_sram(struct i2cm_instance *i2c_master,uint8_t addr);
void i2c_sr_read(struct i2cm_instance *i2c_master,uint8_t addr);
void i2c_isc_enable_flash_XO2_XO3(struct i2cm_instance *i2c_master,uint8_t addr);
void i2c_isc_erase_flash_XO2_XO3(struct gpio_instance *gpio,struct i2cm_instance *i2c_master,uint8_t addr );
void i2c_lsc_init_address_XO2_XO3(struct i2cm_instance *i2c_master,uint8_t addr);
void i2c_flash_program(struct gpio_instance *gpio,struct i2cm_instance *i2c_master,uint8_t addr,const unsigned char *bitstream,const int bit_len);
void i2c_flash_verify(struct gpio_instance *gpio,struct i2cm_instance *i2c_master,uint8_t addr,const unsigned char *bitstream,const int bit_len);
void i2c_program_done(struct i2cm_instance *i2c_master,uint8_t addr);
void i2c_isc_disable(struct i2cm_instance *i2c_master,uint8_t addr);
void i2c_program_XO2_XO3(struct gpio_instance *gpio,struct i2cm_instance *i2c_master,uint8_t addr, const unsigned char *bitstream, const int bitstream_len);
void i2c_program_XO3D(struct gpio_instance *gpio,struct i2cm_instance *i2c_master,uint8_t addr, const unsigned char *bitstream, const int bitstream_len,int CFG);
void i2c_isc_erase_flash_XO3D(struct gpio_instance *gpio,struct i2cm_instance *i2c_master,uint8_t addr, int CFG);
void i2c_lsc_init_address_XO3D(struct i2cm_instance *i2c_master,uint8_t addr,int CFG);
void i2c_flash_program_spiflash(struct gpio_instance *gpio,struct i2cm_instance *i2c_master,uint8_t slv_addr,struct spim_instance *spi_master,uint32_t start_addr,uint32_t end_addr);
void i2c_flash_verify_spiflash(struct gpio_instance *gpio,struct i2cm_instance *i2c_master,uint8_t slv_addr,struct spim_instance *spi_master,uint32_t start_addr,uint32_t end_addr);
void i2c_program_XO2_XO3_spiflash(struct gpio_instance *gpio,struct i2cm_instance *i2c_master,uint8_t addr,struct spim_instance *spi_master, uint32_t start_addr,uint32_t end_addr);
void i2c_program_XO3D_spiflash(struct gpio_instance *gpio,struct i2cm_instance *i2c_master,uint8_t addr, struct spim_instance *spi_master, uint32_t start_addr,uint32_t end_addr,int CFG);
void spiflash_deviceid(struct spim_instance *spi_master);
void  i2c_refresh(struct i2cm_instance *i2c_master,uint8_t addr);
#endif /* INC_DATA_H_ */
