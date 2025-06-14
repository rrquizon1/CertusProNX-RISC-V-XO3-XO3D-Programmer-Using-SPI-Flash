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
