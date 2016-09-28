

/*==================[inclusions]=============================================*/
#include "main.h"
#include "dac.h"
#include "teclas.h"
#include "timer.h"
#include "led.h"
/*==================[macros and definitions]=================================*/
#define base_de_tiempo 1
/*==================[internal data declaration]==============================*/
uint32_t valor = 0;

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

/*Aplicación en la que se hacen parpadear todos los leds de la placa.*/

void LlamadoRIT (void)
{
	Limpiar_RIT();
	if (valor >= 1023)
		valor = 0;
	else
		valor++;
	ValorSalida(valor);
}

int main(void)
{
	InitGPIO_EDUCIAA_Leds();
	InicializarDAC();
	Inicializar_RIT();
	Setear_RIT(base_de_tiempo);
	while(1)
	{
		asm("nop");
	}
}
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

