
/*==================[inclusions]=============================================*/

#include "timer.h"
/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

void RIT_Init(void)
{
	Chip_RIT_Init(LPC_RITIMER);

	NVIC_EnableIRQ(RITIMER_IRQn);
	NVIC_ClearPendingIRQ(RITIMER_IRQn);
}


void RIT_SetInterval(uint32_t intervalo)
{
	Chip_RIT_SetTimerInterval(LPC_RITIMER, intervalo);
}


void RIT_Clear(void)
{
	Chip_RIT_ClearInt(LPC_RITIMER);
}

/*==================[end of file]============================================*/

