/*
 * data.c
 *
 *  Created on: Mar 9, 2025
 *      Author: Rhodz
 */
#include "uart.h"
#include "gpio.h"
#include "pic.h"
#include "sys_platform.h"
#include "utils.h"
#include <stdio.h>
#include "hal.h"
#include "i2c_master.h"
#include "spi_master.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "i2c_program.h"

void i2c_program_XO3D(struct gpio_instance *gpio,struct i2cm_instance *i2c_master,uint8_t addr, const unsigned char *bitstream, const int bitstream_len,int CFG){
	printf("=======================================================\n");
	printf("Programming MachXO3D Via I2C with address: 0x%02x\n",addr);
	printf("=======================================================\n");

	i2c_device_id(i2c_master,addr);//Device ID check
	i2c_isc_enable_sram(i2c_master,addr);//ISC Enable SRAM
	i2c_isc_erase_sram(i2c_master,addr);//ISC Erase SRAM
	i2c_sr_read(i2c_master,addr);//Status Register Read
	i2c_isc_enable_flash_XO2_XO3(i2c_master,addr);//ISC Enable Flash
	i2c_isc_erase_flash_XO3D(gpio,i2c_master,addr,CFG);// ISC Erase Flash
	i2c_sr_read(i2c_master,addr);// Status Register Read
	i2c_lsc_init_address_XO3D(i2c_master,addr,CFG);// Init Address CFGX
	i2c_flash_program(gpio ,i2c_master,addr,bitstream,bitstream_len);//Flash Program
	i2c_lsc_init_address_XO3D(i2c_master,addr,CFG);//Init Address CFGX
	i2c_flash_verify(gpio,i2c_master,addr,bitstream,bitstream_len);//Flash Verify
	i2c_lsc_init_address_XO3D(i2c_master,addr,CFG);//Init Address CFGX
	i2c_program_done(i2c_master,addr);// Program Done bit
	i2c_sr_read(i2c_master,addr);// Status Register Read
	i2c_isc_disable(i2c_master,addr);//Device Exits Programming mode*/

}

void i2c_program_XO2_XO3(struct gpio_instance *gpio,struct i2cm_instance *i2c_master,uint8_t addr, const unsigned char *bitstream,const int bitstream_len){

	printf("=======================================================\n");
	printf("Programming MachXO2/XO3 Via I2C with address: 0x%02x\n",addr);
	printf("=======================================================\n");
	i2c_device_id(i2c_master,addr);//Device ID check
	i2c_isc_enable_sram(i2c_master,addr);//ISC Enable SRAM
	i2c_isc_erase_sram(i2c_master,addr);//ISC Erase SRAM
	i2c_sr_read(i2c_master,addr);//Status Register Read
	i2c_isc_enable_flash_XO2_XO3(i2c_master,addr);//ISC Enable Flash
	i2c_sr_read(i2c_master,addr);//Status Register Read
	i2c_lsc_init_address_XO2_XO3(i2c_master,addr);
	i2c_isc_erase_flash_XO2_XO3(gpio,i2c_master,addr);
	i2c_lsc_init_address_XO2_XO3(i2c_master,addr);
	i2c_flash_program(gpio,i2c_master,addr,bitstream,bitstream_len);//Flash Program
	i2c_lsc_init_address_XO2_XO3(i2c_master,addr);
	i2c_flash_verify(gpio,i2c_master,addr,bitstream,bitstream_len);//Flash Verify
	i2c_program_done(i2c_master,addr);// Program Done bit
	i2c_sr_read(i2c_master,addr);// Status Register Read
	i2c_isc_disable(i2c_master,addr);//Device Exits Programming mode*/

}


