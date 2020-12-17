#include "LCDlib.h"

 void printChar(char znaczek, int x, int y, uint16_t LCD_RegValue)
 {
		unsigned char znak[16];
		GetASCIICode(0, znak, znaczek);
	
		for(int i=0;i<16;i++)
		{		
			uint8_t tmp = znak[i];
			for(int j=0;j<8;j++)
			{
				if(tmp & (1<<j))
				{
					lcdSetCursor(x-i, y-j);
					lcdWriteReg(DATA_RAM, LCD_RegValue);
				}
						
			}
		}
 }

 void printString(char* str, int x, int y,  uint16_t LCD_RegValue)
 {
	 int size = strlen(str);
	 int x2, y2;
	 
	 for(int k=0;k<size;k++)
	 {
			x2 = x;
			y2 = y+k*10;
			printChar(str[k], x2, y2, LCD_RegValue);		
	 }
	
 }
 
  void setBackground(uint16_t LCD_RegValue)
	{
		lcdSetCursor(0, 0);
		lcdWriteReg(DATA_RAM, LCD_RegValue);

		for(int i=0;i<320;i++)
		{
				for(int j=0;j<240;j++)
					lcdWriteData(LCD_RegValue);
		}
	}