#include "lpc11xx.h"
#include "timer16.h"
#include "clkconfig.h"
#include "led.h"

#define LED_pin 8 //set LED_pin
#define Key_pin 6 //set Key_pin
#define LED_on_delay 250 // set LED_on delay time
#define LED_off_delay 250 // set LED_off delay time

static __inline void LED_OFF(void)
{
		LPC_GPIO1->DATA |=(1<<LED_pin);  //close(clear) LED
}

static __inline void LED_Change(void)
{
		LPC_GPIO1->DATA^=(1<<LED_pin); // XOR
}

static __inline int Key_press (void)
{ 
		return (LPC_GPIO2->DATA&(1<<Key_pin))!=(1<<Key_pin); // press key1(pin2.6)
}
static __inline int Key_release (void)
{
		return (LPC_GPIO2->DATA&(1<<Key_pin))==(1<<Key_pin); // release key1(pin2.6)
}


extern volatile uint32_t timer16_0_counter;
uint32_t msTicks=0;

/* system Clock */
void SysTick_Handler(void) 
{
   msTicks++;// plus System Clock
}

void Button_Handler(void)
{
	while(1)
	{
		 /* 
			*press key1(button)_pin2.6 
			*/
			if(Key_press())
			{ 
					T16B0_delay_ms(2); // avoid for switch bounce
					msTicks=0; 				 // clear msTicks to zero
				
					while(1)
					{
							SysTick_Config(SystemFrequency/1000); // set every millisecond into interrupt
							T16B0_delay_ms(2); 									 // avoid for switch bounce
								
							/* press key1(button)_pin2.6 and press over one second */
							if(Key_press()&&(msTicks>1000))	// plus 1000 times to count 1sec
							{ 
									LED_OFF(); 								  // clear LED
								
								  /* Enter Flashing loop */
									while(1)
									{
											LED_Change();
											T16B0_delay_ms(LED_on_delay); // delay open 0.25sec
										
											/* release key1(button) */
											if(Key_release())
											{
													LED_OFF(); //	close LED
													msTicks=0; // clear msTicks
													break; // break Flashing loop
											}
									}
									break;
							}
							
							/* Press to release the button not over than one second */
							else if(msTicks<1000&&Key_release())
							{
									T16B0_delay_ms(2);// avoid for switch bounce
									LED_Change(); // xor LED status
									msTicks=0;// clear msTicks
									break;
							}
							
					}
		}
	}
}

int main()
{
   led_init(); // use led
   T16B0_init(); // use timer16
	 Button_Handler(); // use Button_Handler
}	 
