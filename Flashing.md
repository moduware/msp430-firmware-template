# Flashing the firmware on MSP430 

Download and install latest version of [Code Composer Studio](http://processors.wiki.ti.com/index.php/Download_CCS) (versions supported down to V5.5)

## Compiling MSP430 firmware
* Install MSP430 4.2.1 compiler
    * Open Code Composer Studio and click on *Help > Install New Software...*
    
    ![compiler_instructions_1]
    
    * Select *Work With* as image below, search for **MSP430 Compiler Tools 4.2.1** and click on *Next*
    
    ![compiler_instructions_2]
    
    * Finish Installation 
    
    ![compiler_instructions3]

## Flashing Configuration 
- Wire MSP module to MSP-EXP430G2 LaunchPad (Emulation part) and connect LaunchPad to USB

![MSP-LaunchPad]
- Make sure *Project>Debug>MSP430 Properties> 
Project >	Properties	>	Debug	>	MSP430	Properties	>‘Replace written memory locations, retain unwritten memory locations’ is selected*

![Debug_options]

- Flash the firmware

![Debug]

## Important 
- The module connector has two sides. Insert the module to the gateway facing the pins out of the hub (note that it is easier to attach the wires to a breadboard or other hardware)



[compiler_instructions_1]:https://github.com/nexpaq/msp430-firmware-template/blob/develop/img/compiler_instructions_1.jpg
[compiler_instructions_2]:https://github.com/nexpaq/msp430-firmware-template/blob/develop/img/compiler_instructions_2.jpg
[compiler_instructions3]:https://github.com/nexpaq/msp430-firmware-template/blob/develop/img/compiler_instructions3.jpg
[MSP-LaunchPad]:https://github.com/nexpaq/msp430-firmware-template/blob/develop/img/MSP-LaunchPad.jpg
[Debug_options]:https://github.com/nexpaq/msp430-firmware-template/blob/master/img/Debug_options.png
[Debug]:https://github.com/nexpaq/msp430-firmware-template/blob/develop/img/Debug.jpg