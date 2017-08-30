/*
 * soft_uart_cpp.cpp
 *
 *  Created on: 2015-7-6
 *      Author: Jake
 */
#include "soft_uart_cpp.h"
#include "msp430.h"
#include "queue.h"
Serial serial;
Serial::Serial(void) {
	config = SERIAL_8N1;
	start_bits = 1;
	stop_bits = 1;
	parity_bits = PARITY_NONE;
	data_bits = 8;
	TxPin = 8;
	RxPin = 9;
}
inline unsigned char Serial::getParityBits(void) {
	return this->parity_bits;
}
void Serial::begin(long speed,unsigned char config,unsigned char TxPin,unsigned char RxPin) {
	this->TxPin = TxPin;
	this->RxPin = RxPin;
	begin(speed,config);
}
void Serial::begin(long speed,unsigned char config) {
	switch(config) {
	case SERIAL_5E1:
		data_bits = 5;
		parity_bits = PARITY_EVEN;
		stop_bits = 1;
		break;
	case SERIAL_5E2:
		data_bits = 5;
		parity_bits = PARITY_EVEN;
		stop_bits = 2;
		break;
	case SERIAL_6E1:
		data_bits = 6;
		parity_bits = PARITY_EVEN;
		stop_bits = 1;
		break;
	case SERIAL_6E2:
		data_bits = 6;
		parity_bits = PARITY_EVEN;
		stop_bits = 2;
		break;
	case SERIAL_7E1:
		data_bits = 7;
		parity_bits = PARITY_EVEN;
		stop_bits = 1;
		break;
	case SERIAL_7E2:
		data_bits = 7;
		parity_bits = PARITY_EVEN;
		stop_bits = 2;
		break;
	case SERIAL_8E1:
		data_bits = 8;
		parity_bits = PARITY_EVEN;
		stop_bits = 1;
		break;
	case SERIAL_8E2:
		data_bits = 8;
		parity_bits = PARITY_EVEN;
		stop_bits = 2;
		break;
	case SERIAL_5O1:
		data_bits = 5;
		parity_bits = PARITY_ODD;
		stop_bits = 1;
		break;
	case SERIAL_5O2:
		data_bits = 5;
		parity_bits = PARITY_ODD;
		stop_bits = 2;
		break;
	case SERIAL_6O1:
		data_bits = 6;
		parity_bits = PARITY_ODD;
		stop_bits = 1;
		break;
	case SERIAL_6O2:
		data_bits = 6;
		parity_bits = PARITY_ODD;
		stop_bits = 2;
		break;
	case SERIAL_7O1:
		data_bits = 7;
		parity_bits = PARITY_ODD;
		stop_bits = 1;
		break;
	case SERIAL_7O2:
		data_bits = 7;
		parity_bits = PARITY_ODD;
		stop_bits = 2;
		break;
	case SERIAL_8O1:
		data_bits = 8;
		parity_bits = PARITY_ODD;
		stop_bits = 1;
		break;
	case SERIAL_8O2:
		data_bits = 8;
		parity_bits = PARITY_ODD;
		stop_bits = 2;
		break;
	case SERIAL_5N1:
		data_bits = 5;
		parity_bits = PARITY_NONE;
		stop_bits = 1;
		break;
	case SERIAL_5N2:
		data_bits = 5;
		parity_bits = PARITY_NONE;
		stop_bits = 2;
		break;
	case SERIAL_6N1:
		data_bits = 6;
		parity_bits = PARITY_NONE;
		stop_bits = 1;
		break;
	case SERIAL_6N2:
		data_bits = 6;
		parity_bits = PARITY_NONE;
		stop_bits = 2;
		break;
	case SERIAL_7N1:
		data_bits = 7;
		parity_bits = PARITY_NONE;
		stop_bits = 1;
		break;
	case SERIAL_7N2:
		data_bits = 7;
		parity_bits = PARITY_NONE;
		stop_bits = 2;
		break;
	case SERIAL_8N1:
		data_bits = 8;
		parity_bits = PARITY_NONE;
		stop_bits = 1;
		break;
	case SERIAL_8N2:
		data_bits = 8;
		parity_bits = PARITY_NONE;
		stop_bits = 2;
		break;
	}
	begin(speed);
}
void Serial::begin(long speed) {
	if(stop_bits == 0x01)
		stop_value = (0x0001 << data_bits) << (!!parity_bits);
	else if(stop_bits == 0x02)
		stop_value = (0x0003 << data_bits) << (!!parity_bits);
	data_value = 0xFF >> (8-data_bits);
	uart_tbit_div_2 = (unsigned int)(SYSTEM_SMCK/(speed *2));
	uart_tbit = (unsigned int)(SYSTEM_SMCK/speed);

    TA1CCTL0 = OUT;                          // Set TXD Idle as Mark = '1'

	switch(RxPin) {
	case 9:
		P2SEL |= BIT1;
		P2DIR &=~BIT1;
		TA1CCTL1 = SCS + CM1 + CAP + CCIE;       // Sync, Neg Edge, Capture, Int
		break;
	case 10:
		P2SEL |= BIT2;
		P2DIR &=~BIT2;
		TA1CCTL1 = SCS + CM1 + CAP + CCIE + CCIS_1;       // Sync, Neg Edge, Capture, Int
		break;
	}
	switch(TxPin){
	case 8:
		P2SEL |= BIT0;
		P2DIR |= BIT0;
		break;
	case 11:
		P2SEL |= BIT3;
		P2DIR |= BIT3;
		break;
	}

    TA1CTL = TASSEL_2 + MC_2;                // SMCLK, start in continuous mode
    __enable_interrupt();
}

