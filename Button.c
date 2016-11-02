#include "lpc11xx.h"
#include "timer16.h"
#include "clkconfig.h"

#define LED1_ON  LPC_GPIO1->DATA &= ~(1<<8)
#define LED1_OFF LPC_GPIO1->DATA |= (1<<8)
#define LED1_Change LPC_GPIO1->DATA^=(1<<8); // XOR

extern volatile uint32_t timer16_0_counter;
uint32_t msTicks=0;

void SysTick_Handler(void)
{
   msTicks++;
}

void led_init()
{
   LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16); // 
   LPC_IOCON->PIO0_1 &= ~0x07;
   LPC_IOCON->PIO0_1 |= 0x01; //
   LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<16); // 
   LPC_GPIO1->DIR |= (1<<8); // 
   LPC_GPIO1->DATA |= (1<<8); // 
}
int main()
{
   led_init();
   T16B0_init();
	 while(1){
		 if((LPC_GPIO2->DATA&(1<<6))!=(1<<6)){
					T16B0_delay_ms(2);
					msTicks=0;
				while(1){
						SysTick_Config(SystemAHBFrequency/2500);
						T16B0_delay_ms(2);
						if((LPC_GPIO2->DATA&(1<<6))!=(1<<6)&&(msTicks>1000)){
							LED1_OFF;
									while(1){
										LED1_ON;
										T16B0_delay_ms(250);
										LED1_OFF;
										T16B0_delay_ms(250);
										
										if((LPC_GPIO2->DATA&(1<<6))==(1<<6)){
										LED1_OFF;
										msTicks=0;
										break;
										}
									}
									break;
						}
						
						else if(msTicks<1000&&(LPC_GPIO2->DATA&(1<<6))==(1<<6)){
									T16B0_delay_ms(2);
									LED1_Change;
							    msTicks=0;
									break;
						}
					
					}
			}
		 }
}	 