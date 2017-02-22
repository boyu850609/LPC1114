#include "lpc11xx.h"
#include "PWM.h"


void T16B0M0_PWM_Init(uint16_t cycle,float duty)
{
   if((duty>=100)&&(duty<=0))return;
   LPC_SYSCON->SYSAHBCLKCTRL |= (1<<7);
   LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16);
   LPC_IOCON->PIO0_8 &= ~0x07;
   LPC_IOCON->PIO0_8 |= 0x02;
   LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<16);
	 LPC_TMR16B0->TCR = 0x00; 
	 LPC_TMR16B0->TCR = 0x02;
   LPC_TMR16B0->PWMC= 0x01;
   LPC_TMR16B0->MCR = 0x02<<9;
   LPC_TMR16B0->MR3 = cycle;
   LPC_TMR16B0->MR0 = cycle/100*(100-duty);
   LPC_TMR16B0->TCR = 0x01;
   //LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<7);
}

void T16B0M0_PWM_SET(uint16_t cycle,uint8_t duty)
{
   if((duty>=100)&&(duty<=0))return;
   LPC_TMR16B0->MR0 = cycle/100*(100-duty);
}