void Serial::end(void){
	switch(TxPin){
	case 8:
		P2SEL &=~BIT0;
		break;
	case 11:
		P2SEL &=~BIT3;
		break;
	}
	switch(RxPin) {
	case 9:
		P2SEL &=~BIT1;
		break;
	case 10:
		P2SEL &=~BIT2;
		break;
	case 4:
		P3SEL &=~BIT2;
		break;
	}
	TA1CCTL1 &=~ CCIE;
}
unsigned char Serial::read(void) {
	return rec_fifo.pop();
}
unsigned char Serial::available(void) {
	return rec_fifo.available();
}
int Serial::peak(void) {
	return rec_fifo.peak();
}


void Serial::write(unsigned char byte) {
    while (TA1CCTL0 & CCIE);                 // Ensure last char got TX'd
    txData = byte & data_value;                          // Load global variable
    txData |= stop_value;
    if(parity_bits != PARITY_NONE) {
    	unsigned char parity_result = 0;
    	parity_result = ((0x01 & byte & data_value) == 0x01) + ((0x02 & byte & data_value) == 0x02) + ((0x04 & byte & data_value) == 0x04) + ((0x08 & byte & data_value) == 0x08) +
    			((0x10 & byte & data_value ) == 0x10) + ((0x20 & byte & data_value) == 0x20) + ((0x40 & byte & data_value ) == 0x40) + ((0x80 & byte & data_value) == 0x80);
    	if(parity_result & 0x01) {
    		if(parity_bits == PARITY_EVEN) {
    			txData |= (0x0001 << data_bits);
    		}
    		else {
    			txData &=~(0x0001 << data_bits);
    		}
    	} else {
    		if(parity_bits == PARITY_ODD) {
    			txData |= (0x0001 << data_bits);
    		}
    		else {
    			txData &=~(0x0001 << data_bits);
    		}
    	}

    }
    txData <<= 1;                           // Add space start bit
    TA1CCR0 = TAR;                           // Current state of TA counter
    TA1CCR0 += uart_tbit;                    // One bit time till first bit
    TA1CCTL0 = OUTMOD0 + CCIE;               // Set TXD on EQU0, Int
}
void Serial::write(char *string) {
	while(*string) {
		write(*string++);
	}
}
void Serial::write(unsigned char *buf,unsigned char len) {
	unsigned char i = 0;
	for(i = 0;i < len;i++) {
		write(buf[i]);
	}
}
void Serial::TimerA_UART_tx(unsigned char byte) {

    while (TA1CCTL0 & CCIE);                 // Ensure last char got TX'd
    TA1CCR0 = TAR;                           // Current state of TA counter
    TA1CCR0 += uart_tbit;                    // One bit time till first bit
    TA1CCTL0 = OUTMOD0 + CCIE;               // Set TXD on EQU0, Int
    txData = byte & (0xFF >> (8-data_bits));                          // Load global variable
    if(stop_bits == 0x01)
    	txData |= (0x0001 << data_bits) << (!!parity_bits);
    else if(stop_bits == 0x02)
    	txData |= (0x0003 << data_bits) << (!!parity_bits);		// Add mark stop bit to TXData
    if(parity_bits == PARITY_NONE) {

    } else {
    	unsigned char i = 0;
    	unsigned char parity_result = 0;
    	for(i = 0;i < data_bits;i++)  {
    		if((1 << i) & byte) {
    			parity_result++;
    		}
    	}
    	if(parity_result & 0x01) {
    		if(parity_bits == PARITY_EVEN) {
    			txData |= (0x0001 << data_bits);
    		} else {
    			txData &=~(0x0001 << data_bits);
    		}
    	} else {
    		if(parity_bits == PARITY_ODD) {
    			txData |= (0x0001 << data_bits);
    		} else {
    			txData &=~(0x0001 << data_bits);
    		}
    	}
    }
    txData <<= 1;                           // Add space start bit
}

