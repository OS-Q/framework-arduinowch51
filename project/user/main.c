#include <string.h>
#include <intrins.h> 
#include <stdio.h>

#include "common.h"
#include "delay.h"
#include "N76E003.h"
#include "SFR_Macro.h"
#include "define.h"

#include "adc.h"
#include "uart.h"
#include "BH1750.h"
/*******************************************************************************
* Function Name  : main
* Description    : 
* Input          : 
* Output         : None
* Return         : None
*******************************************************************************/

void main(void) 
{	
	u16 x =0;
	InitUART();
	//x =Convert_BH1750();
	printf("power level=%d",x);
	while(1);
}

