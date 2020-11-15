/*
 * i2c.c
 *
 * Created: 09/11/2020 10:36:45
 *  Author: Alexey Ivanov
 *  v1.0
 *  I2C driver
 * GitHub: https://github.com/AlexAlexFr
 */ 

#include "i2c.h"

void i2c_Init()
{
		//Initialize I2C
		TWBR = I2C_BITRATE;
		TWSR = 0;
		TWCR |= (1<<TWEN);
}

void i2c_Start()
{
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
	
}

void i2c_SendByte(char cByte)
{
	TWDR = cByte;
	TWCR = (1<<TWINT)|(1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
}

char i2c_GetStatus()
{
	return TWSR & 0xf8 >> 3;
}

void i2c_Stop()
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}

char i2c_ReadByteACK()
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	while(!(TWCR & (1<<TWINT)));
	return TWDR;
}

char i2c_ReadByteNOACK()
{
	
	TWCR = (1<<TWINT)|(1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
	return TWDR;
}

