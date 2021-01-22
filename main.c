/// @file main.c

#include <lpc17xx.h>
#include <stdio.h> 
#include <stdlib.h>
#include "LCDlib.h"
#include "Timerlib.h"
#include "DHT11Communication.h"
#include "PIN_LPC17xx.h"
#include "Board_Buttons.h"
#include "IAP.h"

//macros created based on LPC1768 user manual
#define SECTOR 29
#define START 0x00078000
#define END 0x0007FFFF
#define DATA_PIN (1<<17)

/**
 * Main entry point of the program.
*/
int main(void)
{
	
	int8_t dataBits[40] = {0}; // storage for bits send by dht11
	int8_t dataBytes[5] = {0}; // bits converted to bytes
	uint32_t data_from_past[6]; // storage for data written in flash memory
	
	uint32_t* memory_ptr = (uint32_t*) START; // pointer to place in flash memory where data is first written
	
	data_from_past[0] = *(memory_ptr);
	data_from_past[1] = *(memory_ptr+1);
	data_from_past[2] = *(memory_ptr+2);
	data_from_past[3] = *(memory_ptr+3);
	data_from_past[4] = *(memory_ptr+4);
	data_from_past[5] = *(memory_ptr+5);
	
	/* initalization of average temperature and humidity values */
	float average_minute_temp = 0.;
	float average_ten_temp = 0.;
    	float average_minute_hum = 0.;
    	float average_ten_hum=0.;
	
	/* initalization of counters */
	int counter1 = 0;
    	int counter2 = 0;

	char xc[13];
	char xc2[13];
	char xc3[13];
		
	/* initialization of timers*/
	initTimer0();
	initTimer1();
	
	/* initialization of values that will be used in plot*/
	int pos_x = 1; // start position of x axis
	int start_y = 10; // start position of y axis
		
	/* initializtion of buttons and button's state value*/
	Buttons_Initialize();
	int state = 2;
		
	/* initializtion of basic settings in LCD*/
	lcdConfiguration();
	init_ILI9325();
	setBackground(LCDWhite);
		
	/* PIN configuring */
	PIN_Configure(1, 17, PIN_FUNC_0, PIN_PINMODE_PULLUP, 0);
		
		
	startTimer1();
	

	while(1)
	{
		
		/* checking state of button to switch between screens */
		if(Buttons_GetState()==1)
		{	
			while(Buttons_GetState()!=0){}
				
			if(state == 1) 
			{
				state = 2;
			}
				
			else
				state = 1;	

			setBackground(LCDWhite);
		}
		
		
		LPC_GPIO1->FIODIR |= DATA_PIN; // setting pin for 1 value
		
		LPC_GPIO1->FIOCLR |= DATA_PIN; //setting pin for 0 value and waiting for 18 ms
		delay(18000); 
		
		LPC_GPIO1->FIODIR &= ~(DATA_PIN); // setting pin for 1 value
		
		
		startTimer0(); // waitning between 10 to 40 us for response
		
		while((LPC_GPIO1->FIOPIN & DATA_PIN) != 0)
		{
			if(LPC_TIM0->TC > 40) break; //Timeout
		}
		
		unsigned int time = stopTimer0();
		
		if(time < 10 || time > 40) 
		{ 
			printString("Failed to communicate with sensor", 200, 125,  LCDBlack);
		}
		
		// waiting for 80 us of 0 and  80 us of 1 from sensor
		checkResponse(80,5,0);
		checkResponse(80,5,1);
		
		
		// fetching data from DHT11 sensor
		int8_t data;
		for(int i=0; i < 40; i++)
		{
			data = getData();
			
			if(data == 0 || data == 1)
			{
				dataBits[i] = data;
			}
			//else printString("Data error", 130, 150,  LCDBlack);  // uncomment this line to check data error 
										// but due to various technical states of sensor a few are inevitable
		}																													//technical issues of sensor it is inevitable
	
		
		// converting data from bits do bytes
		data = 0;
		for(int i=0; i<5; i++) // bit counter
		{
			for(int j=0; j<8; j++) 
			{
				if( dataBits[ 8*i + j ] )
					data |= (1<<(7-j)); 
			}
			dataBytes[i] = data;
			data = 0;
		}
		
		/* calculating average values and writing it to flash memory */
		if(LPC_TIM1->TC > 60000000) // if one minute lasts, new values are calculated
        	{
		    stopTimer1();
				
		    average_ten_temp += average_minute_temp/(float)(counter1);
            	    average_ten_hum += average_minute_hum/(float)(counter1);
			
            	    if(counter2 > 10)
            	    {
                 	counter2 = 0;
                	average_ten_temp = 0;
                	average_ten_hum = 0;
            	    }
            	    else
             	    {
                	counter2++;
            
			if(counter2 == 1) // new average values are written to flash memory only once in every 10 minutes - for the firtst time
			{
				Chip_IAP_PreSectorForReadWrite(SECTOR, SECTOR);
				Chip_IAP_EraseSector(SECTOR, SECTOR);
				Chip_IAP_PreSectorForReadWrite(SECTOR, SECTOR);
								
				/* guarantee rewriting of values*/
				data_from_past[5] = data_from_past[3];
				data_from_past[4] = data_from_past[2];
				data_from_past[3] = data_from_past[1];
				data_from_past[2] = data_from_past[0];
							
				data_from_past[0] = average_minute_temp/(float)(counter1);
				data_from_past[1] = average_minute_hum/(float)(counter1);
						
				Chip_IAP_CopyRamToFlash(START, data_from_past, 512);

			}
						
			average_minute_temp = 0.;
			average_minute_hum = 0.;
			counter1 = 0;
            	    }
				
		    startTimer1();
        	}
		else
        	{
			/* add new values to sum*/
			if((int)dataBytes[0]<200 && (int)dataBytes[2] < 100)
			{
				average_minute_temp += dataBytes[0]; 
                    		average_minute_hum += dataBytes[2];
				counter1++;
			}			
		}

		
		
		if(state == 2) // if state == 2 prints data
		{
			
			if(average_minute_temp/(float)counter1 < 100 || average_minute_hum/(float)counter1 < 100)
			{
					printString("Aktualna srednia minutowa:", 225, 15, LCDBlue);
					sprintf(xc, "%4.2fC %4.2f %%", average_minute_temp/(float)counter1, average_minute_hum/(float)counter1);
					printString(xc, 200, 15, LCDBlue);
			}
			
			if(counter2>0 && (average_ten_temp/(float)counter2 < 100 || average_ten_hum/(float)counter2 < 100))
			{
					printString("Aktualna srednia 10 minutowa:", 170, 15, LCDBlue);
					sprintf(xc2, "%4.2fC %4.2f %%", average_ten_temp/(float)counter2, average_ten_hum/(float)counter2);
					printString(xc2, 145, 15, LCDBlue);
			}
			
			printString("Wartosci z przeszlosci: ", 110, 15, LCDBlue);
			uint32_t* tmp = (uint32_t*) START;
			sprintf(xc3, "%dC %d %%", *tmp, *(tmp+1));
			printString(xc3, 90, 15, LCDBlue);
			sprintf(xc3, "%dC %d %%", *(tmp+2), *(tmp+3));
			printString(xc3, 75, 15, LCDBlue);
			sprintf(xc3, "%dC %d %%", *(tmp+4), *(tmp+5));
			printString(xc3, 60, 15, LCDBlue);
			
		}
		else //if state == 1 print plots
		{
			printString(xc, 230, 160, LCDWhite);
				
			int temp_y = 10*pos_x+15;
			int temp_x = ((int)(dataBytes[0])-start_y)* 10 + 5; 
			int hum_x = ((int)(dataBytes[2])-start_y)* 10 + 5; 
			
			if(dataBytes[0]>32 || dataBytes[0]<10)
				temp_x = 0;

			drawLine(temp_x, temp_y, temp_x, temp_y+10, LCDGreen);
			drawLine(hum_x, temp_y, hum_x, temp_y+10, LCDBlue);

			if(pos_x<31)
			{
                		pos_x++;
            		}
			else
			{
				pos_x=1;
				setBackground(LCDWhite);
				drawLine(5,5,225,5,LCDRed);
				drawLine(5,5,5,310,LCDRed);

				for(int i = 1; i <= 22; i++)
	                		drawLine(i*10+5,1,i*10+5,10,LCDRed);

			}

			sprintf(xc, "T = %dC, H = %d%%", dataBytes[0], dataBytes[2]);
			printString(xc, 230, 160, LCDBlack);

			drawLine(5,5,225,5,LCDRed);
			drawLine(5,5,5,310,LCDRed);
			
			for(int i = 1; i <= 22; i++)
			{
				drawLine(i*10+5,1,i*10+5,10,LCDRed);
			}
				
		}
		
		// we wait at least 1 s before trying to communicate with sensor again
		delay(1000000); 
	}

}

