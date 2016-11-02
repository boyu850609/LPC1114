#include "lpc11xx.h"
#include "timer16.h"

#define LED1_ON  LPC_GPIO1->DATA &= ~(1<<8)
#define LED1_OFF LPC_GPIO1->DATA |= (1<<8)

void led_init()
{
   LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16); // ??IOCON??
   LPC_IOCON->PIO0_1 &= ~0x07;
   LPC_IOCON->PIO0_1 |= 0x01; //?P1.1????GPIO
   LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<16); // ??IOCON??
   LPC_GPIO1->DIR |= (1<<8); // ?P1.0???????
   LPC_GPIO1->DATA |= (1<<8); // ?P1.0??????
}
int main()
{
   led_init();
   T16B0_init();
   while(1)
   {
      T16B0_delay_ms(1000);
      LED1_ON;
      T16B0_delay_ms(250);
      LED1_OFF;
   }
}