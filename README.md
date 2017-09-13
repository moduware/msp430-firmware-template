# MSP430 firmware template
Template for development of firmware on MSP430 development module

To start up with a MSP module project, download and install [Code Composer Studio](http://processors.wiki.ti.com/index.php/Download_CCS#Code_Composer_Studio_Version_5_Downloads) V5.5 version or above (Eclipse based IDE, C and C++ languages are used)

Recommendation: install 16K FLASH free edition as it is suitable for MSP module projects

msp430 firmware template contains the firmware project configuration, libraries for communicating the MSP module to a gateway and additional libraries.

Absolute minimum files for communication are:

- tmain.cpp (main cpp file)
- np_module_mdk_v1 (mdk library files )

This template also includes default folder and file structure, plus additional related files to make your development process easier and faster. Clone or fork this repository and start your development. Everyone is also welcome to contribute and improve this template, just do a pull request.

File structure:

- libraries - folder to store existing libraries (click on links for datasheets and additional information)
    - [HC_SR04](https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf) - library files for ultrasonic sensor HC SR04
    - [I2C](https://learn.sparkfun.com/tutorials/i2c) - library files for I2C communication
    - LiquidCrystal - library files for [LCD 16x02](https://www.sparkfun.com/datasheets/LCD/ADM1602K-NSW-FBS-3.3v.pdf)
    - NCN_GPIO - Library files for General Purpose Input/Output generic pin MSP module configuration
    - soft_uart_cpp - [UART](http://www.simplyembedded.org/tutorials/msp430-uart/) communication simulation
    - queue - [FIFO or queue](http://www.simplyembedded.org/tutorials/interrupt-free-ring-buffer/) library file to use with soft_uart_cpp library
- mdk - folder for mdk library module-gateway communication
- t_main - main file to write the firmware code
- t_my_app - file linked to t_main. Use for sending data from the tile to the firmware

Find additional information on [MSP430 architecture](http://www.simplyembedded.org/tutorials/msp430-architecture/)
- TODO: add information about available/used memory on MSP module
- TODO: Add information about available/used timers and interrupts 
- TODO: Add information on available modes (master/slave) to use on I2C library on library comments
- TODO: Add information about soft UART speed on library comments 






