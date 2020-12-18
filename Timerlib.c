#include "Timerlib.h"


extern unsigned int SystemCoreClock;
volatile int counter=0;

void TIMER0_IRQHandler(void)
{	
	LPC_TIM0->IR = 1;
	counter++;
}

void initTimer(void)
{
    LPC_TIM0->CTCR = 0;
    LPC_TIM0->PR  = prescale(PCLK_TIMER0);
    LPC_TIM0->TCR = 2;
}

void delay(int time)
{
    LPC_TIM0->TCR = 2; // reset
    LPC_TIM0->TCR = 1; // enable
    while(LPC_TIM0->TC < time);
    LPC_TIM0->TCR = 0; // disable

    // old version
	//LPC_TIM0->PR  = prescale(PCLK_TIMER0);
	//LPC_TIM0->MR0 = time;
	//LPC_TIM0->MCR = 1<<1 | 1;
	//LPC_TIM0->TCR = 1;
	//NVIC_EnableIRQ(TIMER0_IRQn);
}

int getCounter(void)
{
	return counter;
}

void startTimer(void)
{
	//delay(1);
	//counter = 0;

	LPC_TIM0->TCR = 2; // reset
	LPC_TIM0->TCR = 1; // enable
}
 
int stopTimer(void)
{
    LPC_TIM0->TC = 0;
	return LPC_TIM0->TC;
}

 unsigned int prescale(uint8_t timerPclkBit)
{
    unsigned int pclk,prescalarForUs;
    pclk = (LPC_SC->PCLKSEL0 >> timerPclkBit) & 0x03;  /* get the pclk info for required timer */

    switch ( pclk )                                    /* Decode the bits to determine the pclk*/
    {
    case 0x00:
        pclk = SystemCoreClock/4;
        break;

    case 0x01:
        pclk = SystemCoreClock;
        break; 

    case 0x02:
        pclk = SystemCoreClock/2;
        break; 

    case 0x03:
        pclk = SystemCoreClock/8;
        break;

    default:
        pclk = SystemCoreClock/4;
        break;  
    }

    prescalarForUs =pclk/1000000 - 1;                    /* Prescalar for 1us (1000000Counts/sec) */

    return prescalarForUs;
}