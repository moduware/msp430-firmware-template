/*
 * gpio.h
 *
 *  Created on: Nov 15, 2017
 *      Author: IBM
 */

#ifndef GPIO_H_
#define GPIO_H_

void GPIO_init();
void LCD_init();
void delay(int);
void Command_Write(unsigned char cmd);
void Data_Write(unsigned char data);
void Data_Enable();
void String_Write(char *s);

#endif /* GPIO_H_ */
