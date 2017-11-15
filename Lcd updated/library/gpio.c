/*
 * gpio.c
 *
 *  Created on: Nov 15, 2017
 *      Author: IBM
 */
#include <msp430.h>
#include "gpio.h"


# define DWR_RS P1OUT |= BIT3;      // RS signal for data;
# define CWR_RS P1OUT &= ~BIT3;     // RS signal for command;
# define WR P1OUT &= ~BIT1;         // Write signal for writing on to the LCD.
# define Enable_High P1OUT |=BIT2;
# define Enable_Low P1OUT &= ~BIT2;

unsigned int i,j;
void delay(delay){
    for(i=0; i<delay; i++){
        for(j=0; j<delay;j++){
            asm("nop");

        }
    }
}
/* GPIO initialization
 *
 */

void GPIO_init(){
   // P1SEL &= 0x00;
    //P2SEL &= 0x00;
    P1DIR |= 0xFF;
    P1OUT &= ~0xFF;
}
/* GPIO initialization
 *
 */
void LCD_init(){
    GPIO_init();
    Command_Write(0x33);   // 8 bit mode
    Command_Write(0x32);   // 8 bit mode
    Command_Write(0x28);   // 4 bit mode
    Command_Write(0x0E);   // clear the screen
    Command_Write(0x01);   // display on cursor on
    Command_Write(0x06);    // increment cursor
    Command_Write(0x80);    // Column 1 row 1
}

/*
 * Command write function
 *
 */


void Data_Enable(){
    Enable_High;     //TODO CHANGE DELAY
    __delay_cycles(40);
    Enable_Low;

}

void String_Write(char *s){
    while(*s){
        Data_Write(*s);
        s++;
    }
}



/*
 * Command write function
 *
 */

void Command_Write(unsigned char cmd){
    CWR_RS;     // RS=0 signal for command write;
    WR;         // WR=0 signal for command write;
    P1OUT = (P1OUT&0x0F)|(cmd&0xF0);
    Data_Enable();
    P1OUT = (P1OUT&0x0F)|((cmd<<4)&0xF0);
    Data_Enable();
}

/* Data write function
 *
 *
 *
 */
void Data_Write(unsigned char data){
    DWR_RS;
    WR;
    P1OUT = (P1OUT&0x0F)|(data&0xF0);
    Data_Enable();
    P1OUT = (P1OUT&0x0F)|((data<<4)&0xF0);
    Data_Enable;
}






