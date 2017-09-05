#include <msp430.h>
#include "NCN_GPIO.h"
/*
 * NCN_GPIO.c
 *
 *  Created on: 2015-6-30
 *      Author: Jake
 *
 *nexpaq msp430 module pin map
 */

const unsigned char pin_list [] = {
		BIT0,BIT6,BIT7,								//P1
		BIT4,BIT2,BIT3,BIT5,BIT6,					//P3
		BIT0,BIT1,BIT2,BIT3,BIT4,BIT5,BIT6,BIT7,	//P2

};
static unsigned int pwm_clk0 = 99;
static unsigned int pwm_clk1 = 99;
static unsigned char pin_adc[3] = {0x00};
/*
*******   Pin list    *******
** pin ** Port.pin ****** Mode **************
 * 00.		P1.0		ADC							31
 * 01.		P1.6		ADC							21
 * 02.		P1.7		ADC							22
 * 03.		P3.4									14
 * 04.		P3.2		PWM							12
 * 05.		P3.3		PWM							13
 * 06.		P3.5									18
 * 07.		P3.6									19
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
void pinMode(unsigned char pin,unsigned char mode) {
	if(pin >= 16)
		return;
	else if(pin > 7) {				//P2
		P2SEL &=~pin_list[pin];
		P2SEL2 &=~pin_list[pin];
		mode == OUTPUT ? (P2DIR |= pin_list[pin]) : (P2DIR &=~pin_list[pin]);
	} else if(pin >= 4) {
		P3SEL &=~ pin_list[pin];
		mode == OUTPUT ? (P3DIR |= pin_list[pin]) : (P3DIR &=~pin_list[pin]);
	}
	else if(pin > 2) {		//P3
		mode == OUTPUT ? (P3DIR |= pin_list[pin]) : (P3DIR &=~pin_list[pin]);
	} else {
		if(mode == INPUT) {
			pin_adc[pin] = 0x01;
			P1DIR &=~pin_list[pin];
		} else {
			pin_adc[pin] = 0x00;
			P1DIR |= pin_list[pin];
		}
	}
}

void digitalWrite(unsigned char pin,unsigned char value) {
	if(pin >= 16)
		return;
	else if(pin > 7) {		//P2
		value == HIGH ? (P2OUT |= pin_list[pin]) : (P2OUT &=~pin_list[pin]);
	} else if(pin >= 4) {
		P3SEL &=~ pin_list[pin];
		value == HIGH ? (P3OUT |= pin_list[pin]) : (P3OUT &=~pin_list[pin]);
	}
	else if(pin > 2) {	//P3
		value == HIGH ? (P3OUT |= pin_list[pin]) : (P3OUT &=~pin_list[pin]);
	} else {
		ADC10AE0 &= ~pin_list[pin];
		value == HIGH ? (P1OUT |= pin_list[pin]) : (P1OUT &=~pin_list[pin]);
	}
}

unsigned char digitalRead(unsigned char pin) {
	if(pin >= 16)
		return 0xFF;
	else if(pin > 7) {
		if(P2IN & pin_list[pin])
			return HIGH;
		else
			return LOW;
	} else if (pin >= 4) {
		P3SEL &=~ pin_list[pin];
		if(P3IN & pin_list[pin])
			return HIGH;
		else
			return LOW;
	}
	else if(pin > 2) {
		if(P3IN & pin_list[pin])
			return HIGH;
		else
			return LOW;
	} else {
		ADC10AE0 &= ~pin_list[pin];
		if(P1IN & pin_list[pin])
			return HIGH;
		else
			return LOW;
	}
}

unsigned int analogRead(unsigned char pin) {
	unsigned char channel = 0xFF;
	if(pin > 2)
		return 0xFFFF;
	if(pin_adc[pin] == 0x00)
		return 0xFFFF;
	else if(pin == 0)
		channel = 0;
	else if(pin == 1)
		channel = 6;
	else if(pin == 2)
		channel = 7;
	ADC10CTL0 = ADC10SHT_2 + ADC10ON;
	ADC10CTL1 = (short int) channel << 12;                // input A1
	ADC10AE0 |= 0x01 << channel;                       // PA.1 ADC option select
	ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion start
	while (!(ADC10CTL0 & ADC10IFG))
		;
	return ADC10MEM;
}
void analogFrequencySet(unsigned char pin,unsigned int fre) {
	switch(pin) {
	case 4:
	case 5:
		if(fre >=20 && fre <= 10000)
			pwm_clk1 = (2000000/fre)-1;

		break;
	case 6:
	case 7:
		if(fre >=20 && fre <= 10000)
			pwm_clk0 = (2000000/fre)-1;
		break;
	}
}

void analogWrite(unsigned char pin,unsigned char value) {
	switch(pin) {
	case 4:
		P3DIR |= BIT2;
		P3SEL |= BIT2;
		TA1CCR0 = pwm_clk1;
		TA1CCTL1 = OUTMOD_7;
		TA1CCR1 = ((pwm_clk1 + 1)/100 ) * value;
		TA1CTL = TASSEL_2 + ID_3 + MC_1;
		break;
	case 5:
		P3DIR |= BIT3;
		P3SEL |= BIT3;
		TA1CCR0 = pwm_clk1;
		TA1CCTL2 = OUTMOD_7;
		TA1CCR2 = ((pwm_clk1 + 1)/100 ) * value;
		TA1CTL = TASSEL_2 + ID_3 + MC_1;
		break;
	case 6:
		P3DIR |= BIT5;
		P3SEL |= BIT5;
		TA0CCR0 = pwm_clk0;
		TA0CCTL1 = OUTMOD_7;
		TA0CCR1 = ((pwm_clk0 + 1)/100 ) * value;
		TA0CTL = TASSEL_2 + ID_3 + MC_1;
		break;
	case 7:
		P3DIR |= BIT6;
		P3SEL |= BIT6;
		TA0CCR0 = pwm_clk0;
		TA0CCTL2 = OUTMOD_7;
		TA0CCR2 = ((pwm_clk0 + 1)/100 ) * value;
		TA0CTL = TASSEL_2 + ID_3 + MC_1;
		break;
	}
}

