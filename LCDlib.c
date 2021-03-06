#include "LCDlib.h"

 void printChar(char character, int x, int y, uint16_t LCD_RegValue, uint16_t LCD_BGValue)
 {
	unsigned char znak[16];
	GetASCIICode(0, znak, character);
	
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
			else
			{
				lcdSetCursor(x-i, y-j);
				lcdWriteReg(DATA_RAM, LCD_BGValue);
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
		printChar(str[k], x2, y2, LCD_RegValue, LCDWhite);		
	 }
	
 }
 
 void printStringBackground(char* str, int x, int y,  uint16_t LCD_RegValue, uint16_t LCD_BGValue)
 {
	 int size = strlen(str);
	 int x2, y2;
	 
	 for(int k=0;k<size;k++)
	 {
	 	x2 = x;
		y2 = y+k*10;
		printChar(str[k], x2, y2, LCD_RegValue, LCD_BGValue);		
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
	
	
 void drawLine(const int x1, const int y1, const int x2, const int y2, uint16_t LCD_RegValue)
 {
     // ancillary variables
     int d, dx, dy, ai, bi, xi, yi;
     int x = x1, y = y1;
     // determining the direction of drawing in OX axis
     if (x1 < x2)
     {
         xi = 1;
         dx = x2 - x1;
     }
     else
     {
         xi = -1;
         dx = x1 - x2;
     }
     // determining the direction of drawing in OY axis
     if (y1 < y2)
     {
         yi = 1;
         dy = y2 - y1;
     }
     else
     {
         yi = -1;
         dy = y1 - y2;
     }
     // first pixel
     lcdSetCursor(x, y);
     lcdWriteReg(DATA_RAM, LCD_RegValue);
		 
     // OX axis
     if (dx > dy)
     {
         ai = (dy - dx) * 2;
         bi = dy * 2;
         d = bi - dx;
         // loop through x
         while (x != x2)
         {
             // ratio test
             if (d >= 0)
             {
                 x += xi;
                 y += yi;
                 d += ai;
             }
             else
             {
                 d += bi;
                 x += xi;
             }
	     lcdSetCursor(x, y);
	     lcdWriteReg(DATA_RAM, LCD_RegValue);
         }
     }
     // OY axis
     else
     {
         ai = ( dx - dy ) * 2;
         bi = dx * 2;
         d = bi - dy;
         // loop through y
         while (y != y2)
         {
             // ratio test
             if (d >= 0)
             {
                 x += xi;
                 y += yi;
                 d += ai;
             }
             else
             {
                 d += bi;
                 y += yi;
             }
             lcdSetCursor(x, y);
	     lcdWriteReg(DATA_RAM, LCD_RegValue);
         }
     }
 }
		
