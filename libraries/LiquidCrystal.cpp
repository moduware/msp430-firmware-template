/*
 * LiquidCrystal.cpp
 *
 *  Created on: 2015-8-14
 *      Author: coody
 */
#include "LiquidCrystal.h"
#include "I2C.h"

void delay(unsigned int ms) {
	for (; ms > 0; ms-- ) {
		__delay_cycles(8000);
	}
}
unsigned char m_data = 0x4E;
void LCD_Init(void) {
	I2C.begin(0x27);
	delay(50);
    LCD_Command_write(0x30);	// 4-Bit Mode
	delay(5);
	LCD_Command_write(0x30);	// 4-Bit Mode
	delay(5);
	LCD_Command_write(0x30);	// 4-Bit Mode
	LCD_Command_write(0x20);	// Set 4-Bit interface
	// set lines, font size, etc.
	LCD_Command_write(0x80);	// LCD_FUNCTIONSET(0x20)
	LCD_Command_write(0x80);	// LCD_2LINE(0x08)
	// display on
	LCD_Command_write(0x00);	// LCD_DISPLAYON(0x04)|LCD_CURSOROFF(0x00)|LCD_BLINKOFF(0x00)|LCD_DISPLAYCONTROL(0x08)
	LCD_Command_write(0xC0);	//
	// Clear
	LCD_Clear();
	delay(2);
	// Set the entry mode
	LCD_Command_write(0x00);	// LCD_ENTRYLEFT(0x02)|LCD_ENTRYSHIFTDECREMENT(0x00)|LCD_ENTRYMODESET(0x04)
	LCD_Command_write(0x60);	//
	// home
	LCD_Command_write(0x00);	// LCD_RETURNHOME(0x02)
	LCD_Command_write(0x20);	//
	delay(2);
}

void LCD_Clear(void) {
	LCD_Command_write(0x00);	// LCD_CLEARDISPLAY(0x01)
	LCD_Command_write(0x10);	//
	delay(2);
}

void LCD_SetCursor(unsigned char col, unsigned char row) {
	unsigned char row_offsets[] = {0x00, 0x40, 0x14, 0x54};
	unsigned char lcdaddr = 0x80;

	if ( row > 2 ) {
		row = 1;
	}
	lcdaddr = lcdaddr|(col+row_offsets[row]);

	I2C.I2C_Tx(m_data, 0x08|(lcdaddr&0xf0), 1);
	I2C.I2C_Tx(m_data, 0x0C|(lcdaddr&0xf0), 1);
	I2C.I2C_Tx(m_data, 0x08|(lcdaddr&0xf0), 1);

	I2C.I2C_Tx(m_data, 0x08|((lcdaddr&0x0f)<<4), 1);
	I2C.I2C_Tx(m_data, 0x0C|((lcdaddr&0x0f)<<4), 1);
	I2C.I2C_Tx(m_data, 0x08|((lcdaddr&0x0f)<<4), 1);
}

void LCD_Write_String(const unsigned char *str) {
	I2C.I2C_Tx(m_data, 0x08, 1);

	while (*str) {
		LCD_Data_write((*str)&0xf0);
		LCD_Data_write((*str&0x0f)<<4);
		*str++;
	}
	delay(1);
}

void LCD_Write_Byte(unsigned char *data, unsigned char len) {
	I2C.I2C_Tx(m_data, 0x08, 1);

	for (; len >0; len-- ) {
		LCD_Data_write((*data)&0xf0);
		LCD_Data_write((*data&0x0f)<<4);
		*data++;
	}
	delay(1);
}

void LCD_Command_write(unsigned char cmd) {
	I2C.I2C_Tx(m_data, (0x00|cmd), 1);
	I2C.I2C_Tx(m_data, (0x04|cmd), 1);
	I2C.I2C_Tx(m_data, (0x00|cmd), 1);
    __delay_cycles(800);
}

void LCD_Data_write(unsigned char data) {
	I2C.I2C_Tx(m_data, (0x09|data), 1);
	I2C.I2C_Tx(m_data, (0x0D|data), 1);
	I2C.I2C_Tx(m_data, (0x09|data), 1);
	__delay_cycles(800);
}
