/********************************** (C) COPYRIGHT *******************************
* File Name          : WS281X.H											*	
* Author             : Qitas                                                  *
* Version            : V1.0                                                     *
* Date               : 2019/06/04                                        *
* Description        : 
********************************************************************************/

#ifndef	__WS281X_H__
#define __WS281X_H__


#include "common.h"

#define 	WS_LED_NUM	 	(7)				/*WS灯的数量*/
#define 	WS_DAT_LEN	 	(WS_LED_NUM*3)		       /*WS数据的长度*/

#define  	ring_brightness_duty   		 50

/****************************硬件IO配置*********************************/
//sbit LED_RING = P0^5;
sbit LED_RING = P1^2;
#define 	WS_IO_LOW() 	(LED_RING=0)
#define 	WS_IO_HIGH() 	(LED_RING=1)

/****************************名称统一宏定义*********************************/
#define  U8 	UINT8
#define  U16 	UINT16
#define  U32 	UINT32

#define  U8X 	UINT8X				/*不同平台的xdata定义不同，需要修改宏*/
#define  U16X 	UINT16X
#define  U32X 	UINT32X



/****************************函数定义*********************************/

void H1_nop_800ns();
void L1_nop_450ns();
void H0_nop_400ns();
void L0_nop_850ns();
void Din_1(void);
void Din_0(void);
void Send_WS_8bits(U8 dat);
void Send_WS_24bits(U8 RData,U8 GData,U8 BData);
void WS_rst(void);
void ring_display_clear();
U8 WS_frame_asyn(U8* Ptr);
U8 WS_frame_sync(U8* Ptr);

#endif
/**************************** END *************************************/