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

char getData(void)
{
    int time = 0;

    checkResponse(50,5,0); // each data bit starts with 50 us low

    startTimer();
    while(LPC_GPIO1->FIOPIN & PIN)
    {
        if(LPC_TIM0->TC > 75)
        {
            return 2;
        }
    }
    time = stopTimer();

    if((time > (27-10)) && (time < (27+10)))  // 26-28 high is for 0
    {
        return 0;
    }
    else if((time > (70-5)) && (time < (70+5))) // 70 high is for 1
    {
        return 1;
    }
    else
    {
        return 2;
    }
}