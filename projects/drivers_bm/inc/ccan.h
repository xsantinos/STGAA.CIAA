
#ifndef CCAN_H
#define CCAN_H

/*==================[inclusions]=============================================*/


#include "chip.h"
#include "stdint.h"
/*==================[macros]=================================================*/
#define lpc4337            1
#define mk60fx512vlq15     2

#define CCAN_TX_MSG_ID (0x200)
#define CCAN_RX_MSG_ID (0x100)
#define CCAN_TX_MSG_REMOTE_ID (0x300)

#define true 1
#define false 0

#define CAN_BIT_RATE 125000
/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/


/*==================[external functions declaration]=========================*/

void CCAN0_PORT_Init();

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef CCAN_H */

