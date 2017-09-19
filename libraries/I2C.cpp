/*
 * I2C.cpp
 *
 *  Created on: 2017-9-07
 *      Author: Alan.Lin
 */
#include "I2C.h"
#include "msp430.h"

#define	IIC_TIMER_OUT		22000//22000
unsigned char IICFinishflag  = 0x01;
unsigned int IICTimerOutCnt = 0x00;

static unsigned char TxByteCtr,RxByteCtr;
static unsigned char TxBuf[16];
static unsigned char RxBuf[16];
static unsigned char stop_flag = 1;

I2C_class I2C;
inline void I2C_class::I2C_WriteMode(void){
	UCB0CTL1 |= UCTR;
	IFG2 &=~ UCB0TXIFG;
	IE2 &=~ UCB0RXIE;
	IE2 |= UCB0TXIE;
}
inline void I2C_class::I2C_ReadMode(void){
	UCB0CTL1 &=~ UCTR;
	IFG2 &=~ UCB0RXIFG;
	IE2 &=~ UCB0TXIE;
	IE2 |= UCB0RXIE;                                // 关闭发送中断，开启接收中断
}
void I2C_class::begin(void){
	P1SEL |= BIT6 + BIT7;                     // Assign I2C pins to USCI_B0
	P1SEL2|= BIT6 + BIT7;                     // Assign I2C pins to USCI_B0
	UCB0CTL1 |= UCSWRST;                      // Enable SW reset
	UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC;     // I2C Master, synchronous mode
	UCB0CTL1 = UCSSEL_2 + UCSWRST;            // Use SMCLK, keep SW reset
	UCB0BR0 = 80;                             // fSCL = SMCLK/12 = ~100kHz
	UCB0BR1 = 0;
	UCB0CTL1 &= ~UCSWRST;                     // Clear SW reset, resume operation
}
void I2C_class::begin(unsigned char slave_address){
	P1SEL |= BIT6 + BIT7;                     // Assign I2C pins to USCI_B0
	P1SEL2|= BIT6 + BIT7;                     // Assign I2C pins to USCI_B0
	UCB0CTL1 |= UCSWRST;                      // Enable SW reset
	UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC;     // I2C Master, synchronous mode
	UCB0CTL1 = UCSSEL_2 + UCSWRST;            // Use SMCLK, keep SW reset
	UCB0BR0 = 80;                             // fSCL = SMCLK/12 = ~100kHz
	UCB0BR1 = 0;
	UCB0I2CSA = slave_address;
	UCB0CTL1 &= ~UCSWRST;                     // Clear SW reset, resume operation
}
void I2C_class::change_Slave(unsigned char add){
	UCB0I2CSA = add;
}
void I2C_class::I2C_Tx(unsigned char Reg,unsigned char data[],unsigned char len){
	unsigned char i = 0;

	stop_flag = 0;
	IICTimerOutCnt = 0x00;
	while( (UCB0STAT & UCBBUSY) && (IICTimerOutCnt ++ <= IIC_TIMER_OUT));
	IICTimerOutCnt = 0;
	I2C_WriteMode();
	TxBuf[len]=Reg;
	for(i = 0;i < len;i ++){
		TxBuf[len-1-i] = data[i];
	}
	TxByteCtr=len+1;                       	// Load TX byte counter
	IICFinishflag = 0x00;
	UCB0CTL1 |= UCTR + UCTXSTT;                 // I2C TX, start condition
	stop_flag = 1;

	while((IICFinishflag == 0x00) && (IICTimerOutCnt ++ <= IIC_TIMER_OUT)){	//  while (UCB0CTL1 & UCTXSTT);
	}
	IICTimerOutCnt = 0x00;

	while ((UCB0CTL1 & UCTXSTP) && (IICTimerOutCnt ++ <= IIC_TIMER_OUT));
	IICTimerOutCnt = 0;
}
void I2C_class::I2C_Rx(unsigned char Reg,unsigned char data[],unsigned char len){
	unsigned char i = 0;
	I2C_WriteMode();							// Mode to write command
	TxBuf[0]=Reg;							// Address will be read
	TxByteCtr=1;								// Load TX byte counter
	IICFinishflag = 0x00;
	while ((UCB0CTL1 & UCTXSTP) && (IICTimerOutCnt ++ <= IIC_TIMER_OUT));
	IICTimerOutCnt = 0;
	UCB0CTL1 |= UCTR + UCTXSTT ;    			// I2C TX, start condition

	while((IICFinishflag == 0x00) && (IICTimerOutCnt ++ <= IIC_TIMER_OUT)){

	}
	IICTimerOutCnt = 0x00;

	while ((UCB0CTL1 & UCTXSTP) && (IICTimerOutCnt ++ <= IIC_TIMER_OUT));// Wait for stop bit,generated after send finish
	IICTimerOutCnt = 0;
	I2C_ReadMode();								// Mode to read data
	UCB0CTL1 |= UCTXSTT;						// Start bit
	while((UCB0CTL1 & UCTXSTT) && (IICTimerOutCnt ++ <= IIC_TIMER_OUT));
	IICTimerOutCnt = 0;
	if(len == 1){							// Set stop register before the last byte is sent
		UCB0CTL1 |= UCTXSTP;
	}
	RxByteCtr = len;							// Load RX byte counter

	IICFinishflag = 0x00;
	while((IICFinishflag == 0x00) && (IICTimerOutCnt ++ <= IIC_TIMER_OUT)){
	}
	IICTimerOutCnt = 0x00;
	while ((IFG2 & UCB0RXIFG) && (IICTimerOutCnt ++ <= IIC_TIMER_OUT));// Receive finish
	IICTimerOutCnt = 0;
	while ((UCB0CTL1 & UCTXSTP) && (IICTimerOutCnt ++ <= IIC_TIMER_OUT));// Receive the stop bit
	IICTimerOutCnt = 0;
	for(i = 0;i < len;i++){					// Read the data from the buffer and transpose bytes
		data[len-1-i] = RxBuf[i];
	}
}

#pragma vector = USCIAB0TX_VECTOR
__interrupt void USCIAB0TX_ISR(void)
{
	if ( IFG2 & UCB0TXIFG )
	{
		if (TxByteCtr)                            	// Check TX byte counter
		{
			TxByteCtr--;
			UCB0TXBUF =TxBuf[TxByteCtr];     		// Load TX buffer                               // Decrement TX byte counter
		}
		else
		{
			if(stop_flag == 1){
				UCB0CTL1 |= UCTXSTP;       			// I2C stop condition
			}
			IFG2 &= ~UCB0TXIFG;                     // Clear USCI_B0 TX int flag
			IE2 &=~UCB0TXIE;
			IICFinishflag = 0x01;
		}
	}
	if ( IFG2 & UCB0RXIFG )
    {

		  RxByteCtr--;                              // Decrement RX byte counter
		  if (RxByteCtr)
		  {
			  RxBuf[RxByteCtr] = UCB0RXBUF; 		// Move RX data to address PRxData
			  if (RxByteCtr == 1){              		// Only one byte left?
				  UCB0CTL1 |= UCTXSTP;          	// Generate I2C stop condition
			  }
		  }
		  else
		  {
			  RxBuf[RxByteCtr] = UCB0RXBUF;    		// Move final RX data to PRxData
			  IICFinishflag = 0x01;
		  }
    }
}
