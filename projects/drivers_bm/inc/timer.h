
#ifndef TIMER_H
#define TIMER_H

/*==================[inclusions]=============================================*/

#include "chip.h"
#include "stdint.h"

/*==================[macros]=================================================*/
#define lpc4337            1
#define mk60fx512vlq15     2

/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

void Inicializar_RIT(void);
void Setear_RIT(uint32_t intervalo);
void Limpiar_RIT(void);

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef MI_NUEVO_PROYECTO_H */
