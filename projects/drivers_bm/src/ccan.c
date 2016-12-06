
/*==================[inclusions]=============================================*/
#include "ccan.h"
/*==================[macros and definitions]=================================*/
#define C_CAN0_IRQn 51

#define CCAN0_PACK_NUMBER 3

#define CCAN0_RD_PIN_NUMBER 1
#define CCAN0_TD_PIN_NUMBER 2


/*IDs for handling received messages*/
#define CPU_ASKFOR_CONFIG 	2
#define CPU_ASKFOR_DATA		3

#define GPS_CFG				4
#define GPS_DATA			5

#define ANEM_CFG			6
#define ANEM_DATA			7

#define THYG_CFG			8
#define THYG_DATA			9

#define FLOW_CFG			10
#define FLOW_DATA			11

/*==================[internal data declaration]==============================*/
uint32_t MsgRAM[32];
/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
void CCAN0_PORT_Init(void)
{
	SystemCoreClockUpdate();
	Chip_Clock_SetBaseClock(CLK_BASE_APB3, CLKIN_IDIVC, true, false);
	Chip_CCAN_Init(LPC_C_CAN0);

	Chip_CCAN_SetBitRate(LPC_C_CAN0, CAN_BIT_RATE);

	/* Chip_CCAN_EnableInt enables CCAN interrupts
	 * CAN_CTRL_IE: Enable CAN interrupts. The interrupt line is set to LOW and
	 * remains LOW until all pending interrupts are cleared.
	 *
	 * CAN_CTRL_SIE: A status change interrupt will be generated when a message
	 * transfer is successfully completed or a CAN bus error is detected
	 *
	 * CCAN_CTRL_EIE: Enable error interrupt. A change in the bits BOFF or EWARN
	 * in the CANSTAT registers will generate an interrupt. */
	Chip_CCAN_EnableInt(LPC_C_CAN0, (CCAN_CTRL_IE | CCAN_CTRL_SIE | CCAN_CTRL_EIE));

	/* Pin muxing */

	Chip_SCU_PinMuxSet(CCAN0_PACK_NUMBER, CCAN0_TD_PIN_NUMBER, (SCU_MODE_INACT | SCU_MODE_FUNC2)); /* CAN TD */
	Chip_SCU_PinMuxSet(CCAN0_PACK_NUMBER, CCAN0_RD_PIN_NUMBER, (SCU_MODE_INACT |
			           SCU_MODE_INBUFF_EN | SCU_MODE_FUNC2)); /* CAN RD */

	NVIC_EnableIRQ(C_CAN0_IRQn);
	NVIC_ClearPendingIRQ(C_CAN0_IRQn);

	CCAN0_IDsToReceive();
}

void CCAN0_IDsToReceive(void)
{
	uint8_t NofMsg[8];
	NofMsg[0] = Chip_CCAN_AddReceiveID2(LPC_C_CAN0, CCAN_MSG_IF1, GPS_CFG);
	NofMsg[1] = Chip_CCAN_AddReceiveID2(LPC_C_CAN0, CCAN_MSG_IF1, GPS_DATA);

	NofMsg[2] = Chip_CCAN_AddReceiveID2(LPC_C_CAN0, CCAN_MSG_IF1, ANEM_CFG);
	NofMsg[3] = Chip_CCAN_AddReceiveID2(LPC_C_CAN0, CCAN_MSG_IF1, ANEM_DATA);

	NofMsg[4] = Chip_CCAN_AddReceiveID2(LPC_C_CAN0, CCAN_MSG_IF1, THYG_CFG);
	NofMsg[5] = Chip_CCAN_AddReceiveID2(LPC_C_CAN0, CCAN_MSG_IF1, THYG_DATA);

	NofMsg[6] = Chip_CCAN_AddReceiveID2(LPC_C_CAN0, CCAN_MSG_IF1, FLOW_CFG);
	NofMsg[7] = Chip_CCAN_AddReceiveID2(LPC_C_CAN0, CCAN_MSG_IF1, FLOW_DATA);

	MsgRAM[NofMsg[0]] = GPS_CFG;
	MsgRAM[NofMsg[1]] = GPS_DATA;
	MsgRAM[NofMsg[2]] = ANEM_CFG;
	MsgRAM[NofMsg[3]] = ANEM_DATA;
	MsgRAM[NofMsg[4]] = THYG_CFG;
	MsgRAM[NofMsg[5]] = THYG_DATA;
	MsgRAM[NofMsg[6]] = FLOW_CFG;
	MsgRAM[NofMsg[7]] = FLOW_DATA;
}

void CCAN0_Clear(void)
{
	NVIC_ClearPendingIRQ(C_CAN0_IRQn);
}

void CCAN0_SendMessage (uint32_t _id, uint32_t _dlc, uint8_t _data[8])
{
	CCAN_MSG_OBJ_T Message;
	Message.id = _id;
	Message.dlc = _dlc;
	memcpy (Message.data, _data, DATA_LENGTH);

	Chip_CCAN_Send(LPC_C_CAN0, CCAN_MSG_IF2, false, &Message);
	Chip_CCAN_ClearStatus(LPC_C_CAN0, CCAN_STAT_TXOK);
	Chip_CCAN_ClearStatus(LPC_C_CAN0, CCAN_STAT_RXOK);
}

void CCAN0_GetID (uint32_t* _id)
{
	CCAN_MSG_OBJ_T MsgObj;
	_id = &MsgObj.id;
}

void CCAN0_GetData (uint8_t (*_data)[8])
{
	CCAN_MSG_OBJ_T MsgObj;
	uint32_t can_int = Chip_CCAN_GetIntID(LPC_C_CAN0);
	Chip_CCAN_GetMsgObject(LPC_C_CAN0, CCAN_MSG_IF1, can_int, &MsgObj);
	memcpy (MsgObj.data, _data, DATA_LENGTH);
}






















/*==================[end of file]============================================*/

