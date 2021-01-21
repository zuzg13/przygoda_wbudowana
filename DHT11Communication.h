/// @file DHT11Communication.h

#include "Timerlib.h"
#include "LCDlib.h"
#include <stdio.h>
#define DATA_PIN (1<<17)

/**
 * check if response from sesnor lasts specified time and is equal to specified value
 * @param wait - time to wait
 * @param margin - margin for time
 * @param pinValue - expected value
 */
void checkResponse(unsigned int wait, unsigned int margin, unsigned char pinValue);

/**
 * get data from sensor
 * @return 0 or 1
 */
int8_t getData(void);



