#include <LPC11xx.H>

void delay(){      // subroutine
	long int i;
	for(i=500000;i>0;i--){
	}
}
int main(void){
		
		LPC_GPIO1->DIR=0xffff;
	  LPC_GPIO1->DATA=0xffff;
	
	while(1){
		LPC_GPIO1->DATA&=~(1<<8);
		delay();
		LPC_GPIO1->DATA|=(1<<8);
		delay();
	}
}
