

/*==================[inclusions]=============================================*/
#include "main.h"
#include "led.h"
#include "teclas.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

edu_CIAA_teclado tec;
edu_CIAA_ledRGB rgb;
#define Delay 30000
uint32_t i;
/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

/*Aplicación en la que se encienden y apagan todos los leds de la placa,
 * de modo secuencial.*/

void ApagarLeds(edu_CIAA_ledRGB *rgb )
{
	LEDoff(LED_ROJO);
	LEDoff(LED_AMARILLO);
	LEDoff(LED_VERDE);

	rgb->blue = 0;
	rgb->green = 0;
	rgb->red = 0;
	RGBoff(rgb);
}

void ResetearTeclado(edu_CIAA_teclado *tec)
{
	tec->T1 = 1;
	tec->T2 = 1;
	tec->T3 = 1;
	tec->T4 = 1;
}

int main(void)
{
	InitGPIO_EDUCIAA_Teclas();
	InitGPIO_EDUCIAA_Leds();

	ResetearTeclado(&tec);
	ApagarLeds(&rgb);
	uint8_t Led_seleccionado = LED_AMARILLO;

	while(1)
	{
		if (Led_seleccionado != LED_RGB)
			LEDon(Led_seleccionado);
		else
		{
			rgb.blue = 1;
			rgb.green = 1;
			rgb.red = 1;
			RGBon(&rgb);
		}

		if (tec.T1 == 0)
		{
			if (Led_seleccionado == 0)
				Led_seleccionado = 3;
			else
				Led_seleccionado --;
			tec.T1 = 1;
		}
		if (tec.T4 == 0)
		{
			if (Led_seleccionado == 3)
				Led_seleccionado = 0;
			else
				Led_seleccionado ++;
			tec.T4 = 1;
		}

		for(i = Delay; i != 0; i--)
		{
			Escaneo_Teclado(&tec);
		}
		ApagarLeds(&rgb);
		for(i = Delay; i != 0; i--)
		{
			Escaneo_Teclado(&tec);
		}
	}
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

