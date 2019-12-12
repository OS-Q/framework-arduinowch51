/********************************** (C) COPYRIGHT *******************************
* File Name          : WS281X.C											*	
* Author             : Qitas                                                  *
* Version            : V1.0                                                     *
* Date               : 2019/06/04                                               *
* Description        : 
********************************************************************************/

#include <string.h>
#include <intrins.h> 
#include <stdio.h>

#include "N76E003.h"
#include "WS281X.h"


/****************************硬件参数调整*********************************/

void H1_nop_800ns(){
	_nop_();_nop_();_nop_();
}

void H0_nop_400ns(){
	_nop_();
}

/*******************************************************************************
* Function Name  : Din_1(void)
* Description    : 1bit 信号1
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/

void Din_1(void) {
	WS_IO_HIGH();
        H1_nop_800ns();
	WS_IO_LOW();
	//L1_nop_450ns();
}

/*******************************************************************************
* Function Name  : Din_0(void)
* Description    : 1bit 信号0
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/

void Din_0(void) {
	WS_IO_HIGH();
		_nop_();_nop_();
	WS_IO_LOW();
	//L0_nop_850ns();
}

/*******************************************************************************
* Function Name  : WS_rst()
* Description    : 刷新灯信号
* Input          : 数据
* Output         : None
* Return         : None
*******************************************************************************/

void WS_rst(void) 
{
	WS_IO_LOW();
	//HAL_Delay (1);
}

/*******************************************************************************
* Function Name  : Send_WS_8bits(U8 Data) 
* Description    : 刷新一颗灯一组8bit信号的数据
* Input          : 数据
* Output         : None
* Return         : None
*******************************************************************************/
void Send_WS_8bits(U8 dat)
{
	U8 i;
	for(i=0;i<8;i++) 
	{
		if(dat & 0x80) {//1,for "1",H:0.8us,L:0.45us;
			Din_1();

		} 
		else {		//0,for "0",H:0.4us,L:0.85us
			Din_0();
		}
		dat=dat<<1;
	}
}

/*******************************************************************************
* Function Name  : Send_WS_24bits(U8 RData,U8 GData,U8 BData)  
* Description    : 刷新一颗灯的数据
* Input          : RGB数据
* Output         : None
* Return         : None
*******************************************************************************/
void Send_WS_24bits(U8 RData,U8 GData,U8 BData) 
{
	//G--R--B
	Send_WS_8bits(GData*ring_brightness_duty/255);
	Send_WS_8bits(RData*ring_brightness_duty/255);
	Send_WS_8bits(BData*ring_brightness_duty/255);

}

/*******************************************************************************
* Function Name  : WS_frame_asyn(UINT8* dat) 
* Description    : 刷新一组灯的数据，每颗灯有不同的显示数据
* Input          : 数据地址
* Output         : None
* Return         : 运行状态
*******************************************************************************/
U8 WS_frame_asyn(U8* Ptr) 
{
	U8 i;
	EA = 0;	
	for(i=0;i<WS_LED_NUM;i++) 
	{
		Send_WS_24bits(*(Ptr+3*i),*(Ptr+3*i+1),*(Ptr+3*i+2));
	}
	EA = 1;
	return i;	
}
/*******************************************************************************
* Function Name  : WS_frame_sync(UINT8* dat) 
* Description    : 刷新一组灯的数据，每颗灯有相同的显示数据
* Input          : 数据地址
* Output         : None
* Return         : 运行状态
*******************************************************************************/
U8 WS_frame_sync(U8* Ptr) 
{
	U8 i;
	EA = 0;	
	for(i=0;i<WS_LED_NUM;i++) 
	{
		Send_WS_24bits(*Ptr,*(Ptr+1),*(Ptr+2));
	}
	EA = 1;	
	return i;
}

void ring_display_clear(){
	U8 jk;
	for( jk=0; jk<WS_LED_NUM; jk++) {
		Send_WS_24bits(0x00,0x00,0x00);
	}
}