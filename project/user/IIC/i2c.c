#include "N76E003.h"
#include "SFR_Macro.h"
#include "define.h"
#include "i2c.h"

unsigned char  ack = 0;

void I2C_Delay(void)
{
	int a=0;
	while(a);
}

void Init_I2C(void)
{
	P13_PushPull_Mode;	//SCL PULL HIGH
	SCL_MODE_OUT;	//SCL output
	SCL_DATA = 1;	//SCL 1

	P14_PushPull_Mode;	//SDA PULL HIGH		
	SDA_MODE_OUT;	//SDA output	
	SDA_DATA = 1;	//SDA 1	
}


//启动信号 
void I2C_Start()
{
    //数据线下降沿
    SDA_DATA = 1;
		SCL_DATA = 1;	
    I2C_Delay();
    SDA_DATA = 0;
    I2C_Delay();
		SCL_DATA = 0;
		I2C_Delay();
}

//停止信号 
void I2C_Stop()
{
		SDA_DATA = 0;
//	I2C_Delay();
		SCL_DATA = 1;
		I2C_Delay();
    //数据线上升沿
    SDA_DATA = 1;
//	I2C_Delay();
}

//写一个字节数据
void I2C_Send_Byte(unsigned char  tx_data)
{
    unsigned char  i;
    for(i = 0;i < 8; i ++)
    {	
			if (tx_data & 0x80)
				SDA_DATA = 1;
			else
				SDA_DATA = 0;
			tx_data <<= 1;
			SCL_DATA = 1;
			I2C_Delay();
			SCL_DATA = 0;
			I2C_Delay();
    }
}

unsigned char  I2C_Wait_Ack(void)
{
    //先将数据线要设置成输入模式,有应答则会出现下降沿
	SDA_MODE_IN;
	SCL_DATA = 1;
	I2C_Delay();
	if(SDA_DATA)
	{
		I2C_Stop();
		SDA_MODE_OUT;
		SCL_DATA = 0;
		I2C_Delay();
		return 1;
	}
	SDA_MODE_OUT;
	SCL_DATA = 0;
	I2C_Delay();
	return 0;
}

//写数据
void Dvice_WriteData(unsigned char  DeciveAddr,unsigned char  DataAddr,unsigned char  Data)
{
    I2C_Start();
    I2C_Send_Byte(DeciveAddr);
    I2C_Wait_Ack();
    I2C_Send_Byte(DataAddr);
    I2C_Wait_Ack();
    I2C_Send_Byte(Data);
		I2C_Wait_Ack();
    I2C_Stop();     
}

//应答
void I2C_Ack()
{
    //数据线一直保持为低电平，时钟线出现上升沿即为应答
    SDA_DATA = 0;
    SCL_DATA = 0;
    I2C_Delay();
    SCL_DATA = 1;
    I2C_Delay();
}
void I2C_NAck()
{
    //数据线一直保持为低电平，时钟线出现上升沿即为应答
		SCL_DATA = 0;  
		SDA_DATA = 1;
    I2C_Delay();
    SCL_DATA = 1;
    I2C_Delay();
}

unsigned char  I2C_Read_Byte(unsigned char ack)
{
    unsigned char  i = 0;
    unsigned char  receive = 0;
    //数据线模式切换为输入
		SDA_MODE_IN;
    for(i = 0;i < 8; i ++)
    {
        SCL_DATA = 0;
        I2C_Delay();
				SCL_DATA = 1;
				I2C_Delay();
				receive <<= 1;
        //判断数据线电平
        if(SDA_DATA)
        {
            receive ++;
        }
    }
		SDA_MODE_OUT;
    if (!ack) I2C_NAck();
    else   I2C_Ack(); 
		//I2C_Ack();
		return receive;
}
//unsigned char  I2C_Read_Byte()
//{
//    unsigned char  i = 0;
//    unsigned char  receive = 0;
//    //数据线模式切换为输入
//		SDA_MODE_IN;
//    for(i = 0;i < 8; i ++)
//    {
//        SCL_DATA = 0;
//        I2C_Delay();
//				SCL_DATA = 1;
//				I2C_Delay();
//				receive <<= 1;
//        //判断数据线电平
//        if(SDA_DATA)
//        {
//            receive ++;
//        }
//    }
//		SDA_MODE_OUT;
//		I2C_Ack();
//		return receive;
//}
//unsigned char  Decive_ReadData(unsigned char  DeciveAddr,unsigned char  DataAddr,unsigned char  ReciveData)
//{
//    unsigned char  i;
//    I2C_Start();
//    I2C_Send_Byte(DeciveAddr);
//    I2C_Wait_Ack();
//    I2C_Send_Byte(DataAddr);                     
//    I2C_Wait_Ack();     
//    //发送器件地址读模式
//    I2C_Send_Byte(DeciveAddr + 1);
//    //等待应答
//    I2C_Wait_Ack();
//    for(i = 0;i < 8;i ++)
//    {
//        ReciveData= I2C_Read_Byte();
//        ReciveData++;
//    }
//    //停止信号

//    I2C_Stop();
//	return ReciveData;
//}

unsigned char  IIC_ReadData(unsigned char  DeciveAddr)
{
    unsigned char  i,ReciveData;
    I2C_Start();
//    I2C_Send_Byte(DeciveAddr);
//    I2C_Wait_Ack();
//    I2C_Send_Byte(DataAddr);                     
//    I2C_Wait_Ack();     
    //发送器件地址读模式
    I2C_Send_Byte(DeciveAddr + 1);
    //等待应答
    I2C_Wait_Ack();
    for(i = 0;i < 8;i ++)
    {
        ReciveData = I2C_Read_Byte(0);
        ReciveData++;
    }
    //停止信号

    I2C_Stop();
		return ReciveData;
}
