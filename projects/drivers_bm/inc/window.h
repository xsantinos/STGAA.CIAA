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

#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "stdint.h"
#include "GLCDguiEvent.h"
#include "button.h"
#include "picture.h"
#include "text.h"

#define MAX_WINDOWS 3
#define WINDOWNAME_LENGTH 10
#define WINDOWTEXT_LENGTH 15

#define MAX_PIC 4
#define MAX_TEXT 8
#define MAX_BUTTON 2

// *********************
// Structures Definition
// *********************

struct ObjectList {
	TPicture Pictures[MAX_PIC];
	uint8_t N_Pictures;

	TText Texts[MAX_TEXT];
	uint8_t N_Texts;

	TButton Buttons[MAX_BUTTON];
	uint8_t N_Buttons;

//	TTextSlider TextSliders[MAX_TEXTSL];
//	uint8_t N_TextSliders;
};
typedef struct ObjectList OList;

struct Window
{
	char name[WINDOWNAME_LENGTH];
	uint8_t color;
	char text[WINDOWTEXT_LENGTH];
	OList WindowObjects;
};
typedef struct Window TWindow;


struct WindowList
{
	TWindow Windows[MAX_WINDOWS];
	uint8_t N_Windows;
};
typedef struct WindowList WList;

// ****************
// Public functions
// ****************

void GUI_Window_ListInit ();

void GUI_Window_Create ( char* _name, uint8_t* _color, char* _text );

void GUI_Window_ObjectListInit (OList* pOList);

void GUI_Window_DrawObjects (OList* pOList);

void GUI_Window_Draw ( char* windowName );

void GUI_Window_RedrawActiveWindow ();

void GUI_Window_RaiseEvent (GLCDgui_TEvent* event);

void GUI_Window_GetText (const char* const textName, TText* pText);

void GUI_Window_GetPicture (const char* const pictureName, TPicture* pPicture);

#endif