void Serial::TimerA_UART_print(char *string) {
    while (*string) {
        TimerA_UART_tx(*string++);
    }
}

int Serial::print(char *string) {
	int i = 0;
    while (*string) {
        TimerA_UART_tx(*string++);
        i++;
    }
    return i;
}
int Serial::print(char c) {
	TimerA_UART_tx(c);
	return sizeof(char);
}
int Serial::print(unsigned char *string) {
	int i = 0;
	while(*string) {
		TimerA_UART_tx(*string++);
		i++;
	}
	return i;
}
int Serial::print(int dat) {
	int temp = dat;
	char result[6] = {0};
	char i = 0;
	char j =0;
	if(dat >= 0)
		temp = dat;
	else {
		TimerA_UART_tx('-');
		temp = 0-dat;
		j = 1;
	}
	do{
		result[i++] = temp % 10;
		temp = temp / 10;
	}while(temp != 0);
	j = i;
	i--;
	while(i > 0) {
		TimerA_UART_tx(result[i--] + '0');
	}
	TimerA_UART_tx(result[0] + '0');
	return j;
}
void Serial::print(unsigned char dat,unsigned char format) {
	unsigned char temp = 0;
	switch (format) {
	case BIN:
		temp = (dat >> 7) & 0x01;
		TimerA_UART_tx(temp + '0');
		temp = (dat >> 6) & 0x01;
		TimerA_UART_tx(temp + '0');
		temp = (dat >> 5) & 0x01;
		TimerA_UART_tx(temp + '0');
		temp = (dat >> 4) & 0x01;
		TimerA_UART_tx(temp + '0');
		temp = (dat >> 3) & 0x01;
		TimerA_UART_tx(temp + '0');
		temp = (dat >> 2) & 0x01;
		TimerA_UART_tx(temp + '0');
		temp = (dat >> 1) & 0x01;
		TimerA_UART_tx(temp + '0');
		temp = (dat >> 0) & 0x01;
		break;
	case OCT:
		temp = (dat >> 6) & 0x07;
		TimerA_UART_tx(temp + '0');
		temp = (dat >> 3) & 0x07;
		TimerA_UART_tx(temp + '0');
		temp = (dat >> 0) & 0x07;
		TimerA_UART_tx(temp + '0');
		break;
	case HEX:
		temp = (dat >> 4) & 0x0F;
		if(temp < 0x0A)
			TimerA_UART_tx(temp + '0');
		else
			TimerA_UART_tx(temp - 0x0A + 'A');
		temp = (dat >> 0) & 0x0F;
		if(temp < 0x0A)
			TimerA_UART_tx(temp + '0');
		else
			TimerA_UART_tx(temp - 0x0A + 'A');
		break;
	case DEC:
		temp = dat;
		if(temp > 99) {
			TimerA_UART_tx(temp/100 + '0');
			TimerA_UART_tx((temp%100)/10 + '0');
			TimerA_UART_tx(temp%10 + '0');
		} else if(temp > 9){
			TimerA_UART_tx(temp/10 + '0');
			TimerA_UART_tx(temp%10 + '0');
		} else {
			TimerA_UART_tx(temp%10 + '0');
		}
		break;
	}
}
void Serial::println(unsigned char dat,unsigned char format) {
	unsigned char temp = 0;
	switch (format) {
	case BIN:
		temp = (dat >> 7) & 0x01;
		TimerA_UART_tx(temp + '0');
		temp = (dat >> 6) & 0x01;
		TimerA_UART_tx(temp + '0');
		temp = (dat >> 5) & 0x01;
		TimerA_UART_tx(temp + '0');
		temp = (dat >> 4) & 0x01;
		TimerA_UART_tx(temp + '0');
		temp = (dat >> 3) & 0x01;
		TimerA_UART_tx(temp + '0');
		temp = (dat >> 2) & 0x01;
		TimerA_UART_tx(temp + '0');
		temp = (dat >> 1) & 0x01;
		TimerA_UART_tx(temp + '0');
		temp = (dat >> 0) & 0x01;
		break;
	case OCT:
		temp = (dat >> 6) & 0x07;
		TimerA_UART_tx(temp + '0');
		temp = (dat >> 3) & 0x07;
		TimerA_UART_tx(temp + '0');
		temp = (dat >> 0) & 0x07;
		TimerA_UART_tx(temp + '0');
		break;
	case HEX:
		temp = (dat >> 4) & 0x0F;
		if(temp < 0x0A)
			TimerA_UART_tx(temp + '0');
		else
			TimerA_UART_tx(temp - 0x0A + 'A');
		temp = (dat >> 0) & 0x0F;
		if(temp < 0x0A)
			TimerA_UART_tx(temp + '0');
		else
			TimerA_UART_tx(temp - 0x0A + 'A');
		break;
	case DEC:
		temp = dat;
		if(temp > 99) {
			TimerA_UART_tx(temp/100 + '0');
			TimerA_UART_tx((temp%100)/10 + '0');
			TimerA_UART_tx(temp%10 + '0');
		} else if(temp > 9){
			TimerA_UART_tx(temp/10 + '0');
			TimerA_UART_tx(temp%10 + '0');
		} else {
			TimerA_UART_tx(temp%10 + '0');
		}
		break;
	}
    TimerA_UART_tx('\r');
    TimerA_UART_tx('\n');
}
int Serial::println(char *string) {
	int i = 0;
    while (*string) {
        TimerA_UART_tx(*string++);
        i++;
    }
    TimerA_UART_tx('\r');
    TimerA_UART_tx('\n');
    return i;
}
int Serial::println(char c) {
	TimerA_UART_tx(c);
    TimerA_UART_tx('\r');
    TimerA_UART_tx('\n');
	return sizeof(char) + 2 ;
}
int Serial::println(unsigned char *string) {
	int i = 0;
	while(*string) {
		TimerA_UART_tx(*string++);
		i++;
	}
    TimerA_UART_tx('\r');
    TimerA_UART_tx('\n');
	return i + 2;
}
int Serial::println(int dat) {
	int temp = dat;
	char result[6] = {0};
	char i = 0;
	char j =0;
	if(dat >= 0)
		temp = dat;
	else {
		TimerA_UART_tx('-');
		temp = 0-dat;
		j = 1;
	}
	do{
		result[i++] = temp % 10;
		temp = temp / 10;
	}while(temp != 0);
	j += i;
	i--;
	while(i > 0) {
		TimerA_UART_tx(result[i--] + '0');
	}
	TimerA_UART_tx(result[0] + '0');
    TimerA_UART_tx('\r');
    TimerA_UART_tx('\n');
	return j + 2;
}
//int Serial::print(float dat) {
//	long temp = (long)dat;
//	long temp1 = temp;
//	char result[20] = {0};
//	char i = 0;
//	char j =0;
//	do{
//		result[i++] = temp % 10;
//		temp = temp / 10;
//	}while(temp != 0);
//	j = i;
//	i--;
//	while(i > 0) {
//		TimerA_UART_tx(result[i--] + '0');
//	}
//	TimerA_UART_tx(result[0] + '0');
//	TimerA_UART_tx('1');
//	float f_t = dat - (float)temp1;
//	f_t = f_t * 100;
//	result[j++] = ((int)f_t / 10) + '0';
//	result[j++] = ((int)f_t % 10) + '0';
//	return j;
//}







