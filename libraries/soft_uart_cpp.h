/*
 * soft_uart_cpp.h
 *
 *  Created on: 2015-7-6
 *      Author: Jake
 */
#include "queue.h"
#ifndef SOFT_UART_CPP_H_
#define SOFT_UART_CPP_H_
#define SYSTEM_SMCK			 16000000


#define BIN	1
#define OCT	2
#define DEC	3
#define HEX	4

typedef enum {
	SERIAL_5N1,
	SERIAL_6N1,
	SERIAL_7N1,
	SERIAL_8N1,
	SERIAL_5N2,
	SERIAL_6N2,
	SERIAL_7N2,
	SERIAL_8N2,
	SERIAL_5E1,
	SERIAL_6E1,
	SERIAL_7E1,
	SERIAL_8E1,
	SERIAL_5E2,
	SERIAL_6E2,
	SERIAL_7E2,
	SERIAL_8E2,
	SERIAL_5O1,
	SERIAL_6O1,
	SERIAL_7O1,
	SERIAL_8O1,
	SERIAL_5O2,
	SERIAL_6O2,
	SERIAL_7O2,
	SERIAL_8O2
}SERIAL_VALUES;
typedef enum {
	PARITY_NONE = 0,
	PARITY_ODD,		//奇校验
	PARITY_EVEN		//偶校验
}PARITY_VALUES;
class Serial {
private:
	unsigned char RxPin;
	unsigned char TxPin;
	unsigned char data_value;
	unsigned int  stop_value;
	unsigned char start_bits;
	unsigned char stop_bits;
	unsigned char data_bits;
	unsigned char config;
	unsigned int uart_tbit_div_2;
	unsigned int uart_tbit;
	unsigned int txData;                        // UART internal variable for TX
	unsigned char rxBuffer;                     // Received UART character
	queue rec_fifo;
	void TimerA_UART_tx(unsigned char byte);
	void TimerA_UART_print(char *string);

public:
	unsigned char parity_bits;
	Serial(void);
	/*
	 * Function:		begin
	 * Description:		Initial the Uart Communication
	 * Parameters:		1. 	speed 	(long)
	 * 						The speed of baud rate,the max number can work is 38400
	 * 					2.	config 	(unsigned char)
	 * 						The configuration for setting the Data bits(5,6,7,8),Parity(None,Odd,Even),Stop bits(1,2).
	 * 						Details see the enum type SERIAL_VAULES.
	 * Return:			None
	 */
	void begin(long speed,unsigned char config);
	/*
	 * Function:		begin
	 * Description:		Initial the Uart Communication,the config is the default value:8N1
	 * Parameters:		1. 	speed 	(long)
	 * 						The speed of baud rate,the max number can work is 38400
	 * Return:			None
	 */
	void begin(long speed);
	/*
	 * Function:		end
	 * Description:		End the Uart Communication,Release the Rx pin,Tx pin and the timer.
	 * Parameters:		None
	 * Return:			None
	 */
	void begin(long speed,unsigned char config,unsigned char TxPin,unsigned char RxPin);
	void end(void);
	/*
	 * Function:		gerParityBits
	 * Description:		Get the configuration of the parity.
	 * Parameters:		None
	 * Return:			unsigned char (the parity_bits)
	 */
	inline unsigned char getParityBits(void);
	/*
	 * Function:		read
	 * Description:		Read the uart FIFO and release the fifo by byte.
	 * Parameters:		None
	 * Return:			unsigned char (the Uart value get earliest)
	 */
	unsigned char read(void);
	/*
	 * Function:		available
	 * Description:		Get the length of the Uart fifo.
	 * Parameters:		None
	 * Return:			unsigned char (The length of the Uart fifo)
	 */
	unsigned char available(void);
	/*
	 * Function:		peak
	 * Description:		Get the value of the Uart fifo which received earliest BUT NOT release the memory.
	 * Parameters:		None
	 * Return:			unsigned char (the Uart value get earliest)
	 */
	int peak(void);
	/*
	 * Function:		write
	 * Description:		Send a byte by Uart
	 * Parameters:		1.	byte (unsigned char)
	 * Return:			None
	 */
	void write(unsigned char byte);
	/*
	 * Function:		write
	 * Description:		Send a string by Uart
	 * Parameters:		1. string(char *)
	 * 						The address of string.
	 * Return:			None
	 */
	void write(char *string);
	/*
	 * Function:		write
	 * Description:		Send many bytes by Uart
	 * Parameters:		1. buf (unsigned char *)
	 * 						The address of the buffer.
	 * 					2. len (unsigned char)
	 * 						The length of the buffer.
	 * Return:			None
	 */
	void write(unsigned char *buf,unsigned char len);
	/*
	 * Function:		print
	 * Description:		Send a character by Uart
	 * Parameters:		1. c(char)
	 * 						The character will be sent.
	 * Return:			int
	 * 						The number of buffer has been sent.
	 */
	int print(char c);
	/*
	 * Function:		print
	 * Description:		Send a string by Uart
	 * Parameters:		1. string (unsigned char *)
	 * 						The address of the string will be sent.
	 * Return:			int
	 * 						The number of buffer has been sent.
	 */
	int print(unsigned char *string);
	/*
	 * Function:		print
	 * Description:		Send a string by Uart
	 * Parameters:		1. string (char *)
	 * 						The address of the string will be sent.
	 * Return:			int
	 * 						The number of buffer has been sent.
	 */
	int print(char *string);
	/*
	 * Function:		print
	 * Description:		Send a string by Uart
	 * Parameters:		1. dat (int)
	 * 						The data will be sent by ASCII as DEC.
	 * Return:			int
	 * 						The number of buffer has been sent.
	 */
	int print(int dat);
	/*
	 * Function:		println
	 * Description:		Send a string by Uart,end by '\r\n'.
	 * Parameters:		1. string (unsigned char *)
	 * 						The address of the string will be sent.
	 * Return:			int
	 * 						The number of buffer has been sent.
	 */
	int println(char c);
	/*
	 * Function:		print
	 * Description:		Send a string by Uart,end by '\r\n'.
	 * Parameters:		1. string (unsigned char *)
	 * 						The address of the string will be sent.
	 * Return:			int
	 * 						The number of buffer has been sent.
	 */
	int println(unsigned char *string);
	/*
	 * Function:		print
	 * Description:		Send a string by Uart,end by '\r\n'.
	 * Parameters:		1. string (char *)
	 * 						The address of the string will be sent.
	 * Return:			int
	 * 						The number of buffer has been sent.
	 */
	int println(char *string);
	/*
	 * Function:		print
	 * Description:		Send a string by Uart,end by '\r\n'.
	 * Parameters:		1. dat (int)
	 * 						The data will be sent by ASCII as DEC.
	 * Return:			int
	 * 						The number of buffer has been sent.
	 */
	int println(int dat);
	/*
	 * Function:		print
	 * Description:		Send a number by a special format.
	 * Parameters:		1. dat (unsigend char)
	 * 						The data will be sent by ASCII.
	 * 					2. format(unsigned char)
	 * 						The format can be set as:
	 * 						1)BIN
	 * 						2)OCT
	 * 						3)DEC
	 * 						4)HEX
	 * Return:			None
	 */
	void print(unsigned char dat,unsigned char format);
	/*
	 * Function:		print
	 * Description:		Send a number by a special format,end by '\r\n'.
	 * Parameters:		1. dat (unsigend char)
	 * 						The data will be sent by ASCII.
	 * 					2. format(unsigned char)
	 * 						The format can be set as:
	 * 						1)BIN
	 * 						2)OCT
	 * 						3)DEC
	 * 						4)HEX
	 * Return:			None
	 */
	void println(unsigned char dat,unsigned char format);
	void _Timer_A1_ISR_(void);
	unsigned char _Timer_A1_ISR_NONE(void);
	unsigned char _Timer_A1_ISR_ODD(void);
	unsigned char _Timer_A1_ISR_EVEN(void);
};
//extern UART_FIFO uart_recieve_fifo;
extern Serial serial;
#endif /* SOFT_UART_CPP_H_ */
