

/*==================[inclusions]=============================================*/
#include "main.h"
#include "led.h"
#include "Microinterface.h"
#include "teclas.h"

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

	edu_CIAA_teclado TEC;
	TEC.T1 = 0;
	TEC.T2 = 0;
	TEC.T3 = 0;
	TEC.T4 = 0;

/*Configuro/inicializo los puertos para operar sobre los leds.*/
	InitGPIO_EDUCIAA_Leds();
	MicroInterface_Init();
	InitGPIO_EDUCIAA_Teclas();

/*Hago parpadear todos los leds*/
	while(1)
		{
		Escaneo_Teclado(&TEC);
		if (TEC.T1 == 0){
			MicroInterface_Bit_WriteHigh(3,0);
			LEDon(LED_ROJO);
		}
		if (TEC.T2 == 0){
			MicroInterface_Bit_WriteLow(3,0);
			LEDoff(LED_ROJO);
		}

		}
}
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

