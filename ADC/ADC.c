#include "lpc11xx.h"
#include "ADC.h"

void ADC_Init(int Channel)
{
   if(Channel>7) return;
   LPC_SYSCON->PDRUNCFG &= ~(0x1<<4);        // ADC power up
   LPC_SYSCON->SYSAHBCLKCTRL |= (1<<13);     // ADC clock
   LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16);     // IOCON clock
   switch(Channel)
   {
      case 0: //  set channel 0
			LPC_IOCON->JTAG_TDI_PIO0_11 &= ~0x07;     //clear
			LPC_IOCON->JTAG_TDI_PIO0_11 |= 0x02;      //P0.11 is ADC0 
			LPC_IOCON->JTAG_TDI_PIO0_11 &= ~(3<<3) ;  //close pull-up resistor and pull-dowm resistor
			LPC_IOCON->JTAG_TDI_PIO0_11 &= ~(1<<7) ;   // Analog input mode.
			break;
      case 1:  //  set channel 1
			LPC_IOCON->JTAG_TMS_PIO1_0 &= ~0x07;              //clear
      LPC_IOCON->JTAG_TMS_PIO1_0 |= 0x02;               // P1.0 is ADC1
      LPC_IOCON->JTAG_TMS_PIO1_0 &= ~(3<<3) ;           //close pull-up resistor and pull-dowm resistor
      LPC_IOCON->JTAG_TMS_PIO1_0 &= ~(1<<7) ;           //Analog input mode.
      break;
      case 2:  //  set channel 2
      LPC_IOCON->JTAG_TDO_PIO1_1 &= ~0x07;              //clear
      LPC_IOCON->JTAG_TDO_PIO1_1 |= 0x02;               //P1.1 is ADC2
      LPC_IOCON->JTAG_TDO_PIO1_1 &= ~(3<<3) ;           //close pull-up resistor and pull-dowm resistor
      LPC_IOCON->JTAG_TDO_PIO1_1 &= ~(1<<7) ;           //Analog input mode.
      break;
      case 3:  //  set channel 3
      LPC_IOCON->JTAG_nTRST_PIO1_2 &= ~0x07;             //clear
			LPC_IOCON->JTAG_nTRST_PIO1_2 |= 0x02;              //P1.2 is ADC3
			LPC_IOCON->JTAG_nTRST_PIO1_2 &= ~(3<<3) ;          //close pull-up resistor and pull-dowm resistor
			LPC_IOCON->JTAG_nTRST_PIO1_2 &= ~(1<<7) ;          //Analog input mode.
      break;
      case 4:  //  set channel 4
			LPC_IOCON->ARM_SWDIO_PIO1_3 &= ~0x07;              //clear
			LPC_IOCON->ARM_SWDIO_PIO1_3 |= 0x02;    						//P1.3 is ADC4
			LPC_IOCON->ARM_SWDIO_PIO1_3 &= ~(3<<3) ;           //close pull-up resistor and pull-dowm resistor
			LPC_IOCON->ARM_SWDIO_PIO1_3 &= ~(1<<7) ;           //Analog input mode.
      break;
      case 5:  //  set channel 5
      LPC_IOCON->PIO1_4 &= ~0x07;              //clear
      LPC_IOCON->PIO1_4 |= 0x01;               //P1.4 is ADC5
      LPC_IOCON->PIO1_4 &= ~(3<<3) ;           //close pull-up resistor and pull-dowm resistor
      LPC_IOCON->PIO1_4 &= ~(1<<7) ;           //Analog input mode.
      break;
      case 6:  //  set channel 6
      LPC_IOCON->PIO1_10 &= ~0x07;              //clear
      LPC_IOCON->PIO1_10 |= 0x01;               //P1.10 is ADC6
      LPC_IOCON->PIO1_10 &= ~(3<<3) ;           //close pull-up resistor and pull-dowm resistor
      LPC_IOCON->PIO1_10 &= ~(1<<7) ;           //Analog input mode.
      break;
      case 7:  // set channel 7
      LPC_IOCON->PIO1_11 &= ~0x07;              //clear
      LPC_IOCON->PIO1_11 |= 0x01;               //P1.11 is ADC7
      LPC_IOCON->PIO1_11 &= ~(3<<3) ;           //close pull-up resistor and pull-dowm resistor
      LPC_IOCON->PIO1_11 &= ~(1<<7) ;           //Analog input mode.
      break;
      default:break;
   }
   LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<16);    //IOCON clock
   LPC_ADC->CR = (1<<Channel)|   /* bit7:bit0   select Channel*/
(24<<8);   /* bit15:bit8  clock set 2MHz 50/(24+1)*/
}

float ADC_Read(uint8_t Channel)
{
  float adc_value=0;
	LPC_ADC->CR |= (1 << 24) ;	
  while((LPC_ADC->DR[Channel]&0x80000000)==0);
	adc_value = (LPC_ADC->DR[Channel]>>6)&0x3FF;
	adc_value = (adc_value)/1024*100; // value /1024 *100
  return adc_value;      
}
