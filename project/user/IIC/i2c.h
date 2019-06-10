#ifndef __I2C_H__
#define __I2C_H__

#include <stdio.h>

void Init_I2C(void);
void	I2C_Start(void);
void	I2C_Stop(void);
void	I2C_Send_Byte(unsigned char  tx_data);
//unsigned char  I2C_Read_Byte(void);
unsigned char  I2C_Read_Byte(unsigned char ack);
void	Dvice_WriteData(unsigned char  DeciveAddr,unsigned char  DataAddr,unsigned char  Data);
//void	Decive_ReadData(unsigned char  DeciveAddr,unsigned char  DataAddr,unsigned char  ReciveData);
unsigned char  IIC_ReadData(unsigned char  DeciveAddr);
void	I2C_Ack(void);
void	I2C_NAck(void);
unsigned char  I2C_Wait_Ack(void);
//extern void Write_I2C_Byte(unsigned char IIC_Byte);

/**********************************************
SCL--- P31
SDA--- P30
**************************************************/
//SDA
#define		SDA_DATA			P14
#define		SDA_MODE_IN		P14_Input_Mode
#define		SDA_MODE_OUT	P14_OpenDrain_Mode
#define		SDA_PULL_HIGH	P14_PushPull_Mode

//SCL
#define		SCL_DATA			P13
#define		SCL_MODE_OUT	P13_OpenDrain_Mode

//#define		I2C_Delay()		

#endif
