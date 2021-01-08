#include "LPC17xx.h"
#include "LCDlib.h"
#include "Timerlib.h"
#include <stdio.h>
#define PIN (1<<17)

 
int main(){
	
	lcdConfiguration();
	init_ILI9325();
	
	setBackground(LCDWhite);
	
	char xc[10];

	//printString("y=2x+4", 200, 50, LCDBlack);
	
	LPC_GPIO1->FIODIR |= PIN;
	LPC_GPIO1->FIOCLR |= PIN;
	delay(18000);
	
	LPC_GPIO1->FIODIR &= ~(PIN);

	startTimer();
	
	while(LPC_GPIO1->FIOPIN & PIN)
	{
		if(LPC_TIM0->TC>40) break;
	}
	int t = stopTimer();
	
	if(t<10 || t>40)
	{
		printString("ERROR", 200, 50, LCDBlack);
		sprintf(xc, "%d", t);
		printString(xc, 100, 25, LCDBlack);
	}
	else
	{
		printString("Good!", 200, 50, LCDBlack);
	}
	
	
	
	while(1){}
}

