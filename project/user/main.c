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

/*******************************************************************************
* Function Name  : main
* Description    : 
* Input          : 
* Output         : None
* Return         : None
*******************************************************************************/

void main(void) 
{	
	char *i ="test";
	int x =3333;
	InitUART();
	printf("power level=%d",x);
	printf("power level=%s\n",i);
	printf("power level=%d\n",(int)43);
	while(1);
}