void i2c_isc_disable(struct i2cm_instance *i2c_master,uint8_t addr){

	uint8_t isc_disable[4]={0x26,0x00,0x00,0x00};
	i2c_master_write(i2c_master, addr, 4, isc_disable);
	printf("Device Exits Programming Mode!\n");
}
void i2c_program_done(struct i2cm_instance *i2c_master,uint8_t addr){
	uint8_t program_done[4]={0x5E,0x00,0x00,0x00};
	i2c_master_write(i2c_master, addr, 4,program_done);
	delayMS(1);
	printf("Programmed CFG Internal Done bit!\n");

}
void i2c_flash_verify(struct gpio_instance *gpio,struct i2cm_instance *i2c_master,uint8_t addr,const unsigned char *bitstream,const int bit_len){

	int num_chunks= ((bit_len + 16 - 1) / 16);
	uint8_t lsc_read_incr[4]={0x73,0x00,0x00,0x00};
	uint8_t read_buffer[16];

    printf("Verifying internal flash..\n");
   for(int k=0;k<num_chunks;k++){
       i2c_master_repeated_start(i2c_master,addr,4,lsc_read_incr,16,read_buffer);
   if (memcmp( read_buffer, &bitstream[k*16], 16) == 0) {

   } else {
       printf("Verify Fail\n");
       gpio_output_write(gpio,0, 1);
       exit(0);
   }
	if (k%200==0){
		gpio_output_write(gpio,0, 1);
	}

	else if (k%200==100) {
		gpio_output_write(gpio,0, 0);

	}

   delayMS(2);
   }
   printf("Verify Successful!\n");
   gpio_output_write(gpio,0, 0);

}


void i2c_flash_program(struct gpio_instance *gpio, struct i2cm_instance *i2c_master,uint8_t addr,const unsigned char *bitstream,const int bit_len){
	uint8_t lsc_prog_incr[4]={0x70,0x00,0x00,0x00};
	uint8_t prog_buffer[20];
	int num_chunks= ((bit_len + 16 - 1) / 16);
	int step = bit_len/7;
	int level=0;
	printf("Programming internal flash..\n");
	for(int k=0;k<num_chunks;k++){
		memcpy(prog_buffer, lsc_prog_incr, 4);
		memcpy(prog_buffer+4, &bitstream[k*16], 16);
		i2c_master_write(i2c_master, addr, 20, prog_buffer);
		delayMS(2);
		if (k%200==0){
			gpio_output_write(gpio,0, 1);
		}

		else if (k%200==100) {
			gpio_output_write(gpio,0, 0);

		}
	  }
	gpio_output_write(gpio,0, 0);
	printf("Finished Programming internal flash!\n");



}
void i2c_lsc_init_address_XO3D(struct i2cm_instance *i2c_master,uint8_t addr,int CFG){
	uint8_t lsc_init_address[4]={0x46,0x00,0x01,0x00};
	 if (CFG==0){
		 lsc_init_address[2]=0x01;
		 printf("Init Address at CFG0\n");
	 }

	 else if (CFG==1){
		 lsc_init_address[2]=0x02;
		 printf("Init Address at CFG1\n");
	 }

	 else if (CFG==3){
		 lsc_init_address[2] =0x00;
		 lsc_init_address[1] =0x04;
		 printf("Init Address at feature row\n");

	 }

	 else{

		 printf("Not a Valid sector\n");
	 }
	i2c_master_write(i2c_master, addr, 4, lsc_init_address);
	delayMS(1);
}


void i2c_lsc_init_address_XO2_XO3(struct i2cm_instance *i2c_master,uint8_t addr){
	uint8_t lsc_init_address[4]={0x46,0x04,0x00,0x00};

	printf("Init Address at Internal Flash!\n");



	i2c_master_write(i2c_master, addr, 4, lsc_init_address);
	delayMS(1);
}




void i2c_isc_erase_flash_XO3D(struct gpio_instance *gpio,struct i2cm_instance *i2c_master,uint8_t addr, int CFG){
	 printf("Erasing Internal Flash.....\n");
	 uint8_t isc_erase_flash[4]={0x0E,0x00,0x01,0x00};
	 if (CFG==0){
		 isc_erase_flash[2]=0x01;
	 }

	 else{
		 isc_erase_flash[2]=0x02;

	 }

		i2c_master_write(i2c_master, addr, 4, isc_erase_flash);

		//delayMS(8000);
		int total_ms=10000;
		int elapsed=0;
		int led_state=0;
	    while (elapsed < total_ms) {
	        gpio_output_write(gpio, 0, led_state);         // Set LED
	        led_state = !led_state;                          // Toggle LED
	        delayMS(500);                      // Wait
	        elapsed +=500;                    // Accumulate time
	    }
	 printf("Internal Flash Erased!\n");



}

