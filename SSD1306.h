/*
 * SSD1306.h
 *
 * Created: 08/11/2020 20:32:53
 *  Author: Alexey Ivanov
 *  v1.0
 *  C driver for SSD1306
 * GitHub: https://github.com/AlexAlexFr
 */ 


#ifndef SSD1306_H_
#define SSD1306_H_

#include <avr/io.h>
#include "i2c.h"
#include <util/twi.h>

#ifndef F_CPU
#define F_CPU	16000000UL
#endif
//define display resolution
#define SSD1306_H_RES		128
#define SSD1306_V_RES		64
#define SSD1306_PAGES_NB	SSD1306_V_RES/8-1

#define SSD1306_ADR			0b01111000	//SSD1306 ADR

#define SSD1306_WRADR		SSD1306_ADR			//SSD1306 write address
#define SSD1306_RDADR		SSD1306_ADR|0x01	//SSD1306 read address

#define SSD1306_DATA_TRANSMIT	0b01000000		//C0 = 0: indicates data transmission, DC = 1: follow only data bytes

//SSD1306 commands
#define SSD1306_SET_CONTRAST	0x81
#define SSD1306_ALL_DISP_ON		0xA4
#define SSD1306_DISPLAY_NORAM	0xA5
#define SSD1306_DISPLAY_RESET	0xA6
#define SSD1306_DISPLAY_INVERSE	0xA7
#define SSD1306_DISPLAY_OFF		0xAE
#define SSD1306_DISPLAY_ON		0xAF
#define SSD1306_SET_MUX			0xA8
#define SSD1306_NORM_SEG		0xA0
#define SSD1306_INV_SEG			0xA1

#define SSD1306_NORM_COM		0xC0
#define SSD1306_INV_COM			0xC8

#define SSD1306_DISPLAY_OFFSET	0xD3
#define SSD1306_DISPLAY_SL		0x40

#define SSD1306_COM_PIN_CONF	0xDA
#define SSD1306_NORMAL_PIN		0x02
#define SSD1306_ALTERNATIVE_PIN	0x10
#define SSD1306_PIN_REMAP		0x20

#define SSD1306_DISPLAY_CLK		0xD5

#define SSD1306_SET_PUMP		0x8D

#define SSD1306_SET_ADR_MODE	0x20
#define SSD1306_HORZ_MODE		0x00		//column increase, if column reaches end, page is increased
#define SSD1306_VERT_MODE		0x01		//page increase, if page reaches end, column is increased
#define SSD1306_PAGE_MODE		0x02		//column increase, if column reaches end, column at start, page not increased

#define SSD1306_SET_COLUMN		0x21
#define SSD1306_SET_PAGE		0x22

#define SSD1306_SCROLL_ON		0x2F
#define SSD1306_SCROLL_OFF		0x2E

#define SSD1306_SCROLL_RIGHT	0x26
#define SSD1306_SCROLL_LEFT		0x27

#define SSD1306_OFF				0x00
#define SSD1306_ON				0x01

#define SSD1306_SCROLLx5		0x00
#define SSD1306_SCROLLx64		0x01
#define SSD1306_SCROLLx128		0x02
#define SSD1306_SCROLLx256		0x03
#define SSD1306_SCROLLx3		0x04
#define SSD1306_SCROLLx4		0x05
#define SSD1306_SCROLLx25		0x06
#define SSD1306_SCROLLx2		0x07

/************************************************************************/
/* Initialize SSD1306                                                   */
/************************************************************************/
void SSD1306_Init();

void SSD1306_SendCommand(char cCommand);

/************************************************************************/
/* Fill all screen with the same byte                                   */
/************************************************************************/
void SSD1306_FillDisplay(char cByte);

/************************************************************************/
/* Set start and end columns for vertical or horizontal addressing modes
	 (horizontal position)												*/
/************************************************************************/
void SSD1306_SetColumns(char cColStart, char cColEnd);

/************************************************************************/
/* Set start and end pages for vertical or horizontal addressing modes
	 (vertical position)												*/
/************************************************************************/

void SSD1306_SetPages(char cPageStart, char cPageEnd);

/************************************************************************/
/* Set SSD1306 addressing mode
	cAdrMode = 0 : horizontal addressing mode
			 = 1 : vertical addressing mode
			 = 2 : page addressing mode                                 */
/************************************************************************/
void SSD1306_SetAdrMode(char cAdrMode);

/************************************************************************/
/* Send raw data from a buffer to RAM   
	*cBuffer - data to send
	iBufferLen - length of the buffer                                   */
/************************************************************************/
void SSD1306_SendBuffer(char* cBuffer, int iBufferLen);

/************************************************************************/
/* Clear entire display by writing 0x00 to RAM				            */
/************************************************************************/
void SSD1306_ClearDisplay();

/************************************************************************/
/* Write a string using cFont5x8 from current position
	*cText - string to write
	cTextLen - Length of the string							            */
/************************************************************************/
void SSD1306_WriteText(char* cText, char cTextLen);

/************************************************************************/
/* Write a char from cFont5x8 to current position                       */
/************************************************************************/
void SSD1306_WriteChar(char cChar);

/************************************************************************/
/* Draw Icon from array
	*cIcon - array which contains icon (icon must be placed in flash memory, 
	if it's not the case -> remove pgm_read_byte macro)
	cColumn : starting column
	sPage : starting page
	cIconWidth : icon's width
	cIconHeight : icon's height
															            */
/************************************************************************/
void SSD1306_DrawRectIcon(char* cIcon, char sColumn, char sPage, char cIconWidth, char cIconHeight);

/************************************************************************/
/* Display ON/OFF
	0 - off, 1 - on					                                    */
/************************************************************************/
void SSD1306_DisplayOnOff(char cDispOnOff);

/************************************************************************/
/* Set Contrast of display                                              */
/************************************************************************/
void SSD1306_SetContrast(char cContrast);

/************************************************************************/
/* Scroll ON/OFF
	0 - off, 1 -on					                                    */
/************************************************************************/
void SSD1306_ScrollOnOff(char cScrollOnOff);

/************************************************************************/
/* Horizontal Scroll command
cDir = 0: Right scroll, cDir = 1: Left Scroll
cStartPage = 0-7: Start Page for scroll
cInterval = 0-7: interval in terms of frame freq, see datasheet
cEndPage = 0-7: End page for scroll				                        */
/************************************************************************/
void SSD1306_HorizontalScroll(char cDir, char cStartPage, char cInterval, char cEndPage);

#endif /* SSD1306_H_ */