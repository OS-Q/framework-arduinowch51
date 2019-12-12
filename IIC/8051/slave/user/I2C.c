
#include "N76E003.h"
#include "WS281X.h"
#include "SFR_Macro.h"
#include "define.h"
#include "intrins.h"
#include "string.h"
#include "I2C.h"

/* Private variables ---------------------------------------------------------*/

bit BIT_TMP;

#define I2C_CLOCK               13									//iic传输速率
#define EEPROM_SLA              0x40								//从机地址	

U8 xdata data_received[64];

U8 xdata data_store[256];
U8 ptr;
U8 data_num = 0,num = 0,data_flag = 0,ll = 0;
U8 Rxflag=0;
U8 begin_flag = 0;
U8 led_number = 0;
U8 led_lck = 0;

bit I2C_Reset_Flag;

void Init_I2C(void)
{
		P13_OpenDrain_Mode;
		P14_OpenDrain_Mode;		
    SDA = 1;                                //set SDA and SCL pins high
    SCL = 1;   	
    set_P0SR_6;                             //set SCL (P06) is  Schmitt triggered input select. 	
    set_EI2C;                               //enable I2C interrupt by setting IE1 bit 0
    set_EA;
    I2ADDR = EEPROM_SLA;                    //define own slave address
    set_I2CEN;                              //enable I2C circuit
    set_AA;

		memset(data_received,0x00,64);//清零，防止后面处理数据时拿取的数据出错
		memset(data_store,0x00,256);	
}

void I2C_SI_Check(void)
{
		if (I2STAT == 0x00)
		{
				I2C_Reset_Flag = 1;
				set_STO;
				SI = 0;
				if(SI)
				{
						clr_I2CEN;
						set_I2CEN;
						clr_SI;
						clr_I2CEN;		
				} 	
		}	
}

void i2c_send_task(void)
{	
	//printf("\n test i2c_send_task ");
}

void i2c_wait_task(void)
{	
	if( begin_flag == 1)	 //主机发送数据结束标志
	{			
				led_lck = data_received[1];	
/*******************************************************************************
				蜂鸣器判断数据先判断，是执行后清空数据退出，不是则开始接收灯数据
*******************************************************************************/
				if(data_received[1]==0xa1 && data_received[2]==0x01)
				{
						if( data_received[3]>=0x04 )data_received[3]=0x04;
						data_num = 0;
						memset(data_received,0x00,64);		
						begin_flag = 0;	
						return ;
				}
				if(data_received[1]==0xa1 && data_received[2]==0x00)
				{
						data_num = 0;
						memset(data_received,0x00,64);		
						begin_flag = 0;	
						return ;
				}
/*******************************************************************************
				灯数据接收
*******************************************************************************/
				data_num = 0;
				for( num=0;num<22;num++ )
				{
					data_store[ptr] = data_received[num+3];	
					ptr++;	
				}	
#if 0
				for( num=0;num<22;num++ )
				{
					Send_Data_To_UART0(data_store[num]);		
				}
#endif				
/*******************************************************************************
				灯数据接收结束，次数为data_received[2]-0x80
*******************************************************************************/
				if(data_received[2]>0x80)
				{
					Rxflag = 1;
					led_number = data_received[2]-0x80;
					ptr = 0;
				}
				memset(data_received,0x00,64);		
				begin_flag = 0;	
	}																			
}

	
void I2C_ISR(void) interrupt 6
{
    switch (I2STAT)
    {
#if 0
        case 0x00:
            STO = 1;
            break;
#endif
        case 0x60://ADDR ACK
//						memset(data_received,0x00,sizeof(data_received));
			systatus = 1;
            AA = 1;
            break;
#if 0				
        case 0x68:
						P02 = 0;
						
            while(1);
            break;
#endif
        case 0x80:	//DATA ACK																			//接收数据
            data_received[data_num] = I2DAT;
						data_num++;					
            AA = 1;
            break;
#if 0
        case 0x88:	//DATA ERROR																			//错误时归零
            data_received[data_num] = I2DAT;
            data_num = 0;
						clr_GPIO1;
            AA = 1;
            break;
#endif				       
/*******************************************************************************
主机发送停止位，程序每次都会执行但是有时候判断不到，所以改为判断数据值
*******************************************************************************/
				case 0xA0:	//REC END		
						begin_flag = 1;	
            AA = 1;						
            break;
#if 0 
				case 0xA8:	//ADDR BACK ACK											
						ll = 0;
						I2DAT = data_store[ll];   
						ll++;
            AA = 1;
            break;
#endif	  
#if 0				
        case 0xB8:  //DATA BACK ACK 
				
						I2DAT = data_store[ll];
            ll++;
            AA = 1;
            break;
#endif
        case 0xC0:	//NACK						
						data_num = 0;		//为下一次数据做准备
						memset(data_received,0x00,sizeof(data_received));	
						memset(data_store,0x00,sizeof(data_store));				
						ptr = 0;
						ll = 0;
            AA = 1;
            break; 
#if 0
        case 0xC8:	
            AA = 1;
            break;
#endif
		default:		
						set_STO;
//((void(code*)(void))0x0000)();	
		   break;		
    }
    SI = 0;   
    while(SI != 0)
    {
				if(I2STAT == 0x00)
        {
            set_STO;
        }
        SI = 0;
        if(SI != 0)
        {
            clr_I2CEN;
            set_I2CEN;
            clr_SI;
            //clr_I2CEN
        } 
										
    }   
    while(STO);
}


/************************ (C) COPYRIGHT Q-i-t-a-s **********************/


