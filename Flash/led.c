#include "LPC11xx.h"
#include "led.h"

#define LED_delay_time 1250000  // set delay 0.5sec
#define LED_delay_Initialtime 0

void led_init(void)
{
	
	 LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16); // Enable the IOCON clock
	
	/* set pin to GPIO */
   LPC_IOCON->PIO0_1 &= ~0x07;
   LPC_IOCON->PIO0_1 |= 0x01; // set pin1.0 to GPIO
	
   LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<16); // Disable the IOCON clock
	
	/* set pin as the output pin*/
   LPC_GPIO1->DIR=0xffff; // set pin1.0 as the output pin
   LPC_GPIO1->DATA =0xffff; // set pin1.0 to high
   
}

void led_delay(void)
{
	long int i;
  for(i=LED_delay_time;i>LED_delay_Initialtime;i--){};	
}
