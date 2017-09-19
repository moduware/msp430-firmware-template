/*
 * HC_SR04.cpp
 *
 *  Created on: 24/06/2016
 *      Author: MSJ
 *
 *  HC_SR04 driver
 */
#include <np_module_mdk_v1.h>
#include "NCN_GPIO.h"
#include "HC_SR04.h"
#include "msp430.h"

unsigned int index = 0;
unsigned int finish_measurament = 0;
short unsigned T1 = 0;
short unsigned T2 = 0;
short unsigned ClockTime = 0;

HC_SR04_class  US_s;

void HC_SR04_class::Initialitzation(void){


	WDTCTL = WDTPW +WDTHOLD;				// Stop Watchdog Timer
	BCSCTL1 = CALBC1_16MHZ;					// Basic Clock System Control 1
	DCOCTL = CALBC1_16MHZ;					// DCO Clock Frequency Control
	_BIS_SR(LPM0 + GIE);  					// Interrupt enable

	P1DIR |= 0;								// P1.x reset
	P1DIR |= 0x01;                          // P1.0 output

	P2DIR |= 0;								// P2.x reset
	P2DIR &= ~BIT0;                         // P2.0/TA0.1 Input Capture
	P2SEL |= BIT0;                          // TA0.1 option select

}

void HC_SR04_class::Trigger(void){

	index = 0;
	T1 = 0;
	T2 = 0;
	finish_measurament = 0;

	P1OUT |= BIT0;					// P1.0 HIGH
	__delay_cycles(160);			// wait 10us
	P1OUT &= ~BIT0;					// P1.0 LOW

	Echo();
	delay(10);
}

inline void HC_SR04_class::Echo(void) {

	// Timer1_A3 Capture/Compare Control 0 = pos.edge, input.CCIxX, capture mode, interrupt enable
	TA1CCTL0 = CM_3 + CCIS_0 + CAP +  CCIE;

	// Timer1_A3 Control = SMCLK, Timer A input divider: 0 , continuousMode, Timer A counter clear
	TA1CTL |= TASSEL_2 + ID_0 + MC_2 + TACLR;

}

// Timer1_A0 interrupt service routine
#pragma vector=TIMER1_A0_VECTOR
__interrupt void Timer1_A0 (void){

	if (index == 0) {

		T1 = TA1CCR0;					//1st capture SMCLK value
		index = 1;

	} else if (index == 1){

		T2 = TA1CCR0;					//2nd capture SMCLK value
		ClockTime = (T2 - T1)/16;		//Total wide echo signal
		finish_measurament = 1;

	}
}
