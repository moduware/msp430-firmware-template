# MSP430 firmware template
Template for development of firmware on MSP430 development module

To start up with an MSP430 module project, download and install [Code Composer Studio](http://processors.wiki.ti.com/index.php/Download_CCS) latest version (versions supported down to V5.5)

Recommendation: install 16K FLASH free edition as it is suitable for MSP430 module projects

MSP430 firmware template contains the firmware project configuration, libraries for communicating the MSP module to a gateway and additional libraries.

Absolute minimum files for communication are:

- tmain.cpp (main cpp file)
- np_module_mdk_v1 (mdk library files)
- lnk_msp430g2553.cmd: linker command file

This template also includes default folder and file structure, plus additional related files to make your development process easier and faster. Clone or fork this repository and start your development. Everyone is also welcome to contribute and improve this template, just do a pull request.

## File structure:

- libraries - folder to store existing libraries (click on links for datasheets and additional information)
    - [HC_SR04](https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf) - library files for ultrasonic sensor HC SR04
    - [I2C](https://learn.sparkfun.com/tutorials/i2c) - library files for I2C communication
    - LiquidCrystal - library files for [LCD 16x02](https://www.sparkfun.com/datasheets/LCD/ADM1602K-NSW-FBS-3.3v.pdf)
    - NCN_GPIO - Library files for General Purpose Input/Output generic pin MSP module configuration
    - soft_uart_cpp - [UART](http://www.simplyembedded.org/tutorials/msp430-uart/) communication simulation
    - queue - [FIFO or queue](http://www.simplyembedded.org/tutorials/interrupt-free-ring-buffer/) library file to use with soft_uart_cpp library
- mdk - folder for mdk library module-gateway communication
- t_main - main file to write the firmware code
- Flashing: steps and setup on how to flash the firmware on MSP430 module
- How to Fix broken MSP430 Bootloader: steps and setup on how to restore the BSL 
- Interrupt vectors and timers MSP430: table on available interrupt vectors and timers 
- MSP430 memory settings: information about available and used memory
- Protocol Message Format: message exchange format 
- bootloader_v1.0.1.txt - BSL firmware file to restore bootloader on MSP430 module

## Related links 
- [Flash the firmware on MSP430 module](https://github.com/nexpaq/msp430-firmware-template/blob/master/Flashing.md)
- [Restore the bootloader on MSP430 module](https://github.com/nexpaq/msp430-firmware-template/blob/master/restorebootloader.md)
- [MSP430 module memory settings](https://github.com/nexpaq/msp430-firmware-template/blob/master/MSP430%20memory%20settings%20.md) 
- [Interrupt vectors and timers on MSP430 module](https://github.com/nexpaq/msp430-firmware-template/blob/master/Interrupt%20vectors%20and%20timers%20msp430.md)
- [Protocol Message Format](https://github.com/nexpaq/msp430-firmware-template/blob/master/Protocol%20Message%20Format.md)
- [MSP430 architecture](http://www.simplyembedded.org/tutorials/msp430-architecture/)
- [MSP430 Specifications and datasheet](http://www.ti.com/lit/ds/symlink/msp430g2253.pdf)

- TODO: Add information on available modes (master/slave) to use on I2C library on library comments
- TODO: Add information about soft UART speed on library comments 
