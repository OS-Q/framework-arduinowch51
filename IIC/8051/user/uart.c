#include "N76E003.h"
#include "define.h"

#include "common.h"
#include "delay.h"

#include "SFR_Macro.h"
#include "uart.h"

#define XON  0x11
#define XOFF 0x13

#if 0
/****************************************************************************/
/* Define putchar send from UART1, printf function will send from P1.6(TXD_1)
/* NOTICE: Since UART1 pin is multi-function with OCD DATA/CLK pin.
/* Suggest download than use run with realchip but not OCD mode.
/****************************************************************************/
char putchar (char c)
{
		while (!TI_1);  /* wait until transmitter ready */
		TI_1 = 0;
		SBUF_1 = c;      /* output character */
		return (c);
}

void InitUART(void) 
{
	InitialUART1_Timer3(115200);
	TI_1 = 1;
}
#else

void InitUART(void) 
{
		InitialUART0_Timer3(115200);
		TI = 1;														
}
char putchar (char c)  {

  if (c == '\n')  {
    if (RI)  {
      if (SBUF == XOFF)  {
        do  {
          RI = 0;
          while (!RI);
        }
        while (SBUF != XON);
        RI = 0; 
      }
    }
    while (!TI);
    TI = 0;
    SBUF = 0x0d;                         /* output CR  */
  }
  if (RI)  {
    if (SBUF == XOFF)  {
      do  {
        RI = 0;
        while (!RI);
      }
      while (SBUF != XON);
      RI = 0; 
    }
  }
  while (!TI);
  TI = 0;
  return (SBUF = c);
}
#endif









