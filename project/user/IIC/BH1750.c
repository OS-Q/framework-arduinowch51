


#include "N76E003.h"
#include "SFR_Macro.h"
#include "define.h"
#include "common.h"
#include "delay.h"
#include "i2c.h"
#include "BH1750.h"


float result_lx=0;
unsigned char Data_BH1750[2]={0};
unsigned int LLX;


void Init_BH1750(void)
{
	Init_I2C();
	Timer0_Delay1ms(15);
}

void I2C_Send(u8 cmd)
{
    I2C_Start();                 
    I2C_Send_Byte(BH1750_Addr+0);  
    while(I2C_Wait_Ack());
    I2C_Send_Byte(cmd);    
    while(I2C_Wait_Ack());    
    I2C_Stop();              
    Timer0_Delay1ms(5);
}

void Start_BH1750(void)
{
//	Dvice_WriteData(BH1750_Addr,BH1750_ON,0);
//	Dvice_WriteData(BH1750_Addr,BH1750_RSET,0);
//	Dvice_WriteData(BH1750_Addr,BH1750_ONE,0);
	I2C_Send(BH1750_ON);	
	I2C_Send(BH1750_RSET);	
	I2C_Send(BH1750_ONE);   
}


void Read_BH1750(void)
{ 
    Init_I2C();
    Start_BH1750();
    Timer0_Delay1ms(180);
		//Data_BH1750[0] = IIC_ReadData(BH1750_Addr);
    I2C_Start();                      
    I2C_Send_Byte(BH1750_Addr+1);       
    while(I2C_Wait_Ack());
    Data_BH1750[0]=I2C_Read_Byte();    
    Data_BH1750[1]=I2C_Read_Byte();  
		I2C_Stop(); 
		printf("level 0=%x \n",Data_BH1750[0]);	
		printf("level 1=%x \n",Data_BH1750[1]);	
                   
    Timer0_Delay1ms(5);
}


u16 Convert_BH1750(void)
{
  Read_BH1750();
	LLX=Data_BH1750[0];
	LLX=(LLX<<8)+Data_BH1750[1];
	LLX=(u16)(LLX/1.2);	
	return LLX;
}


