
/*==================[inclusions]=============================================*/

#include "timer.h"
/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

void Inicializar_RIT(void)
{
	Chip_RIT_Init(LPC_RITIMER);
//	NVIC_ClearPendingIRQ(RITIMER_IRQn);
//	NVIC_EnableIRQ(RITIMER_IRQn);
}


void Setear_RIT(uint32_t intervalo)
{
	Chip_RIT_SetTimerInterval(LPC_RITIMER, intervalo);
}


void Limpiar_RIT(void)
{
	Chip_RIT_ClearInt(LPC_RITIMER);
}

/*==================[end of file]============================================*/

