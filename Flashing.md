# Flashing the firmware on MSP430 

Download and install latest version of [Code Composer Studio](http://processors.wiki.ti.com/index.php/Download_CCS) (versions supported down to V5.5)

## Compiling MSP430 firmware
- Install MSP430 4.2.1 compiler
    - Open Code Composer Studio and click on *Help > Install New Software...*
    ![](img/compiler_instructions_1)
    - Select *Work With* as image below, search for **MSP430 Compiler Tools 4.2.1** and click on *Next*
    ![](img/compiler_instructions_2)
    - Finish Installation 
    ![](img/compiler_instructions3)

## Flashing Configuration 
- Wire MSP module to MSP-EXP430G2 LaunchPad (Emulation part) and connect LaunchPad to USB
![img/MSP-LaunchPad]
- Make sure *Project>Debug>MSP430 Properties> 
Project >	Properties	>	Debug	>	MSP430	Properties	>‘Replace written memory locations, retain unwritten memory locations’ is selected
![](img/Debug_options)
- Flash the firmware
![](img/Debug)

## Important 
- The module connector has two sides. Insert the module to the gateway facing the pins out of the hub (note that it is easier to attach the wires to a breadboard or other hardware)



