#include "DHT11Communication.h"

void checkResponse(unsigned int waitTimeUS, unsigned int margin, unsigned char pinValue)
{
	int time = 0;
	int maxwait = waitTimeUS + margin;
	
	startTimer0();
	if(pinValue)
	{
		while(LPC_GPIO1->FIOPIN & DATA_PIN)
		{
			if(LPC_TIM0->TC > (maxwait)) break; 
		}
	}
	else
	{
		while( !(LPC_GPIO1->FIOPIN & DATA_PIN) )
		{
			if(LPC_TIM0->TC > (maxwait)) break; 
		}
	}
	time = stopTimer0();
	
	if(time < (waitTimeUS-margin) || time > maxwait) 
	{
		//printString("checkResponse() Error", 180, 200, LCDBlack);
	}
}


char getData(void)
{
  int time = 0;
	checkResponse(50,5,0); 
	startTimer0();
	
	while(LPC_GPIO1->FIOPIN & DATA_PIN)
	{
		if(LPC_TIM0->TC > 75)
		{
			return 2; //2 = Error (Timeout for 50us LOW)
		}
	}
	time = stopTimer0();
	
	if((time > (27-10)) && (time < (27+10))) 
	{
		return 0;
	}
	else if((time > (70-5)) && (time < (70+5)))
	{
		return 1;
	}
	else 
	{ 
		return 2; //Timeout for data pulse 
	}
}
