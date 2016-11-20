#include "LPC11xx.H"
#include "led.h"
#include "timer16.h"

#define LED_pin 8 //set LED_pin
#define LED_on  LPC_GPIO1->DATA &=~(1<<LED_pin); //open(set) LED
#define LED_off LPC_GPIO1->DATA |=(1<<LED_pin);  //close(clear) LED
#define LED_on_delay 1000 // set LED_on delay time
#define LED_off_delay 250 // set LED_off delay time

int main()
{
   led_init(); // use led
   T16B0_init(); // use timer16
   while(1)
   {
      T16B0_delay_ms(LED_on_delay);  // delay LED_on 1sec
      LED_on;
      T16B0_delay_ms(LED_off_delay); // delay LED_off 0.25sec
      LED_off;
   }
}
