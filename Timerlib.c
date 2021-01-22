#include "Timerlib.h"

void initTimer0(void)
{
    LPC_TIM0->CTCR = 0;
    LPC_TIM0->PR  = 24;
    LPC_TIM0->TCR = 2;
}

void initTimer1(void)
{
    LPC_TIM1->CTCR = 0;
    LPC_TIM1->PR  = 24;
    LPC_TIM1->TCR = 2;
}

void delay(int time)
{
    LPC_TIM0->TCR = 2; // reset
    LPC_TIM0->TCR = 1; // enable
    while(LPC_TIM0->TC < time);
    LPC_TIM0->TCR = 0; // disable
}



void startTimer0(void)
{
    //delay(1);
    //counter = 0;

    LPC_TIM0->TCR = 2; // reset
    LPC_TIM0->TCR = 1; // enable
}

void startTimer1(void)
{
    //delay(1);
    //counter = 0;

    LPC_TIM1->TCR = 2; // reset
    LPC_TIM1->TCR = 1; // enable
}
 
int stopTimer0(void)
{
    LPC_TIM0->TCR = 0;
    return LPC_TIM0->TC;
}

int stopTimer1(void)
{
    LPC_TIM0->TCR = 0;
    return LPC_TIM0->TC;
}
