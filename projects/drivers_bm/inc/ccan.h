
#ifndef CCAN_H
#define CCAN_H

/*==================[inclusions]=============================================*/
#include "chip.h"
#include "stdint.h"
#include "string.h"
/*==================[macros]=================================================*/
#define lpc4337            1
#define mk60fx512vlq15     2

#define CCAN_TX_MSG_ID (0x200)
#define CCAN_RX_MSG_ID (0x100)
#define CCAN_TX_MSG_REMOTE_ID (0x300)
#define DATA_LENGTH 8

#define true 1
#define false 0

#define CAN_BIT_RATE 125000
/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/


/*==================[external functions declaration]=========================*/
void CCAN0_PORT_Init();

void CCAN0_IDsToReceive (void);

void CCAN0_Clear(void);

void CCAN0_SendMessage (uint32_t _id, uint32_t _dlc, uint8_t _data[8]);

void CCAN0_GetID (uint32_t* _id);

void CCAN0_GetData (uint8_t (*_data)[8]);

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef CCAN_H */

