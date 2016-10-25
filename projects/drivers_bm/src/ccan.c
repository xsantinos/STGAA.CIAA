
/*==================[inclusions]=============================================*/
#include "chip.h"
#include "ccan.h"
#include "led.h"
/*==================[macros and definitions]=================================*/
#define C_CAN0_IRQn 51

#define CCAN0_PACK_NUMBER 3

#define CCAN0_RD_PIN_NUMBER 1
#define CCAN0_TD_PIN_NUMBER 2
/*==================[internal data declaration]==============================*/

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
	Chip_CCAN_EnableInt(LPC_C_CAN0, (CCAN_CTRL_IE | CCAN_CTRL_SIE | CCAN_CTRL_EIE));

	Chip_SCU_PinMuxSet(CCAN0_PACK_NUMBER, CCAN0_RD_PIN_NUMBER, (SCU_MODE_INACT |
			           SCU_MODE_INBUFF_EN | SCU_MODE_FUNC2)); /* CAN RD */
	Chip_SCU_PinMuxSet(CCAN0_PACK_NUMBER, CCAN0_TD_PIN_NUMBER, (SCU_MODE_INACT | SCU_MODE_FUNC2)); /* CAN TD */

	NVIC_EnableIRQ(C_CAN0_IRQn);
	NVIC_ClearPendingIRQ(C_CAN0_IRQn);
}

void CCAN0_Clear(void)
{
	NVIC_ClearPendingIRQ(C_CAN0_IRQn);
}



/*==================[end of file]============================================*/

