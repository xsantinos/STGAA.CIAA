/*
   ********************* Authors *********************
   ***** Laboratorio de Sistemas Embebidos (LSE) *****
   *****    http://laboratorios.fi.uba.ar/lse    *****
   ******************* 20/12/2011 ********************
     Ezequiel Espósito <ezequiel.esposito@gmail.com>
         Alan Kharsansky <akharsa@gmail.com>
       Federico Roasio <federoasio@gmail.com>
     Daniel Schermuk <daniel.schermuk@gmail.com>
   ***************************************************
*/

#include <string.h>
#include "button.h"

#include "GLCDLowLevel.h"
#include "GLCDPrimitives.h"
#include "GLCDFonts.h"
#include "GLCDColor.h"
#include "SystemFont5x7.h"

#define FALSE 	0
#define TRUE 	1

#ifndef NULL
#define NULL	0
#endif

void GUI_Button_Create (TButton* pButton, char* _windowName, char* _name, uint16_t _height, uint16_t _width,
						uint16_t _xPos,	uint16_t _yPos, uint8_t _color, char* _fontName, uint8_t _fontColor,
						char* _text)
{
	strcpy (pButton->windowName, _windowName);
	strcpy (pButton->name, _name);

	pButton->height = _height;
	pButton->width = _width;
	pButton->xPos = _xPos;
	pButton->yPos = _yPos;
	pButton->color = _color;
	strcpy(pButton->fontName, _fontName);
	strcpy (pButton->text, _text);
}

void GUI_Button_Draw ( TButton* pButton )
{
	uint8_t fontXPos;
	uint8_t fontYPos;
	size_t cantChar;
	uint8_t charWidth;
	uint8_t charHeight;

	GLCDPrimitives_FillRect (pButton->xPos, pButton->yPos, pButton->width, pButton->height, pButton->color);

	// Button name position
	cantChar = strlen(pButton->text);
	charWidth = System5x7[FONT_FIXED_WIDTH];
	charHeight = System5x7[FONT_HEIGHT];
	fontXPos = pButton->xPos + (pButton->width - (charWidth+1) * cantChar) / 2;
	fontYPos = pButton->yPos + (pButton->height - charHeight) / 2;

	// Draw button name
	GLCD_SelectFont(pButton->fontName, pButton->fontColor);
    GLCD_CursorFreeTo(fontXPos, fontYPos);
    GLCD_FreePuts( pButton->text );
}
