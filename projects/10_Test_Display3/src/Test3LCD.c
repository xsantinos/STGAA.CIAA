

/*==================[inclusions]=============================================*/
#include "main.h"
#include "led.h"
#include "Microinterface.h"
#include "teclas.h"
#include "Bitmaps.h"
#include "GLCDgui.h"
#include "window.h"
#include "button.h"
#include "text.h"
#include "picture.h"
#include "SysFont3x5.h"
#include "SystemFont5x7.h"
#include "GLCDguiEvent.h"

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

int main(void)
{
	GUI_StartLibrary ();
	char Login[10] = "Login";
	uint8_t* color = WHITE;
	char text[10] = "STGAA";

	GUI_Window_Create ( Login, color, text );
	GUI_Window_AddPicture (Login, "Logdraw", 5, 23, 48, 40, InicioBitmaps, BLACK );
	GUI_Window_AddText (Login, "row1", 60, 9, "SystemFont5x7", WHITE, "RECETA  : ....");
	GUI_Window_AddText (Login, "row2", 60, 17, "SystemFont5x7", WHITE, "PRODUCTO: ....");
	GUI_Window_AddText (Login, "row3", 60, 25, "SystemFont5x7", WHITE, "DOSIS   : ....");
	GUI_Window_AddText (Login, "row4", 60, 33, "SystemFont5x7", WHITE, "VOLUMEN : ....");
	GUI_Window_AddText (Login, "row5", 60, 41, "SystemFont5x7", WHITE, "REGENTE : ....");
	GUI_Window_AddText (Login, "row6", 60, 49, "SystemFont5x7", WHITE, "OPERARIO: ....");
	GUI_Window_Draw (Login);

//	GLCDLowLevel_SwapBuffer ();
	while(1)
		{
		asm("nop");
		}
}
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

