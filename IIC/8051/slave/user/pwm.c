#include "N76E003.h"
#include "WS281X.h"
#include "SFR_Macro.h"
#include "define.h"
#include "pwm.h"
#include "i2c.h"
#include "string.h"

 

U16 Time1flag;															//总时间
U8  Interval = 0;														//时间间隔


U8  vol_save = 0;														//保存音量
U8  buzz_begin = 0;

void pwm_init()
{
		P03_PushPull_Mode;
		PWM5_P03_OUTPUT_ENABLE;	
		PWM_IMDEPENDENT_MODE;
		PWM_CLOCK_DIV_8;
		PWMPH = 0x04;
		PWMPL = 0xCF;
/**********************************************************************
	PWM frequency = Fpwm/((PWMPH,PWMPL) + 1) <Fpwm = Fsys/PWM_CLOCK_DIV> 
								= (16MHz/8)/(0x7CF + 1)
								= 1KHz (1ms)
***********************************************************************/
		set_SFRPAGE;						//PWM4 and PWM5 duty seting is in SFP page 1
		PWM5H = 0x00;						
		PWM5L = 0x00;
		clr_SFRPAGE;
    set_LOAD;
    set_PWMRUN;
}

void pwm_off()
{
		set_SFRPAGE;						//PWM4 and PWM5 duty seting is in SFP page 1
		PWM5H = 0x00;						
		PWM5L = 0x00;
		clr_SFRPAGE;
	  set_LOAD;
}
void pwm_on()
{
		set_SFRPAGE;						//PWM4 and PWM5 duty seting is in SFP page 1
		PWM5H = 0x07;						
		PWM5L = 0x50;
		//PWM5H = data_received[3];						
		PWM5L = 0x00;
		clr_SFRPAGE;
	  set_LOAD;
}











