#include "LPC11xx.H"
#include "led.h"
#include "timer16.h"

#define LED_pin 8 //set LED_pin
#define Key_pin 6 //set Key_pin
#define Key_delay_timer 1000000 // Button over time into flashing LED
#define delay_timer 600000 // led flashing 0.25sec
#define LED_ON  LPC_GPIO1->DATA &=~(1<<LED_pin); //open(set) LED
#define LED_OFF LPC_GPIO1->DATA |=(1<<LED_pin);  //close(clear) LED
#define LED_Change LPC_GPIO1->DATA^=(1<<LED_pin); // XOR
#define Key_press_interrupt (LPC_GPIO2->MIS&(1<<Key_pin))==(1<<Key_pin) // press key1 for interrupt(pin2.6)
#define Key_press (LPC_GPIO2->DATA&(1<<Key_pin))!=(1<<Key_pin) // press key1(pin2.6)
#define Key_release (LPC_GPIO2->DATA&(1<<Key_pin))==(1<<Key_pin) // release key1(pin2.6)


void Interrupt_init(void){
	//LPC_GPIO2->IS |= (1<<Key_pin); // set pin2.6 touch off 	
	LPC_GPIO2->IE |= (1<<Key_pin); // set pin2.6 to generate an interrupt
}
int delay(int time){
	long int i;
 for(i=time;i>0;i--){};
	 return time;
}

void PIOINT2_IRQHandler(void){
	long i;
	if(Key_press_interrupt){
		while(Key_press){
			for(i=Key_delay_timer;i>0;i--){
				if(Key_release)
					break;
			}
			if(Key_release){
				LED_Change;
				LPC_GPIO2->IC = 0XFFFF;
				break;
			}		
				while(1){
				LED_Change;
				delay(delay_timer);
					if(Key_release){
							LED_OFF; //	close LED
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
	 while(1);
}	  
