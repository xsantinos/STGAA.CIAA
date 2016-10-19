

/*==================[inclusions]=============================================*/
#include "main.h"
#include "string.h"
#include "led.h"
#include "teclas.h"
#include "ccan.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/
uint8_t msg_received_counter = 0;
/*==================[external data definition]===============================*/
edu_CIAA_teclado tec;
edu_CIAA_ledRGB rgb;

uint32_t i;
#define DELAY 5000000
#define C_CAN0_IRQn 51
/*==================[internal functions definition]==========================*/
void CAN0_IRQHandler(void)
{
	ToggleLed(LED_VERDE);
	ToggleLed(LED_AMARILLO);
	ToggleLed(LED_ROJO);

	CCAN_MSG_OBJ_T msg_buf;
	uint32_t can_int, can_stat, i;
	while ( (can_int = Chip_CCAN_GetIntID(LPC_C_CAN0)) != 0 )
	{
		if (can_int & CCAN_INT_STATUS)
		{
/*			can_stat = Chip_CCAN_GetStatus(LPC_C_CAN0);
			// TODO with error or TXOK, RXOK
			if (can_stat & CCAN_STAT_EPASS) {
//				DEBUGOUT("Passive error\r\n");
				return;
			}
			if (can_stat & CCAN_STAT_EWARN) {
//				DEBUGOUT("Warning!!!\r\n");
				return;
			}
			if (can_stat & CCAN_STAT_BOFF) {
//				DEBUGOUT("CAN bus is off\r\n");
				return;
			}*/
			Chip_CCAN_ClearStatus(LPC_C_CAN0, CCAN_STAT_TXOK);
			Chip_CCAN_ClearStatus(LPC_C_CAN0, CCAN_STAT_RXOK);
		}
		else if ((1 <= CCAN_INT_MSG_NUM(can_int)) && (CCAN_INT_MSG_NUM(can_int) <= 0x20))
		{
			// Process msg num canint
			Chip_CCAN_GetMsgObject(LPC_C_CAN0, CCAN_MSG_IF1, can_int, &msg_buf);
			switch (msg_buf.id) {
			case CCAN_RX_MSG_ID:
				msg_buf.id += 1;
				Chip_CCAN_Send(LPC_C_CAN0, CCAN_MSG_IF1, false, &msg_buf);
				break;

			case CCAN_TX_MSG_ID:
				break;
			case CCAN_TX_MSG_REMOTE_ID:
//				msg_received_counter++;
				if (msg_received_counter == 5)
				{
//					LEDon(LED_VERDE);
//					DEBUGOUT("Remote transmit total is 5. Delete remote ID\r\n");
					Chip_CCAN_DeleteReceiveID(LPC_C_CAN0, CCAN_MSG_IF1, CCAN_TX_MSG_REMOTE_ID);
				}
				break;

			default:
				break;
			}
		}
	}
	NVIC_ClearPendingIRQ(C_CAN0_IRQn);
}
//void ToggleporTeclas (void)
//{
//	Escaneo_Teclado(&tec);
//	if (tec.T1 == 0)
//	{
//		rgb.blue=1;
//		rgb.green=1;
//		rgb.red=1;
//		ToggleLedRGB(&rgb);
//	}
//
//	else
//	{
//		rgb.blue=0;
//		rgb.green=0;
//		rgb.red=0;
//		RGBoff(&rgb);
//	}
//	if (tec.T2 == 0)
//		ToggleLed(LED_ROJO);
//	else
//		LEDoff(LED_ROJO);
//	if (tec.T3 == 0)
//		ToggleLed(LED_AMARILLO);
//	else
//		LEDoff(LED_AMARILLO);
//	if (tec.T4 == 0)
//		ToggleLed(LED_VERDE);
//	else
//		LEDoff(LED_VERDE);
//
//	uint32_t i;
//	for(i = DELAY; i != 0; i--)
//	{
//		asm("nop");
//	}
//}
/*==================[external functions definition]==========================*/

//int main(void)
//{
//	InitGPIO_EDUCIAA_Teclas();
//	InitGPIO_EDUCIAA_Leds();
//	CCAN_PORT_Init();
//
//	tec.T1 = 1;
//	tec.T2 = 1;
//	tec.T3 = 1;
//	tec.T4 = 1;
//	rgb.blue = 1;
//	rgb.green = 1;
//	rgb.red = 1;
//
//	while(1)
//	{
//		ToggleporTeclas();
//	}
//}
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
int main(void)
{
	InitGPIO_EDUCIAA_Teclas();
	InitGPIO_EDUCIAA_Leds();
	CCAN_PORT_Init();


	CCAN_MSG_OBJ_T send_obj;
//	Board_Init();
//	DEBUGOUT(WelcomeMenu);
	/* Set CCAN peripheral clock under 100Mhz for working stable */


	send_obj.id = CCAN_TX_MSG_ID;
	send_obj.dlc = 4;
	send_obj.data[0] = 'A';
	send_obj.data[1] = 'B';
	send_obj.data[2] = 'C';
	send_obj.data[3] = 'D';
	Chip_CCAN_Send(LPC_C_CAN0, CCAN_MSG_IF1, false, &send_obj);
	Chip_CCAN_ClearStatus(LPC_C_CAN0, CCAN_STAT_TXOK);

//	send_obj.id = CCAN_TX_MSG_REMOTE_ID;
	send_obj.data[0] = 'E';
	send_obj.data[1] = 'F';
	send_obj.data[2] = 'G';
	send_obj.data[3] = 'H';
	Chip_CCAN_Send(LPC_C_CAN0, CCAN_MSG_IF1, false, &send_obj);
	Chip_CCAN_ClearStatus(LPC_C_CAN0, CCAN_STAT_TXOK);


//	Chip_CCAN_AddReceiveID(LPC_C_CAN0, CCAN_MSG_IF1, CCAN_RX_MSG_ID);

//	NVIC_EnableIRQ(C_CAN0_IRQn);

	while (1)
	{
		Escaneo_Teclado(&tec);
		if (tec.T1 == 0)
		{
			Chip_CCAN_Send(LPC_C_CAN0, CCAN_MSG_IF1, false, &send_obj);
			rgb.blue=1;
			rgb.green=1;
			rgb.red=1;
			ToggleLedRGB(&rgb);
			Chip_CCAN_Send(LPC_C_CAN0, CCAN_MSG_IF1, true, &send_obj);
			Chip_CCAN_AddReceiveID(LPC_C_CAN0, CCAN_MSG_IF1, CCAN_RX_MSG_ID);
		}

		else
		{
			rgb.blue=0;
			rgb.green=0;
			rgb.red=0;
			RGBoff(&rgb);
		}
		for(i = DELAY; i != 0; i--)
		{
			asm("nop");
		}
	}
}
