# How to fix the broken MSP430 Bootloader
## Introduction - Bootloader
In the process of msp 430 project development the embedded memory can be accessed with the help of boot loader which was also known as Boot strap loader(BSL). It allows the user to communicate with the available memory in prototype or initial phase of product development. The available flash memory or programmable memory (FRAM) and data memory also known as RAM can be modified as required by users. Boot loader actually control the data exchange activities of the MCU hence, avoiding accidental removal or overwriting
of BSL commands. In case, you have created a program that accidentally erased or overwritten the boot loader file, following procedure explains how we can fix it.
## Flashing MSP module with bootloader
If main memory is being erased when flashing MSP module, follow this document to upload it again
### Requirements
- MSP module
- TI Launch Pad
- Female- female wire connector
- Software [FET- Pro 430][FET430]
- Bootloader file [bootloader v1.0.1.txt][bootloader]
### Step 1











[bootloader]:https://github.com/nexpaq/msp430-firmware-template/blob/master/bootloader_v1.0.1.txt
