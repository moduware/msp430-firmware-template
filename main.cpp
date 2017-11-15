
#include <msp430.h>
#include "gpio.h"

/*
 * main.cpp
 *
 *  Created on: Nov 15, 2017
 *      Author: IBM
 */

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
    LCD_init();
    String_Write("Balbir");
    while(1){

    }

}



