

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

struct tex{
	char name[10];
	uint8_t i;
};
typedef struct tex TEXTO;

int main(void)
{
	GUI_StartLibrary ();
	char name[10] = "hola";
	uint8_t* color = BLACK;
	char text[10] = "texto";

	GUI_Window_Create ( name, color, text );
	GUI_Window_Draw ("hola");

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

