
#ifndef TIMER_H
#define TIMER_H

/*==================[inclusions]=============================================*/

#include "chip.h"
#include "stdint.h"

/*==================[macros]=================================================*/
#define lpc4337            1
#define mk60fx512vlq15     2

#define RITIMER_IRQn 11
/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

void RIT_Init(void);

void RIT_SetInterval(uint32_t intervalo);

void RIT_Clear(void);

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef MI_NUEVO_PROYECTO_H */