void Serial::_Timer_A1_ISR_(void) {
	static unsigned char txBitCnt = start_bits + data_bits + (!!parity_bits) + stop_bits;		//发送10个字节。。1开始8字节无校验1停止
	TA1CCR0 += uart_tbit;                    // Add Offset to CCRx
	if (txBitCnt == 0) {                    // All bits TXed?
		TA1CCTL0 &= ~CCIE;                   // All bits TXed, disable interrupt
		txBitCnt = start_bits + data_bits + (!!parity_bits) + stop_bits;                      // Re-load bit counter
	} else {
		if (txData & 0x01) {
			TA1CCTL0 &= ~OUTMOD2;              // TX Mark '1'
		} else {
			TA1CCTL0 |= OUTMOD2;               // TX Space '0'
		}
		txData >>= 1;
		txBitCnt--;
	}
}
unsigned char Serial::_Timer_A1_ISR_NONE(void) {
	static unsigned char rxBitCnt = data_bits;			//接收8字节
	static unsigned char rxData = 0;
	TA1CCR1 += uart_tbit;                 // Add Offset to CCRx
	if (TA1CCTL1 & CAP) {                 // Capture mode = start bit edge
		TA1CCTL1 &= ~CAP;                 // Switch capture to compare mode
		TA1CCR1 += uart_tbit_div_2;       // Point CCRx to middle of D0
		return 0;
	} else {
		rxData >>= 1;
		if (TA1CCTL1 & SCCI) {            // Get bit waiting in receive latch
			rxData |= 0x80;
		}
		rxBitCnt--;
		if (rxBitCnt == 0) {             // All bits RXed?
			rec_fifo.push(rxData);
			rxBitCnt = data_bits;                // Re-load bit counter
			TA1CCTL1 |= CAP;              // Switch compare to capture mode
			return 1;
		}
		return 0;
	}
}
unsigned char Serial::_Timer_A1_ISR_ODD(void) {
	static unsigned char rxBitCnt = data_bits + 1;			//接收8字节
	static unsigned char rxData = 0;
	TA1CCR1 += uart_tbit;                 // Add Offset to CCRx
	if (TA1CCTL1 & CAP) {                 // Capture mode = start bit edge
		TA1CCTL1 &= ~CAP;                 // Switch capture to compare mode
		TA1CCR1 += uart_tbit_div_2;       // Point CCRx to middle of D0
	} else if(rxBitCnt > 1){
		rxData >>= 1;
		if (TA1CCTL1 & SCCI) {            // Get bit waiting in receive latch
			rxData |= (0x01 << (data_bits - 1));
		}
		rxBitCnt--;
	} else {
		unsigned char parity_result = 0x00;
		parity_result = ((0x01 & rxData & data_value) == 0x01)
				+ ((0x02 & rxData & data_value) == 0x02)
				+ ((0x04 & rxData & data_value) == 0x04)
				+ ((0x08 & rxData & data_value) == 0x08)
				+ ((0x10 & rxData & data_value) == 0x10)
				+ ((0x20 & rxData & data_value) == 0x20)
				+ ((0x40 & rxData & data_value) == 0x40)
				+ ((0x80 & rxData & data_value) == 0x80)
				+ ((TA1CCTL1 & SCCI) != 0x00);
		if(parity_result & 0x01) {
			rec_fifo.push(rxData);
			rxBitCnt = data_bits+1;                // Re-load bit counter
			TA1CCTL1 |= CAP;              // Switch compare to capture mode
			return 1;
		}
	}
	return 0;
}
unsigned char Serial::_Timer_A1_ISR_EVEN(void) {
	static unsigned char rxBitCnt = data_bits + 1;			//接收8字节
	static unsigned char rxData = 0;

	TA1CCR1 += uart_tbit;                 // Add Offset to CCRx
	if (TA1CCTL1 & CAP) {                 // Capture mode = start bit edge
		TA1CCTL1 &= ~CAP;                 // Switch capture to compare mode
		TA1CCR1 += uart_tbit_div_2;       // Point CCRx to middle of D0
	} else if(rxBitCnt > 1){
		rxData >>= 1;
		if (TA1CCTL1 & SCCI) {            // Get bit waiting in receive latch
			rxData |= (0x01 << (data_bits - 1));
		}
		rxBitCnt--;
	} else {
		unsigned char parity_result = 0x01;
		parity_result = ((0x01 & rxData & data_value) == 0x01)
				+ ((0x02 & rxData & data_value) == 0x02)
				+ ((0x04 & rxData & data_value) == 0x04)
				+ ((0x08 & rxData & data_value) == 0x08)
				+ ((0x10 & rxData & data_value) == 0x10)
				+ ((0x20 & rxData & data_value) == 0x20)
				+ ((0x40 & rxData & data_value) == 0x40)
				+ ((0x80 & rxData & data_value) == 0x80)
				+ ((TA1CCTL1 & SCCI) != 0x00);

		if((parity_result & 0x01) == 0x00) {
			rec_fifo.push(rxData);
			rxBitCnt = data_bits+1;                // Re-load bit counter
			TA1CCTL1 |= CAP;              // Switch compare to capture mode
		}
		return 1;
	}
	return 0;
}
//------------------------------------------------------------------------------
// Timer_A UART - Transmit Interrupt Handler
//------------------------------------------------------------------------------
extern "C" {
#pragma vector = TIMER1_A0_VECTOR
__interrupt void Timer_A0_ISR(void) {
	serial._Timer_A1_ISR_();
}
//------------------------------------------------------------------------------
// Timer_A UART - Receive Interrupt Handler
//------------------------------------------------------------------------------
#pragma vector = TIMER1_A1_VECTOR
__interrupt void Timer_A1_ISR(void)
{
	_no_operation();
    switch (__even_in_range(TA1IV, TA1IV_TAIFG)) { // Use calculated branching
        case TA1IV_TACCR1:                        // TACCR1 CCIFG - UART RX
        	if(serial.getParityBits() == PARITY_NONE)
        		if(serial._Timer_A1_ISR_NONE())
        			__bic_SR_register_on_exit(LPM0_bits);  // Clear LPM0 bits from 0(SR)
        	if(serial.getParityBits() == PARITY_ODD)
        		if(serial._Timer_A1_ISR_ODD())
        			__bic_SR_register_on_exit(LPM0_bits);  // Clear LPM0 bits from 0(SR)
        	if(serial.getParityBits() == PARITY_EVEN)
        		if(serial._Timer_A1_ISR_EVEN())
        			__bic_SR_register_on_exit(LPM0_bits);  // Clear LPM0 bits from 0(SR)
            break;
    }
}
}
//------------------------------------------------------------------------------

