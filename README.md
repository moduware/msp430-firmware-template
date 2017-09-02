# MSP430 firmware template
Template for development of firmware on MSP430 development module

msp430 firmware template conatains the firmware project configuration, libraries for communicating the MSP module to a gateway. Absolute minimum files for communication are:

- tmain.cpp (main cpp file)
- np_module_mdk_v1 (mdk library files )

This template also includes default folder and file structure, plus additional related files to make your developement process easier and faster. Clone or fork this repository and start your development. Everyone is also welcome to contribute and improve this template, just do a pull request.

File structure:

- libraries - folder to store existing libraries
    - HC_SR04 - library files for ultrasonic sensor HC SR04
    - I2C - library files for I2C communication
    - LiquidCrystal - library files for LCD 16x02
    - NCN_GPIO - Library files for General Prupose Input/Output generic pins
    - soft_uart_cpp - UART communication simulation
    - queue - library file to use with soft_uart_cpp library
- mdk - folder for mdk library module-gateway communicatio
- t_main - main file to write the firmware cose
- t_my_app - file linked to t_main. Use for sending data from the tile to the fiwmare