void i2c_isc_erase_flash_XO2_XO3(struct gpio_instance *gpio,struct i2cm_instance *i2c_master,uint8_t addr ){
	 printf("Erasing Internal Flash.....\n");
	 uint8_t isc_erase_flash[4]={0x0E,0x04,0x00,0x00};


		i2c_master_write(i2c_master, addr, 4, isc_erase_flash);

		//delayMS(8000);
		int total_ms=10000;
		int elapsed=0;
		int led_state=0;
	    while (elapsed < total_ms) {
	        gpio_output_write(gpio, 0, led_state);         // Set LED
	        led_state = !led_state;                          // Toggle LED
	        delayMS(500);                      // Wait
	        elapsed +=500;                    // Accumulate time
	    }
	 printf("Internal Flash Erased!\n");



}

void i2c_isc_enable_flash_XO2_XO3(struct i2cm_instance *i2c_master,uint8_t addr){
	uint8_t isc_enable_flash[4]={0xC6,0x08,0x00};
	i2c_master_write(i2c_master, addr, 3, isc_enable_flash);
	delayMS(1);
	printf("Device Enters Config Mode: Flash\n");

}
void i2c_sr_read(struct i2cm_instance *i2c_master,uint8_t addr){
	uint8_t status_reg[4]={0x3C,0x00,0x00,0x00};
	uint8_t read[4];
	i2c_master_repeated_start(i2c_master,addr,4,status_reg,4,read);
	printf("Status Register Read\n");
	for(int i=0;i<4;i++){
			printf("0x%02x\n",read[i]);

	}

}
void i2c_isc_erase_sram(struct i2cm_instance *i2c_master,uint8_t addr){
	uint8_t isc_erase_sram[4]={0x0E,0x01,0x00,0x00};
	printf("Erasing internal SRAM\n");
	i2c_master_write(i2c_master, addr, 4, isc_erase_sram);
	delayMS(5);

}

void i2c_isc_enable_sram(struct i2cm_instance *i2c_master,uint8_t addr){
	uint8_t isc_enable_sram[4]={0xC6,0x00,0x00,0x00};
	i2c_master_write(i2c_master, addr, 4, isc_enable_sram);
	delayMS(1);
	printf("Device Enters Config Mode: SRAM\n");


}

void  i2c_device_id(struct i2cm_instance *i2c_master,uint8_t addr){

	uint8_t device_id[4]={0xE0,0x00,0x00,00};
	uint8_t read[4];
	i2c_master_repeated_start(i2c_master,addr,4,device_id,4,read);
	printf("Device ID Read\n");
	for(int i=0;i<4;i++){
			printf("0x%02x\n",read[i]);

	}


}
void i2c_flash_program_spiflash(struct gpio_instance *gpio,struct i2cm_instance *i2c_master,uint8_t slv_addr,struct spim_instance *spi_master,uint32_t start_addr,uint32_t end_addr){

	uint8_t read_command_address_a[4];
	uint8_t read_buffer_a[16];  // Read 16 bytes at a time
	uint8_t lsc_prog_incr[4]={0x70,0x00,0x00,0x00};
	uint8_t prog_buffer[20];
	printf("Programming internal flash from SPI Flash from address 0x%06x to 0x%06x \n",start_addr,end_addr);
	for (uint32_t addr = start_addr; addr <= end_addr; addr += 16) {
	    // Prepare READ command and 24-bit address
	    read_command_address_a[0] = 0x03;                     // READ command
	    read_command_address_a[1] = (addr >> 16) & 0xFF;
	    read_command_address_a[2] = (addr >> 8) & 0xFF;
	    read_command_address_a[3] = addr & 0xFF;

	    // Print Address
	  //  for(int i=0;i<4;i++){

	   // 	printf("Address and command: %02x \n",read_command_address_a[i]);

	   // }

	    spi_master_transfer_blocking(spi_master,
	                                 read_command_address_a,  // 1-byte cmd + 3-byte addr
	                                 4,
	                                 read_buffer_a,           // Data buffer
	                                 16);                   // Read 16 bytes

		memcpy(prog_buffer, lsc_prog_incr, 4);
		memcpy(prog_buffer+4, read_buffer_a, 16);

	   /* printf("Writing from Address 0x%06X: ", addr);
	    for (int i = 0; i < 20; i++) {
	        printf("%02X ",prog_buffer[i]);
	    }
	    printf("\n");*/


		i2c_master_write(i2c_master, slv_addr, 20, prog_buffer);
		delayMS(5);
		if (addr%0x200==0){
			gpio_output_write(gpio,0, 1);
		}

		else if (addr%0x200==0x100) {
			gpio_output_write(gpio,0, 0);

		}
	  }

	}


