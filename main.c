#include <lpc17xx.h>
#include <stdio.h> 
#include "LCDlib.h"
#include "Timerlib.h"
#include "DHT11Communication.h"
#include "PIN_LPC17xx.h"
#include "Board_Buttons.h" // ::Board Support:Buttons



#define DATA_PIN (1<<17)

int main(void)
{
	//unsigned char dataBits[40] = {0};
	//char dataBytes[5] = {0};
	uint8_t dataBits[40] = {0};
	uint8_t dataBytes[5] = {0};
	
	char xc[13];
	initTimer0();
	initTimer1();
	
	int pos_x = 1;
	int start_y=10;

	Buttons_Initialize();
	int state = 1; //ekran z wypisanymi danymi
	
	lcdConfiguration();
	init_ILI9325();
	setBackground(LCDWhite);

	PIN_Configure(1, 17, PIN_FUNC_0, PIN_PINMODE_PULLUP, 0);
	
	
	/*while(1){
		
		if(Buttons_GetState()==1)
		{	
			while(Buttons_GetState()!=0){}
			if(state == 1) 
				state =2;
			else
				state = 1;		
		}
		
		printString(xc, 180, 50, LCDWhite);
			sprintf(xc, "stan = %d", state );
			printString(xc, 180, 50, LCDBlue);
		
	}*/
	
	
	while(1)
	{
		if(Buttons_GetState()==1)
		{	
			while(Buttons_GetState()!=0){}
			if(state == 1) 
				state =2;
			else
				state = 1;		
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
		
		
		if(state == 2)
		{
			//printString(xc, 180, 50, LCDWhite);
			//sprintf(xc, "wartosci z przeszlosci + czas");
			//printString(xc, 180, 50, LCDBlue);
		}
		else
		{
			printString(xc, 230, 160, LCDWhite);
			sprintf(xc, "T = %dC, H = %d%%", dataBytes[0], dataBytes[2]);
			printString(xc, 230, 160, LCDBlack);
			drawLine(5,5,225,5,LCDRed);
			drawLine(5,5,5,310,LCDRed);
			for(int i = 1; i <= 22; i++)
			{
				drawLine(i*10+5,1,i*10+5,10,LCDRed);
			}
			
			int temp_y = 10*pos_x+15;
			int temp_x = ((int)(dataBytes[0])-start_y)*10 + 10; 
			
			
			//printString("*", temp_y, temp_x, LCDGreen);
			drawLine(temp_x, temp_y, temp_x, temp_y+10, LCDGreen);
			if(pos_x<31)
				pos_x ++;
			else
			{
				pos_x=1;
				setBackground(LCDWhite);
			}
			
				
			//printString("*", , , LCDBlue);
			
			
		}
		
		
		// czekamy ok 1 s przed kolejna proba komunikacji
		delay(1000000); 
	}

}


