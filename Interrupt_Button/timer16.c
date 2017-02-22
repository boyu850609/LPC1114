#include "LPC11xx.h"
#include "timer16.h"

void T16B0_init(void)
{
   LPC_SYSCON->SYSAHBCLKCTRL |= (1<<7);   
   LPC_TMR16B0->IR  = 0x01;           
   LPC_TMR16B0->MCR = 0x04;  
}
void T16B0_delay_ms(uint16_t ms)
{
   LPC_TMR16B0->TCR = 0x02;          
   LPC_TMR16B0->PR  = SystemAHBFrequency/1000-1;       
   LPC_TMR16B0->MR0 = ms;     
   LPC_TMR16B0->TCR = 0x01;         
   while (LPC_TMR16B0->TCR & 0x01);
}
void T16B0_delay_us(uint16_t us)
{
   LPC_TMR16B0->TCR = 0x02;          
   LPC_TMR16B0->PR  = SystemAHBFrequency/1000000-1;        
   LPC_TMR16B0->MR0 = us;      
   LPC_TMR16B0->TCR = 0x01;          
   while (LPC_TMR16B0->TCR & 0x01);
}
