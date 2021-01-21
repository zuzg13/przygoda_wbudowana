#include <lpc17xx.h>
#include <stdio.h> 
#include <stdlib.h>
#include "LCDlib.h"
#include "Timerlib.h"
#include "DHT11Communication.h"
#include "PIN_LPC17xx.h"
#include "Board_Buttons.h" // ::Board Support:Buttons
#include "IAP.h"


#define SECTOR 29
#define START 0x00078000
#define END 0x0007FFFF
#define DATA_PIN (1<<17)



int main(void)
{
	
	int8_t dataBits[40] = {0};
	char dataBytes[5] = {0};
	uint32_t data_from_past[6];
	
	uint32_t* memory_ptr = (uint32_t*) START;
	
	data_from_past[0] = *(memory_ptr);
	data_from_past[1] = *(memory_ptr+1);
	data_from_past[2] = *(memory_ptr+2);
	data_from_past[3] = *(memory_ptr+3);
	data_from_past[4] = *(memory_ptr+4);
	data_from_past[5] = *(memory_ptr+5);

		float average_minute_temp = 0.;
		float average_ten_temp = 0.;
    float average_minute_hum = 0.;
    float average_ten_hum=0.;
		int counter1 = 0;
    int counter2 = 0;

	char xc[13];
	char xc2[13];
	char xc3[13];
	initTimer0();
	initTimer1();
	
	
	int pos_x = 1;
	int start_x=10;

	Buttons_Initialize();
	int state = 2; //ekran z wypisanymi danymi
	
	lcdConfiguration();
	init_ILI9325();
	setBackground(LCDWhite);

	PIN_Configure(1, 17, PIN_FUNC_0, PIN_PINMODE_PULLUP, 0);
	startTimer1();
	
	/*int tmp1;
	uint32_t tmp;// = {0};
						tmp1 = Chip_IAP_PreSectorForReadWrite(SECTOR, SECTOR);
						sprintf(xc3, "%d", tmp1);
						printString(xc3, 50, 15, LCDBlue);
						tmp1 = Chip_IAP_EraseSector(SECTOR, SECTOR);
						sprintf(xc3, "%d", tmp1);
						printString(xc3, 30, 15, LCDBlue);
						Chip_IAP_PreSectorForReadWrite(SECTOR, SECTOR);
						tmp = 5;
						//tmp[1] = average_minute_hum/(float)(counter1);
							
						tmp1 = Chip_IAP_CopyRamToFlash(START, &tmp, 512);
						sprintf(xc3, "%d", tmp1);
						printString(xc3, 10, 15, LCDBlue);
						tmp = 10;//average_minute_hum/(float)(counter2);
						//Chip_IAP_PreSectorForReadWrite(SECTOR, SECTOR);
						//tmp1 = Chip_IAP_CopyRamToFlash(START+512, &tmp, 512);
						//sprintf(xc3, "%d", tmp1);
						//printString(xc3, 10, 30, LCDBlue);*/

	while(1)
	{
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
		
		
		LPC_GPIO1->FIODIR |= DATA_PIN; // ustawienie pinu na stan 1
		
		LPC_GPIO1->FIOCLR |= DATA_PIN; //ustawienie pinu na stan 0 i czekanie przez 18 ms
		delay(18000); 
		
		LPC_GPIO1->FIODIR &= ~(DATA_PIN);// ustawienie pinu na stan 1
		
		
		startTimer0(); //czekamy od 20 do 40 us na odpowiedz
		while((LPC_GPIO1->FIOPIN & DATA_PIN) != 0)
		{
			if(LPC_TIM0->TC > 40) break; //Timeout
		}
		unsigned int time = stopTimer0();
		
		if(time < 10 || time > 40) 
		{ 
			printString("Failed to communicate with sensor", 200, 125,  LCDBlack);
		}
		
		// czekamy na 80 us sygnalu 0 i nastepnie 80 us sygnalu 1
		checkResponse(80,5,0);
		checkResponse(80,5,1);
		
		
		// zczytywanie danych
		char data;
		for(int i=0; i < 40; i++)
		{
			data = getData();
			
			if(data == 0 || data == 1)
			{
				dataBits[i] = data;
			}
			//else printString("Data error", 130, 150,  LCDBlack);
		}
	
		
		// konwersja danych
		data = 0;
		for(int i=0; i<5; i++) // licznik bajtow
		{
			for(int j=0; j<8; j++) 
			{
				if( dataBits[ 8*i + j ] )
					data |= (1<<(7-j)); 
			}
			dataBytes[i] = data;
			data = 0;
		}

		if(LPC_TIM1->TC > 60000000)
    {
		    stopTimer1();
				
		    average_ten_temp += average_minute_temp/(float)(counter1);
        average_ten_hum += average_minute_hum/(float)(counter1);
        if(counter2>10)
        {
           counter2 = 0;
        }
        else
        {		int tmp1;
            counter2++;
            
						
						tmp1 = Chip_IAP_PreSectorForReadWrite(SECTOR, SECTOR);
						//sprintf(xc3, "%d", tmp1);
						//printString(xc3, 50, 15, LCDBlue);
						tmp1 = Chip_IAP_EraseSector(SECTOR, SECTOR);
						//sprintf(xc3, "%d", tmp1);
						//printString(xc3, 30, 15, LCDBlue);
						Chip_IAP_PreSectorForReadWrite(SECTOR, SECTOR);
						//float a = average_minute_temp/counter1;///(float)(counter1);
						//sprintf(xc3, "%f", a);
						//printString(xc3, 60, 15, LCDGreen);
					//float b = a;
							data_from_past[5] = data_from_past[4];
							data_from_past[4] = data_from_past[3];
							data_from_past[3] = data_from_past[2];
							data_from_past[2] = data_from_past[1];
							data_from_past[0] = average_minute_temp/(float)(counter1);//(uint32_t)(average_minute_temp/(float)(counter1));
							data_from_past[1] = average_minute_hum/(float)(counter1);
						//tmp[1] = average_minute_hum/(float)(counter1);
							
						Chip_IAP_CopyRamToFlash(START, data_from_past, 512);
						//sprintf(xc3, "%d", tmp1);
						//printString(xc3, 10, 15, LCDBlue);
						//tmp = average_minute_hum/(float)(counter1);
						//Chip_IAP_PreSectorForReadWrite(SECTOR, SECTOR);
						//tmp1 = Chip_IAP_CopyRamToFlash(START+512, &tmp, 512);
						//sprintf(xc3, "%d", tmp1);
						//printString(xc3, 10, 30, LCDBlue);
						average_minute_temp = 0.;
						average_minute_hum = 0.;
						counter1 = 0;
        }
				
		    startTimer1();
     }
		else
    {
				if((int)dataBytes[0]<200 || (int)dataBytes[2] < 100)
				{
					average_minute_temp += dataBytes[0]; // + dataBytes[1]/100
          average_minute_hum += dataBytes[2]; // + dataBytes[3]/100
					counter1++;
				}			
		}

		
		
		if(state == 2)
		{
			
			if(average_minute_temp/(float)counter1 < 100 || average_minute_hum/(float)counter1 < 100)
			{
					printString("Aktualna srednia minutowa:", 225, 15, LCDBlue);
					sprintf(xc, "%4.2f %4.2f", average_minute_temp/(float)counter1, average_minute_hum/(float)counter1);
					printString(xc, 200, 15, LCDBlue);
			}
			
			if(counter2>0)
			{
					printString("Aktualna srednia 10 minutowa:", 170, 15, LCDBlue);
					sprintf(xc2, "%4.2f %4.2f", average_ten_temp/(float)counter2, average_ten_hum/(float)counter2);
					printString(xc2, 145, 15, LCDBlue);
			}
			
			printString("Wartosci z przeszlosci: ", 110, 15, LCDBlue);
					uint32_t* tmp = (uint32_t*) START;
					//sprintf(xc3, "%d, %d, %d, %d", *tmp, *(tmp+1), *(tmp+2), *(tmp+3));
					sprintf(xc3, "%dC %d%%", *tmp, *(tmp+1));
					printString(xc3, 90, 15, LCDBlue);
					sprintf(xc3, "%dC, %d%%", *(tmp+2), *(tmp+3));
					printString(xc3, 75, 15, LCDBlue);
					sprintf(xc3, "%dC, %d%%", *(tmp+4), *(tmp+5));
					printString(xc3, 60, 15, LCDBlue);
			
		}
		else
		{
			printString(xc, 230, 160, LCDWhite);
				
			
			int temp_y = 10*pos_x+15;
			int temp_x = ((int)(dataBytes[0])-start_x)* 10 + 5; 
			int hum_x = ((int)(dataBytes[2])-start_x)* 10 + 5; 
			
			if(dataBytes[0]>32 || dataBytes[0]<10)
				temp_x = 0;

			drawLine(temp_x, temp_y, temp_x, temp_y+10, LCDGreen);
			drawLine(hum_x, temp_y, hum_x, temp_y+10, LCDBlue);
			if(pos_x<31)
				pos_x ++;
			else
			{
				pos_x=1;
				setBackground(LCDWhite);
				drawLine(5,5,225,5,LCDRed);
				drawLine(5,5,5,310,LCDRed);
				for(int i = 1; i <= 22; i++)
				{
					drawLine(i*10+5,1,i*10+5,10,LCDRed);
				}
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
		
		// czekamy ok 1 s przed kolejna proba komunikacji
		delay(1000000); 
	}

}

// jak zwiekzyc stos
/*
device->startup.s->configuration wizard
*/

