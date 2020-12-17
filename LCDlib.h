#include "Open1768_LCD.h"
#include "LCD_ILI9325.h"
#include "asciiLib.h"
#include <string.h>



void printChar(char znaczek, int x, int y, uint16_t LCD_RegValue);
void printString(char* str, int x, int y,  uint16_t LCD_RegValue);
void setBackground(uint16_t LCD_RegValue);