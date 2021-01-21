/// @file LCDlib.h

#include "Open1768_LCD.h"
#include "LCD_ILI9325.h"
#include "asciiLib.h"
#include <string.h>


/**
 * @brief print one character on screen with specified background
 * @param character - character to print
 * @param x - x coordinate
 * @param y - y coordinate
 * @param LCD_RegValue - color of printed character
 * @param LCD_BGValue - color of background
 */
void printChar(char character, int x, int y, uint16_t LCD_RegValue, uint16_t LCD_BGValue);

/**
 * print string on screen with white background
 * @param str - string to print
 * @param x - x coordinate
 * @param y - y coordinate
 * @param LCD_RegValue - color of string
 */
void printString(char* str, int x, int y,  uint16_t LCD_RegValue);

/**
 * print string on screen with white background
 * @param str - string to print
 * @param x - x coordinate
 * @param y- y coordinate
 * @param LCD_RegValue - color of string
 * @param LCD_BGValue - color of background
 */
void printStringBackground(char* str, int x, int y,  uint16_t LCD_RegValue, uint16_t LCD_BGValue);

/**
 * sets all background with specified color
 * @param LCD_RegValue - coor to set on background
 */
void setBackground(uint16_t LCD_RegValue);

/**
 * draw line using Bressenham algorithm
 * @param x1 - x start coordinate
 * @param y1 - y start coordinate
 * @param x2 - x end coordinate
 * @param y2 - y end coordinate
 * @param LCD_RegValue - color of line
 */
void drawLine(int x1, int y1, int x2, int y2, uint16_t LCD_RegValue);

