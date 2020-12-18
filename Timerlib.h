#include "LPC17xx.h"
#define PCLK_TIMER0  24 //value for prescaler

#define MiliToMicroSec(x)  (x*1000) //converting seconds


/**
@brief delay time
@param time - time for delay
*/
void delay(int time);

void initTimer(void);

/**
@brief starts time counter
*/
void startTimer(void);

/**
@brief stops time counter
@return value of counter
*/
int stopTimer(void);

/**
@brief returns current value of counter
@return value of counter
*/
int getCounter(void);

/**
@brief calculate value to put into prescaler
@param timerPclkBit
@return value to put into prescaler
*/
unsigned int prescale(uint8_t timerPclkBit);