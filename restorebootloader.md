# How to fix the broken MSP430 Bootloader
## Introduction - Bootloader
In the process of msp 430 project development the embedded memory can be accessed with the help of boot loader which was also known as Boot Strap Loader(BSL). It allows the user to communicate with the available memory in the prototype or initial phase of product development. The available flash memory/programmable memory (FRAM) and data memory(RAM) can be modified as required by users. Boot loader actually control the data exchange activities of the MCU hence, avoiding accidental removal or overwriting
of BSL commands. In case, you have created a program that accidentally erased or overwritten the boot loader file, following procedure explains how we can fix it.


## Flashing MSP module with bootloader
If main memory has been erased while flashing MSP module with the program code, follow this document to upload it again


### Requirements
- MSP module
- TI Launch Pad
- Female- female wire connector
- Software [FET- Pro 430][FET430]
- Bootloader file [bootloader v1.0.1.txt][bootloader]

## Steps
### Step 1
Connect the MSP430 module with the TI launch pad as per following table and diagram:

|    MSP430 module    |    TI launch pad     |
|   ---------------   |    ---------------   |
|         3V3         |          3V3         |
|         GND         |          GND         |
|         IO          |          RST         |
|         CLK         |         TEST         |

![Connection]

### Step 2
Install, if not previously and run the FET-Pro430 and load the bootlaoder v1.0.1.txt file as shown in diagram below. Make sure the bootloader file version is the latest(v1.0.1).


![STEP2]

### Step 3
Go to Setup -> Connection/Device Reset and select the following items:

![STEP3]

### Step 4

Go to Setup ! Lock/ Unlock Setup and select 'Yes'

![STEP4]

### Step 5

Press next to upload the boatloader to the MSP module and wait until the process is finished and the status has updated to 'pass' as shown by the diagram below:


![STEP5]


## Miscellaneous
During the setup of target connection  sometime the FET-pro430 continue to give error like target not found.
In such cases try following:
- Plug the target device into another available USB port.
- Restart FET pro430.

## Useful links
[Bootloader- Additional information about the bootloader program][boot]

[Connection]:https://github.com/nexpaq/msp430-firmware-template/blob/master/Images/connection.jpg
[STEP2]:https://github.com/nexpaq/msp430-firmware-template/blob/master/Images/step2.png
[STEP3]:https://github.com/nexpaq/msp430-firmware-template/blob/master/Images/step3.png
[STEP4]:https://github.com/nexpaq/msp430-firmware-template/blob/master/Images/step4.png
[STEP5]:https://github.com/nexpaq/msp430-firmware-template/blob/master/Images/step5.png





[bootloader]:https://github.com/nexpaq/msp430-firmware-template/blob/master/bootloader_v1.0.1.txt
[FET430]:https://www.elprotronic.com/productdata
[boot]:http://www.ti.com/lit/ug/slau319n/slau319n.pdf
