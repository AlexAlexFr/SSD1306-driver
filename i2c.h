/*
 * i2c.h
 *
 * Created: 09/11/2020 10:37:00
 *  Author: Alexey Ivanov
 *  I2C driver
 *  v1.0
 */ 


#ifndef I2C_H_
#define I2C_H_

#include <avr/io.h>

#ifndef F_CPU
#define F_CPU		16000000UL
#endif

#define I2C_CLK		400000								//define SCL I2C frequency, maximum 400kHz
#define I2C_BITRATE	((F_CPU/I2C_CLK)-16)/2+1	//calculation for TWBR register with prescale 1

/************************************************************************/
/* I2C functions                                                        */
/************************************************************************/

#define I2C_START	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
#define I2C_STOP	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);

#define I2C_WRITE	0
#define I2C_READ	1

void i2c_Init();
void i2c_Start();
void i2c_SendByte(char cByte);
void i2c_Stop();
char i2c_ReadByteACK();
char i2c_ReadByteNOACK();

char i2c_GetStatus();

#endif /* I2C_H_ */