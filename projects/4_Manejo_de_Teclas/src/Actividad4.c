

/*==================[inclusions]=============================================*/
#include "main.h"
#include "led.h"
#include "teclas.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

edu_CIAA_teclado tec;
edu_CIAA_ledRGB rgb;


/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

/*Aplicación en la que se encienden y apagan todos los leds de la placa,
 * de modo secuencial.*/
int main(void)
{
	tec.T1 = 1;
	tec.T2 = 1;
	tec.T3 = 1;
	tec.T4 = 1;
	rgb.blue = 1;
	rgb.green = 1;
	rgb.red = 1;
	uint32_t i;

	#define DELAY 5000000

	InitGPIO_EDUCIAA_Teclas();
	InitGPIO_EDUCIAA_Leds();

	while(1)
		{

			Escaneo_Teclado(&tec);
			if (tec.T1 == 0)
			{
				rgb.blue=1;
				rgb.green=1;
				rgb.red=1;
				ToggleLedRGB(&rgb);
			}

			else
			{
				rgb.blue=0;
				rgb.green=0;
				rgb.red=0;
				RGBoff(&rgb);
			}
			if (tec.T2 == 0)
				ToggleLed(LED_AMARILLO);
			else
				LEDoff(LED_AMARILLO);
			if (tec.T3 == 0)
				ToggleLed(LED_ROJO);
			else
				LEDoff(LED_ROJO);
			if (tec.T4 == 0)
				ToggleLed(LED_VERDE);
			else
				LEDoff(LED_VERDE);
			for(i = DELAY; i != 0; i--)
			{
				asm("nop");
			}
		}
}
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

