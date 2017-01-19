#include "LPC11xx.H"
#include "led.h"

#define LED_pin 8 //set LED_pin
static __inline void LED_on (void){
		LPC_GPIO1->DATA &=~(1<<LED_pin);	//open(set) LED
}	
static __inline void LED_off(void){ 
		LPC_GPIO1->DATA |=(1<<LED_pin);	//close(clear) LED
}  


int main(void){
		
	led_init();  //use led
	
	while(1){
		LED_on();			 // open LED
		led_delay(); // delay open 0.5sec
		LED_off();		 //	close LED
		led_delay(); // delay close 0.5sec
	}
}