void i2c_flash_verify_spiflash(struct gpio_instance *gpio,struct i2cm_instance *i2c_master,uint8_t slv_addr,struct spim_instance *spi_master,uint32_t start_addr,uint32_t end_addr){


	uint8_t lsc_read_incr[4]={0x73,0x00,0x00,0x00};
	uint8_t read_buffer[16];
	uint8_t read_command_address_a[4];
	uint8_t read_buffer_spi[16];  // Read 16 bytes at a time
    printf("Verifying internal flash..\n");


	for (uint32_t addr = start_addr; addr <= end_addr; addr += 16) {
	    // Prepare READ command and 24-bit address
	    read_command_address_a[0] = 0x03;                     // READ command
	    read_command_address_a[1] = (addr >> 16) & 0xFF;
	    read_command_address_a[2] = (addr >> 8) & 0xFF;
	    read_command_address_a[3] = addr & 0xFF;

	    spi_master_transfer_blocking(spi_master,
	                                 read_command_address_a,  // 1-byte cmd + 3-byte addr
	                                 4,
	                                 read_buffer_spi,           // Data buffer
	                                 16);
	    delayMS(2);
	    i2c_master_repeated_start(i2c_master,slv_addr,4,lsc_read_incr,16,read_buffer);
	   // printf("Reading from Address 0x%06X: ", addr);
	   // for (int i = 0; i < 16; i++) {
	  //      printf("%02X ",read_buffer[i]);
	  //  }
	   // printf("\n");

		if (addr%0x200==0){
			gpio_output_write(gpio,0, 1);
		}

		else if (addr%0x200==0x100) {
			gpio_output_write(gpio,0, 0);

		}
	   if (memcmp( read_buffer, read_buffer_spi, 16) == 0) {

	   } else {
	       printf("Verify Fail\n");
	       gpio_output_write(gpio,0, 1);
	       exit(0);
	   }




	}


    /*
   for(int k=0;k<num_chunks;k++){
       i2c_master_repeated_start(i2c_master,addr,4,lsc_read_incr,16,read_buffer);
   if (memcmp( read_buffer, &bitstream[k*16], 16) == 0) {

   } else {
       printf("Verify Fail\n");
       gpio_output_write(gpio,0, 1);
       exit(0);
   }
	if (k%200==0){
		gpio_output_write(gpio,0, 1);
	}

	else if (k%200==100) {
		gpio_output_write(gpio,0, 0);

	}

   delayMS(2);
   }*/
   printf("Verify Successful!\n");
   gpio_output_write(gpio,0, 0);

}


