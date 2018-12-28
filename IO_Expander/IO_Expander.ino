/*
 Name:		IO_Expander.ino
 Created:	12/27/2018 11:50:21 PM
 Author:	braya
*/

// the setup function runs once when you press reset or power the board
#include <Wire.h>
#include "CustomBinary.h"

const int _address = 0x20;

#define _IOCON 0x0A
#define _IODIRA 0x00
#define _GPIOA 0x12 // 0x09 // 
#define _OLATA 0x14 // 0x0A // 

void execute(void);
void I2C_Write(int address, int reg, int data);
int I2C_Read(int address, int reg);

void setup() {
	// I2C_Write(_address, _IOCON, B00100000);
	 I2C_Write(_address, _IODIRA, 0x0F);	// set input output register of IO-expander // 1 == input // IO0 - IO3 == input
	 I2C_Write(_address, _OLATA, 0x00);
}

// the loop function runs over and over again until power down or reset
void loop() {
	 execute();

}

void execute(void)
{
	int result = I2C_Read(_address, _GPIOA);
	if (result > 0x00) {
		I2C_Write(_address, _OLATA, (result << 4));
	}
	else {
		I2C_Write(_address, _OLATA, 0x00);
	}
}

void I2C_Write(int address, int reg, int data)
{
	Wire.beginTransmission(address);
	Wire.write(reg);
	Wire.write(data);
	Wire.endTransmission();
	delay(500);
}

int I2C_Read(int address, int reg)
{
	int result;

	Wire.beginTransmission(address);	// slave address
	Wire.write(reg);				    // set pointer to the right address of the register to read from
	Wire.endTransmission();

	Wire.requestFrom(address, 1);		// request 1 byte from slave address
	do
	{
		result = Wire.read();
	} while (Wire.available());

	Wire.endTransmission();
	delay(500);
	return result;
}
