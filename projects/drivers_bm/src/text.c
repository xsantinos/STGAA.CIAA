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

#include "text.h"
//#include "GLCDgui.h"

#include "string.h"
//#include "GLCDLowLevel.h"
//#include "GLCDPrimitives.h"
#include "GLCDFonts.h"
//#include "GLCDColor.h"
#include "SystemFont5x7.h"
#include "SysFont3x5.h"

void GUI_Text_Create (TText* pText, char* _windowName, char* _name, uint16_t _xPos, uint16_t _yPos,
						char* _fontName, uint8_t _fontColor, char* _text)
{
	strcpy ( pText->windowName, _windowName);
	strcpy (pText->name, _name);
	strcpy (pText->fontName, _fontName);
	strcpy (pText->text, _text);

	pText->xPos = _xPos;
	pText->yPos = _yPos;
	pText->fontColor = _fontColor;
}

void GUI_Text_Edit(TText* pText, char* _text, uint8_t TextLength) //pasar tama�o del texto como argumento
{
	strncpy (pText->text, _text, TextLength); // y ac� usar strncpy, y como tercer par�metro la cantidad de caracteres a copiar
}

void GUI_Text_Draw ( TText* pText )
{
	// Draw button name
	GLCD_SelectFont(SysFont3x5, pText->fontColor);
	GLCD_CursorFreeTo(pText->xPos, pText->yPos);
	GLCD_FreePuts( pText->text );
}
