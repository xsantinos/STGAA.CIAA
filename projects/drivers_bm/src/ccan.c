
/*==================[inclusions]=============================================*/
#include "chip.h"
#include "ccan.h"
#include "led.h"
/*==================[macros and definitions]=================================*/
#define C_CAN0_IRQn 51
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

	Chip_SCU_PinMuxSet(0x3, 1, (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_FUNC2)); /* CAN RD */
	Chip_SCU_PinMuxSet(0x3, 2, (SCU_MODE_INACT | SCU_MODE_FUNC2)); /* CAN TD */
	NVIC_EnableIRQ(C_CAN0_IRQn);
	NVIC_ClearPendingIRQ(C_CAN0_IRQn);
}



/*==================[end of file]============================================*/

