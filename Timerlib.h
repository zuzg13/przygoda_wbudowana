/// @file Timerlib.h

#include "LPC17xx.h"

/**
@brief delay time
@param time - time for delay
*/
void delay(int time);

/**
 * @brief initialize timer0
 */
void initTimer0(void);

/**
 * @brief initialize timer1
 */
void initTimer1(void);

/**
@brief starts time0
*/
void startTimer0(void);

/**
@brief starts time1
*/
void startTimer1(void);

/**
@brief stops timer0
@return value of counter
*/
int stopTimer0(void);

/**
@brief stops timer1
@return value of counter
*/
int stopTimer1(void);
