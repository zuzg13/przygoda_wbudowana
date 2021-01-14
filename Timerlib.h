#include "LPC17xx.h"



/**
@brief delay time
@param time - time for delay
*/
void delay(int time);

void initTimer0(void);
void initTimer1(void);
/**
@brief starts time counter
*/
void startTimer0(void);
void startTimer1(void);


/**
@brief stops time counter
@return value of counter
*/
int stopTimer0(void);
int stopTimer1(void);


/**
@brief returns current value of counter
@return value of counter
*/
//int getCounter(void);
