

/*==================[inclusions]=============================================*/
#include "main.h"
#include "led.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

/*Aplicación en la que se encienden y apagan todos los leds de la placa,
 * de modo secuencial.*/
int main(void)
{

#define DELAY 5000000
	edu_CIAA_ledRGB ledRGB;
	ledRGB.red = 0;
	ledRGB.green = 0;
	ledRGB.blue = 0;
	uint32_t i;

/*Configuro/inicializo los puertos para operar sobre los leds.*/
	InitGPIO_EDUCIAA_Leds();

/*Hago parpadear todos los leds*/
	while(1)
		{
			for(i = DELAY; i != 0; i--)
			{
				asm("nop");
			}
			ToggleLed(LED_AMARILLO);
			for(i = DELAY; i != 0; i--)
			{
				asm("nop");
			}
			ToggleLed(LED_ROJO);
			for(i = DELAY; i != 0; i--)
			{
				asm("nop");
			}
			ToggleLed(LED_VERDE);
			for(i = DELAY; i != 0; i--)
			{
				asm("nop");
			}
			ledRGB.blue = 0;
			ledRGB.red = 1;
			ToggleLedRGB(&ledRGB);
			for(i = DELAY; i != 0; i--)
			{
				asm("nop");
			}
			ledRGB.red = 0;
			ledRGB.green = 1;
			ToggleLedRGB(&ledRGB);
			for(i = DELAY; i != 0; i--)
			{
				asm("nop");
			}
			ledRGB.green = 0;
			ledRGB.blue = 1;
			ToggleLedRGB(&ledRGB);
		}
}
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

