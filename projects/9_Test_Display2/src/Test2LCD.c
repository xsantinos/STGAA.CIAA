

/*==================[inclusions]=============================================*/
#include "main.h"
#include "led.h"
#include "Microinterface.h"
#include "teclas.h"
#include "Bitmaps.h"
#include "GLCDgui.h"
#include "window.h"
#include "button.h"
#include "textSlider.h"
#include "text.h"
#include "picture.h"
#include "SysFont3x5.h"
#include "GLCDguiEvent.h"
#include "object.h"


#include "GLCDColor.h"
#include "GLCDPrimitives.h"
#include "GLCDLowLevel.h"
#include "GLCDFonts.h"

#include "string.h"
/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

uint8_t _delayCounter;
typedef struct {
char c[25];
} texto;
texto T;

int main(void)
{

	strcpy (T.c, "la vi venir");
//	GUI_DefineHeapMalloc (pvPortMalloc);
//	GUI_DefineHeapFree (vPortFree);
//	GUI_StartLibrary ();
////	DSP_CreateGUI();
//
//	GLCD_SelectFont(SysFont3x5, WHITE);
//	GLCD_CursorFreeTo(12, 52);
//	GLCD_FreePuts( T.c );
//
//
//	GLCDPrimitives_DrawLine(20,20,20,50, WHITE);
//	GLCDPrimitives_DrawLine(20,20,50,50, WHITE);
//	GLCDPrimitives_DrawLine(50,20,50,50, WHITE);
//	GLCDPrimitives_DrawRoundRect(70,20,30,30,5, WHITE);
//	GLCDPrimitives_SetDot(110,50, WHITE);
//	GLCDPrimitives_DrawRect(10,10,110,50, WHITE);
//	GLCDPrimitives_SetDot(0,0, WHITE);
//	GLCDPrimitives_SetDot(0,63, WHITE);
//	GLCDPrimitives_SetDot(127,0, WHITE);
//	GLCDPrimitives_SetDot(127,63, WHITE);
//
//
//	GLCDLowLevel_SwapBuffer ();
//	while(1)
//		{
//		asm("nop");
//		}
}
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

