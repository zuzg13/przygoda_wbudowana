#include "DHT11Communication.h"

void checkResponse(unsigned int waitTime, unsigned int margin, unsigned char pinValue)
{
    int time = 0;
    int maxTime = waitTime + margin;

    startTimer();
    if(pinValue)
    {
        while(LPC_GPIO1->FIOPIN & PIN)
        {
            if(LPC_TIM0->TC > (maxTime)) break;
        }
    }
    else
    {
        while( !(LPC_GPIO1->FIOPIN & PIN) )
        {
            if(LPC_TIM0->TC > (maxTime)) break;
        }
    }
    time = stopTimer();

    if(time < (waitTime - margin) || time > maxTime)
    {
        printString("error", 100, 25, LCDBlack);
    }
}