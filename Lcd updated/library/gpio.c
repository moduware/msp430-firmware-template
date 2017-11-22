/*
 * gpio.c
 *
 *  Created on: Nov 15, 2017
 *      Author: Balbir
 */
#include <msp430.h>
#include "gpio.h"

/*
 * Control signalS(RS, WR and Enable) initialization for LCD
 *
 * */

# define DWR_RS P1OUT |= BIT3;      // RS(Register Select) = 1 signal to select the data register of LCD;
# define CWR_RS P1OUT &= ~BIT3;     // RS(Register Select) = 0 signal to select the command register of LCD;
# define WR P1OUT &= ~BIT1;         // Write signal(WR = 0) for writing on to the LCD.
# define Enable_High P1OUT |=BIT2;  // Enable signal High
# define Enable_Low P1OUT &= ~BIT2; // Enable signal low

unsigned int i,j;

/*
 * Delay function to introduce necessary delay between different data events
 * */
void delay(delay){
    for(i=0; i<delay; i++){
        for(j=0; j<delay;j++){
            asm("nop");

        }
    }
}
/* GPIO initialization
 * Port 1 is configured as output with output levels zero
 */

void GPIO_init(){
   // P1SEL &= 0x00;
    //P2SEL &= 0x00;
    P1DIR |= 0xFF;
    P1OUT &= ~0xFF;
}
/* LCD mode and function initialization
 * LCD always required to be initialized in 8 bit mode before putting into 4 bit operation
 *
 */
void LCD_init(){
    GPIO_init();
    Command_Write(0x33);        // LCD initialized in 8 bit mode DL = 1, N=0, F=0;
    Command_Write(0x32);        // Second try to initialize  lcd in 8 bit mode8 bit mode
    Command_Write(0x28);        // 4 bit mode initialization DL=0, N=1,F=0
    Command_Write(0x0E);        // Clear the screen D(Display) = 1, C(Cursor)=1, B(Blink)=0;
    Command_Write(0x01);        // Clears display and returns cursor to the home position (address 0)
    Command_Write(0x06);        // Entry mode increment cursor(I/D =1), Shift display =0
    Command_Write(0x80);        // Initialize the entry address of Column 1 row 1
}

/*
 *  function to make the Enable pulse transition low-high-low for data write
 *
 */


void Data_Enable(){
    Enable_High;                  // Set the enable signal from low to high
    __delay_cycles(40);           // Delay of 40 microseconds
    Enable_Low;                   // Set the enable signal from high to low

}

/*
 * String write function accept the string characters as arguments and
 * Write them onto specified port
 * */

void String_Write(char *s){
    while(*s){
        Data_Write(*s);
        s++;
    }
}



/*
 * Command write function enable the control signals
 * Write the command characters by splitting the bytes into upper and lower nibbles for 4 bit mode.
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

/* Data write function enable the control signals RS=1, WR=0 and E = LOW-HIGH-LOW
 * Write the command characters by splitting the bytes into upper and lower nibbles for 4 bit mode.
 *
 */
void Data_Write(unsigned char data){
    DWR_RS;
    WR;
    P1OUT = (P1OUT&0x0F)|(data&0xF0);
    Data_Enable();
    P1OUT = (P1OUT&0x0F)|((data<<4)&0xF0);
    Data_Enable();
}






