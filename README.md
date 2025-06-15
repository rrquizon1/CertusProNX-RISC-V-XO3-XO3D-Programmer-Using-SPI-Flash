# Introduction

This is an I2C internal flash programming examples for MachXO2/MachXO3 and MachXO3D using Lattice Certus Pro NX.

The MachXO3 and MachXO2 devices feature internal flash memory that supports single boot, eliminating the need for an external flash and reducing component count. However, an external flash can still be used to store a golden image.For more information
please check FPGA-TN-02155 ([MachXO2 Programming and Configuration User Guide](https://www.latticesemi.com/view_document?document_id=39085)) and FPGA-TN-02055 ([MachXO3 Programming and Configuration User Guide](https://www.latticesemi.com/view_document?document_id=50123)).

MachXO3D have two sectors for internal flash programming namely CFG0 and CFG1. These sectors can be used for dual-boot instead of using an external flash for golden image. FPGA-TN-02069-1.8 ([MachXO3D Programming and Configuration User Guide](https://www.latticesemi.com/view_document?document_id=52591)) shows more information regarding MachXO3D dualboot and other features.

This example is very similar to the [Lattice Certus Pro as Programmer of XO2/XO3/XO3D](https://github.com/rrquizon1/MachXO2-XO3-and-MachXO3D-I2C-internal-flash-Programming-using-STM32) I did before but now we are using an external SPI Flash to store the bitstream of the slave devices.

There are several key benefits to using external SPI flash memory rather than relying solely on system memory:

1. Preserves system RAM: By offloading firmware, configuration data, or resource files to SPI flash, more internal RAM is made available for application logic and peripheral management—beneficial for processors with limited memory like RISC-V cores.
2. Larger storage capacity: SPI flash devices typically offer significantly larger storage than internal memory. This allows storing large bitstreams, multiple firmware images, or configuration files for multiple devices in the system.
3. Simplified firmware updates: In complex systems, it is easier to update firmware by simply rewriting the contents of the SPI flash. The main processor (e.g., Lattice CertusPro-NX) can then use the updated data to reprogram or reconfigure connected components. This supports features like in-field or over-the-air (OTA) updates.
4. Non-volatile storage: Unlike RAM, SPI flash retains data even when power is removed. This makes it ideal for storing critical firmware or bootloaders that must persist across power cycles.

The Lattice CertusPro™-NX is a high-performance, low-power FPGA family built on Lattice’s Nexus platform. Designed for compute- and connectivity-intensive applications, it offers advanced features typically found in larger FPGAs, while maintaining the power efficiency and small form factor that Lattice is known for.


# Main Project creation
In this example, we’ll use a RISC-V processor and configure I2C programming similarly to how it’s done on a microcontroller. This approach is designed to help microcontroller users transition smoothly to FPGA-based SoC development.

We will be using three Lattice Boards for this example:
* CertusPro-NX Evaluation Board- Main RISC V Processor (Equipped with External SPI flash)
* MachXO3 Starter Kit- I2C Slave to be programmed
* MachXO3D Breakout board- I2C Slave to be programmed
![image](https://github.com/user-attachments/assets/d1db85bb-9abd-451e-ade9-cd6193b82888)

For this project we will be using Four Lattice Tools
* Lattice Propel Builder 2024.2 => Build the SoC with RISCV Processor
* Lattice Radiant Software 2024.2 => Generate the bitstream to turn our FPGA to a SoC
* Lattice Propel 2024.2 => Firmware development for RISCV processor
* Lattice Radiant Programmer 2024.2=>Program the bitstream into your device

* First off is we use Lattice Propel Builder to build our SoC. Lattice have multiple templates using RISCV core. See below for the SoC I built with Lattice Propel Builder

![image](https://github.com/user-attachments/assets/29da6a41-e412-40a1-89c9-1664b34818a0)

Most templates have the following relevant parts:

OSC and PLLs used as clock source for the CPU and its peripherals
RISC V processor
UART peripheral- This peripheral is used for printf debugging
GPIO peripheral- For simple GPIO control
System Memory
For this example, I added two additional peripherals

I2C Master Peripheral- this perihperal will be used to program MachXO2/XO3/XO3D via I2C
SPI Master- This peripheral is used to communicate with the SPI Flash

After building the circuit, you have to validate then generate the design:
![image](https://github.com/user-attachments/assets/6d9ec414-a34d-46b2-9c15-9181c20803c6)

After generating your design, it's now time to open Lattice Radiant Software and Lattice Propel!
![image](https://github.com/user-attachments/assets/e5f93fb2-fe1d-4964-bb1d-9eac5a785512)

In Lattice Radiant, you generate the bitstream for the CertusPro-NX FPGA, configuring it to function as a processor. Complementing this, Lattice Propel serves as your integrated development environment (IDE) for developing embedded firmware, similar to how STM32CubeIDE is used for STM32 microcontrollers.

Once you opened Radiant, the Radiant Project for the SoC will be generated. This will look just like a normal Radiant PRoject. You could can set the pins in the project and then run the whole flow:
![image](https://github.com/user-attachments/assets/2512990e-d6c2-44cc-80aa-e22b00425d06)


Once you run the whole flow, you should now have a bitstream generated in your project, you should program it using Radiant Programmer.

After programming this to the CertusProNX Evaluation board, your device will now work as a RISCV controller:
![image](https://github.com/user-attachments/assets/1e97f613-1589-474a-8d7f-847940c5135f)

Now Let's go to Lattice Propel, I already have the workspace attached in this Repo, you could just load it right after you program the bitstream:
Notice that it looks very similar to the STM32 IDE! You should fit right in on how to use it. As from here on, you could already use your microcontroller knowledge on implementing your project. Take note that when you generate the workspace only UART peripheral is properly initialized. In these peripheral I used GPIO and I2C so I had to initialize them.

In this workspace I already had them initialized. If you want to learn more about this drivers you can go to src=>bsp. All the drivers of the peripherals used should be here.

Aside from the auto generated .c and .h file I added some .c and .h files that contains the functions used for programmign the MachXO2 and MachXO3D devices:

