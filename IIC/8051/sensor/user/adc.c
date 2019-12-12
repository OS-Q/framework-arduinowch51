
#include "SFR_Macro.h"
#include "N76E003.h"
#include "define.h"
#include "common.h"
#include "delay.h"
#include "adc.h"

u16 adc(void) 
{
		u8 i,cnt=16;	
		u16 ADCsumH=0, ADCsumL=0, ADCval=0;
		u8 ADCavgH, ADCavgL;
		P05_PushPull_Mode;
		P05 = 0;
		Enable_ADC_AIN0;						// Enable AIN0 P1.7 as ADC input, Find in "Function_define.h" - "ADC INIT"
			
		for(i=0;i<cnt;i++)
    {
			clr_ADCF;
			set_ADCS;									// ADC start trig signal
      while(ADCF == 0);
			ADCsumH = ADCsumH + ADCRH;
			ADCsumL = ADCsumL + ADCRL;
		}			
		ADCavgH = ADCsumH/cnt;
		ADCavgL = ADCsumL/cnt;
		P05 = 1;
		ADCval= ADCavgH*256 + ADCavgL;
	  return ADCval;
}