void i2c_program_XO2_XO3_spiflash(struct gpio_instance *gpio,struct i2cm_instance *i2c_master,uint8_t addr,struct spim_instance *spi_master, uint32_t start_addr,uint32_t end_addr){

	printf("======================================================================\n");
	printf("Programming MachXO2/XO3 Via I2C with address: 0x%02x from SPI Flash\n",addr);
	printf("======================================================================\n");
	i2c_device_id(i2c_master,addr);//Device ID check
	i2c_isc_enable_sram(i2c_master,addr);//ISC Enable SRAM
	i2c_isc_erase_sram(i2c_master,addr);//ISC Erase SRAM
	i2c_sr_read(i2c_master,addr);//Status Register Read
	i2c_isc_enable_flash_XO2_XO3(i2c_master,addr);//ISC Enable Flash
	i2c_sr_read(i2c_master,addr);//Status Register Read
	i2c_lsc_init_address_XO2_XO3(i2c_master,addr);
	i2c_isc_erase_flash_XO2_XO3(gpio,i2c_master,addr);
	i2c_lsc_init_address_XO2_XO3(i2c_master,addr);
	i2c_flash_program_spiflash(gpio,i2c_master,addr,spi_master,start_addr,end_addr);
	i2c_lsc_init_address_XO2_XO3(i2c_master,addr);
	i2c_flash_verify_spiflash(gpio,i2c_master,addr,spi_master,start_addr,end_addr);
	i2c_program_done(i2c_master,addr);// Program Done bit
	i2c_sr_read(i2c_master,addr);// Status Register Read
	i2c_isc_disable(i2c_master,addr);//Device Exits Programming mode*/

}

void i2c_program_XO3D_spiflash(struct gpio_instance *gpio,struct i2cm_instance *i2c_master,uint8_t addr, struct spim_instance *spi_master, uint32_t start_addr,uint32_t end_addr,int CFG){
	printf("===================================================================\n");
	printf("Programming MachXO3D Via I2C with address: 0x%02x from SPI Flash\n ",addr);
	printf("===================================================================\n");

	i2c_device_id(i2c_master,addr);//Device ID check
	i2c_isc_enable_sram(i2c_master,addr);//ISC Enable SRAM
	i2c_isc_erase_sram(i2c_master,addr);//ISC Erase SRAM
	i2c_sr_read(i2c_master,addr);//Status Register Read
	i2c_isc_enable_flash_XO2_XO3(i2c_master,addr);//ISC Enable Flash
	i2c_isc_erase_flash_XO3D(gpio,i2c_master,addr,CFG);// ISC Erase Flash
	i2c_sr_read(i2c_master,addr);// Status Register Read
	i2c_lsc_init_address_XO3D(i2c_master,addr,CFG);// Init Address CFGX
	i2c_flash_program_spiflash(gpio,i2c_master,addr,spi_master,start_addr,end_addr);
	i2c_lsc_init_address_XO3D(i2c_master,addr,CFG);//Init Address CFGX
	i2c_flash_verify_spiflash(gpio,i2c_master,addr,spi_master,start_addr,end_addr);
	i2c_lsc_init_address_XO3D(i2c_master,addr,CFG);//Init Address CFGX
	i2c_program_done(i2c_master,addr);// Program Done bit
	i2c_sr_read(i2c_master,addr);// Status Register Read
	i2c_isc_disable(i2c_master,addr);//Device Exits Programming mode*/
	//i2c_refresh(i2c_master,addr);//Device Exits Programming mode*/
}

void spiflash_deviceid(struct spim_instance *spi_master){

	uint8_t cmd1_tx[1] = { 0x9E };
	uint8_t cmd1_rx[4];
    uint8_t status = spi_master_transfer_blocking(spi_master,
                                                  cmd1_tx,  // Command
                                                  1,
                                                  cmd1_rx,  // Data IN
                                                  3);

        // Read JEDEC ID
        uint8_t manufacturer_id = (uint8_t)cmd1_rx[0];
        uint8_t memory_type     = (uint8_t)cmd1_rx[1];
        uint8_t capacity        = (uint8_t)cmd1_rx[2];
        printf("JEDEC ID: %02X %02X %02X\n", manufacturer_id, memory_type, capacity);



}

void  i2c_refresh(struct i2cm_instance *i2c_master,uint8_t addr){

	uint8_t device_id[4]={0x79,0x00,0x00,00};
	uint8_t read[4];
	i2c_master_repeated_start(i2c_master,addr,4,device_id,4,read);


}

