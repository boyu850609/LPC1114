#include "lpc11xx.h"
#include "ADC.h"
#include "PWM.h"

uint16_t cycle=1000;
float duty=0;

int main()
{
	ADC_Init(6);
	
	while(1)
	{
		duty = ADC_Read(6);
		T16B0M0_PWM_Init(cycle,duty);
	}
}
