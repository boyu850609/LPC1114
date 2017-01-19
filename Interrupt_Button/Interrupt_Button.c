#include "LPC11xx.H"
#include "led.h"
#include "timer16.h"

#define Key_pin 6 //set Key_pin
#define Key_delay_timer 1000000 // Button over time into flashing LED
#define delay_timer 600000 // led flashing 0.25sec

static __inline void LED_OFF (void)
{ 
		LPC_GPIO1->DATA |=(1<<8); //close(clear) LED
} 

static __inline void LED_Change (void)
{ 
		LPC_GPIO1->DATA^=(1<<8); // XOR
}

static __inline int Key_press_interrupt (void)
{
		return (LPC_GPIO2->MIS&(1<<6))==(1<<6) ; // press key1 for interrupt(pin2.6)
}

static __inline int Key_press (void)
{
		return (LPC_GPIO2->DATA&(1<<6))!=(1<<6); // press key1(pin2.6)
} 

static __inline int Key_release (void)
{
		return (LPC_GPIO2->DATA&(1<<6))==(1<<6); // release key1(pin2.6)

} 

void Interrupt_init(void)
{
		LPC_GPIO2->IE |= (1<<Key_pin); // set pin2.6 to generate an interrupt
}

int delay(int time)
{
		long int i;
		for(i=time;i>0;i--){};
		return time;
}

/* interrupt Button function */
void PIOINT2_IRQHandler(void)	
{	
		long i;
		if(Key_press_interrupt())
		{
				while(Key_press())
				{
						for(i=Key_delay_timer;i>0;i--)
						{
								if( Key_release())
										break;
						}
						
						if(Key_release())
						{
								LED_Change();
								LPC_GPIO2->IC = 0XFFFF;
								break;
						}			
						
						while(1)
						{
								LED_Change();
								delay(delay_timer);
										if(Key_release())
										{
												LED_OFF(); //	close LED
												LPC_GPIO2->IC = 0XFFFF;
												break; // break Flashing loop
										}
						}
				}		
		}	
}

int main()
{
   led_init(); // use led
   T16B0_init(); // use timer16
	 Interrupt_init();
	 NVIC_EnableIRQ(EINT2_IRQn);// use Button_IRQHandler
	 while(1); // loop
}	  
