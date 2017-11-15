/*
 * I2C.h
 *
 *  Created on: 2015-7-23
 *      Author: Administrator
 */

#ifndef I2C_H_
#define I2C_H_
class I2C_class {
private:

	unsigned int clock;
	unsigned char SlaveAdd;
	inline void I2C_WriteMode(void);
	inline void I2C_ReadMode(void);
public:
	/*Begin I2C without slave address,can set the address by use the function: change_Slave*/
	void begin(void);
	/*Begin I2C with slave address*/
	void begin(unsigned char slave_address);
	/*Change the Slave address*/
	void change_Slave(unsigned char add);
	/*Sent the data by I2C,
	 * sent to register:	Reg
	 * sent data address:	data
	 * sent data length:	len 	(must <= 16)*/
	void I2C_Tx(unsigned char Reg, unsigned char data, unsigned char len);
	/* Receive the data by I2C,
	 * receive from register:		Reg
	 * receive data store address:	data
	 * receive data length:			len 	(must <= 16)*/
	void I2C_Rx(unsigned char Reg,unsigned char data[],unsigned char len);
};
extern I2C_class I2C;

#endif /* I2C_H_ */
