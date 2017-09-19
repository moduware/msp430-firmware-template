/*
 * LiquidCrystal.h
 *
 *  Created on: 2015-8-14
 *      Author: coody
 */

#ifndef LIQUIDCRYSTAL_H_
#define LIQUIDCRYSTAL_H_
#ifdef __cplusplus
extern "C" {
#endif
void LCD_Init(void);
void LCD_Clear(void);
void LCD_SetCursor(unsigned char col, unsigned char row);
void LCD_Write_String(const unsigned char *str);
void LCD_Write_Byte(unsigned char *data, unsigned char len);
void LCD_Command_write(unsigned char cmd);
void LCD_Data_write(unsigned char data);

void delay(unsigned int ms);
#ifdef __cplusplus
}
#endif
#endif /* LIQUIDCRYSTAL_H_ */
