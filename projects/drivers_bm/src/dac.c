
/*==================[inclusions]=============================================*/

#include "dac.h"
/*==================[macros and definitions]=================================*/


/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

void InicializarDAC ()
{
	Chip_SCU_DAC_Analog_Config();
	Chip_DAC_Init(LPC_DAC);
//	Chip_DAC_SetBias(LPC_DAC, DAC_MAX_UPDATE_RATE_400kHz);
//	Chip_DAC_SetDMATimeOut(LPC_DAC, 0xffff);
	Chip_DAC_ConfigDAConverterControl(LPC_DAC, DAC_CNT_ENA | DAC_DMA_ENA);
}

void ValorSalida (uint32_t valor)
{
	Chip_DAC_UpdateValue(LPC_DAC, valor);
}


/*==================[external functions definition]==========================*/

/*==================[end of file]============================================*/

