/*
 * NCN_GPIO.h
 *
 *  Created on: 2015-7-3
 *      Author: Jake
 *
 * nexpaq msp430 module pin map
 */

#ifndef NCN_GPIO_H_
#define NCN_GPIO_H_
#ifdef __cplusplus
	extern "C" {
#endif
typedef enum {
	INPUT = 0x00,
	OUTPUT = 0x01,
	HIGH = 0x01,
	LOW = 0x00
}PIN_MODE;
/*
*******   Pin list    *******
** pin ** Port.pin ****** Mode *******************pin NO.*********
 * 00.		P1.0		ADC							31
 * 01.		P1.6		ADC							21
 * 02.		P1.7		ADC							22
 * 03.		P3.4									14
 * 04.		P3.2		PWM							12
 * 05.		P3.3		PWM							13
 * 06.		P3.5		PWM							18
 * 07.		P3.6		PWM							19
 * 08.		P2.0		UART_TXO					9
 * 09.		P2.1		UART_RDI					10
 * 10.		P2.2		SPI MISO					11
 * 11.		P2.3		SPI_MOSI					15
 * 12.		P2.4		SPI_CLK						16
 * 13.		P2.5		SPI_CS						17
 * 14.		P2.6		I2C_SCL						26
 * 15.		P2.7		I2C_SDA						25
 ********************************************
 */

/*
 * Function:		pinMode
 * Description:		Set the pin as specified mode.
 * Parameters:		1. 	pin (unsigned char)
 * 						range:0~16(Detailed description see the Pin list)
 * 					2	mode (unsigned char)
 * 						1) OUTPUT
 * 						2) INPUT
 * Return:			None
 */
void pinMode(unsigned char pin,unsigned char mode);

/*
 * Function:		digitalWrite
 * Description:		Set the pin as specified output value,need to set the pin mode first.
 * Parameters:		1. 	pin (unsigned char)
 * 						range:0~15(Detailed description see the Pin list)
 * 					2	value (unsigned char)
 * 						1) HIGH
 * 						2) LOW
 * Return:			None
 */
void digitalWrite(unsigned char pin,unsigned char value);

/*
 * Function:		digitalRead
 * Description:		Read the digital value of the pin,need to set the pin mode first.
 * Parameters:		1. 	pin (unsigned char)
 * 						range:0~15(Detailed description see the Pin list)
 * Return:			(unsigned char)		1) HIGH
 * 										2) LOW
 */
unsigned char digitalRead(unsigned char pin);

/*
 * Function:		analogRead
 * Description:		Read the analog value of the pin,need to set the pin mode first.
 * Parameters:		1. 	pin (unsigned char)
 * 						range:0~2 (Detailed description see the Pin list)
 * Return:			(unsigned int)	1) Effective value: 0x0000 ~ 0x03FF (Reference voltage is 3V3 )
 * 									2) Error flag:		0xFFFF
 */
unsigned int analogRead(unsigned char pin);

/*
 * Function:		analogWrite
 * Description:		Read the analog value of the pin,need to set the pin mode first.
 * Parameters:		1. 	pin (unsigned char)
 * 						range:4~7 (Detailed description see the Pin list)
 * 					2.	value(unsigned int)
 * 					1) Effective value: 0x0000 ~ 0x03FF (Reference voltage is 3V3 )
 */
void analogWrite(unsigned char pin,unsigned char value);
/*
 *  * Function:		analogFrequencySet
 * Description:		Set the frequency of the analog write;
 * Parameters:		1. 	pin (unsigned char)
 * 						range:4~7 (Detailed description see the Pin list)
 * 						The 4 and 5 use the same frequency,the 4 and 5 use the same frequency;
 * 					2.	fre(unsigned int)
 * 						1) Effective value: 20Hz~10,000Hz
 */
void analogFrequencySet(unsigned char pin,unsigned int fre);
#ifdef __cplusplus
	}
#endif


#endif /* NCN_GPIO_H_ */
