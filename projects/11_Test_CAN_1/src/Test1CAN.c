

/*==================[inclusions]=============================================*/
#include "main.h"
#include "string.h"
#include "led.h"
#include "teclas.h"
#include "ccan.h"
#include "Sensor2.h"
#include "Display.h"
//#include "stdio.h"
/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/
uint8_t msg_received_counter = 0;
/*==================[external data definition]===============================*/
edu_CIAA_teclado tec;
edu_CIAA_ledRGB rgb;
CCAN_MSG_OBJ_T dummy;
ENV_ENVIRONMENTAL_T* _pEnv;

uint8_t IDReceived;
bool event_CANReceived;
bool event_ConfigReceived;
bool event_DataReceived;

#define DELAY 10
#define C_CAN0_IRQn 51
/*==================[internal functions definition]==========================*/
//void CAN0_IRQHandler(void)
//{
//
////	CCAN_MSG_OBJ_T msg_buf;
//	uint32_t can_int = Chip_CCAN_GetIntID(LPC_C_CAN0);
//
//
//	while (can_int != 0) // Mientras sea != 0, significa que hay algún tipo de interrupción
//	{
//		if (can_int & CCAN_INT_STATUS) // Status interrupt llamó acá
//		{
//			Chip_CCAN_ClearStatus(LPC_C_CAN0, CCAN_STAT_TXOK);
//			Chip_CCAN_ClearStatus(LPC_C_CAN0, CCAN_STAT_RXOK);
//		}
//		if ((1 <= CCAN_INT_MSG_NUM(can_int)) && (CCAN_INT_MSG_NUM(can_int) <= 0x20)) // 1 a 32, número de
//												// Msg Obj que causó la interrupción
//		{
//			Chip_CCAN_GetMsgObject(LPC_C_CAN0, CCAN_MSG_IF1, can_int, &dummy);
//
////			switch (dummy.id)
////			{
////			case GPS_DATA_RECEIVED:
////				ToggleLed(LED_VERDE);
////				break;
////
////			case GPS_CFG_RECEIVED:
////				ToggleLed(LED_ROJO);
////				break;
////
////			case ANEM_DATA_RECEIVED:
////				ToggleLed(LED_AMARILLO);
////				break;
////
////			case ANEM_CFG_RECEIVED:
////				ToggleLed(LED_AMARILLO);
////				break;
////
////			case THYG_DATA_RECEIVED:
////				ToggleLed(LED_AMARILLO);
////				break;
////
////			case THYG_CFG_RECEIVED:
////				ToggleLed(LED_AMARILLO);
////				break;
////
////			case FLOW_CFG_RECEIVED:
////				ToggleLed(LED_AMARILLO);
////				break;
////
////			case FLOW_DATA_RECEIVED:
////				ToggleLed(LED_AMARILLO);
////				break;
////			default:
////				break;
////			}
//		}
//		can_int = Chip_CCAN_GetIntID(LPC_C_CAN0);
//	}
//	NVIC_ClearPendingIRQ(C_CAN0_IRQn);
//}
/*==================[external functions definition]==========================*/
void CAN0_IRQHandler(void)
{
	uint32_t can_int = Chip_CCAN_GetIntID(LPC_C_CAN0);

	while (can_int != 0) // Mientras sea != 0, significa que hay algún tipo de interrupción
	{
		if (can_int & CCAN_INT_STATUS)
		{
			Chip_CCAN_ClearStatus(LPC_C_CAN0, CCAN_STAT_TXOK);
			Chip_CCAN_ClearStatus(LPC_C_CAN0, CCAN_STAT_RXOK);
		}
		if ((1 <= CCAN_INT_MSG_NUM(can_int)) && (CCAN_INT_MSG_NUM(can_int) <= 0x20))
		{
			Chip_CCAN_GetMsgObject(LPC_C_CAN0, CCAN_MSG_IF1, can_int, &dummy);
			if (dummy.id){
				event_CANReceived = true;
				IDReceived = dummy.id;}
		}
		can_int = Chip_CCAN_GetIntID(LPC_C_CAN0);
	}
	CCAN0_Clear();
}
int main(void)
{
	InitGPIO_EDUCIAA_Teclas();
	InitGPIO_EDUCIAA_Leds();
	SNS_Init();
	DSP_Init();
	event_CANReceived = false;

	CCAN_MSG_OBJ_T send_obj;

	send_obj.id = CCAN_TX_MSG_ID;
	send_obj.dlc = 4;
	send_obj.data[0] = 'A';
	send_obj.data[1] = 'B';
	send_obj.data[2] = 'C';
	send_obj.data[3] = 'D';
	Chip_CCAN_Send(LPC_C_CAN0, CCAN_MSG_IF1, false, &send_obj);
	Chip_CCAN_ClearStatus(LPC_C_CAN0, CCAN_STAT_TXOK);

	send_obj.data[0] = 'E';
	send_obj.data[1] = 'F';
	send_obj.data[2] = 'G';
	send_obj.data[3] = 'H';
	Chip_CCAN_Send(LPC_C_CAN0, CCAN_MSG_IF1, false, &send_obj);
	Chip_CCAN_ClearStatus(LPC_C_CAN0, CCAN_STAT_TXOK);

	send_obj.id = CCAN_RX_MSG_ID;
	send_obj.dlc = 4;
	send_obj.data[0] = 'I';
	send_obj.data[1] = 'J';
	send_obj.data[2] = 'K';
	send_obj.data[3] = 'L';

	SNS_AskForConfig();



	while (1)
	{
//		Escaneo_Teclado(&tec);
//		if (tec.T1 == 0)
//		{
//			Chip_CCAN_Send(LPC_C_CAN0, CCAN_MSG_IF1, false, &send_obj);
//			rgb.blue=1;
//			rgb.green=1;
////			rgb.red=1;
////			ToggleLedRGB(&rgb);
//		}
//
//		else
//		{
//			rgb.blue=0;
//			rgb.green=0;
//			rgb.red=0;
//			RGBoff(&rgb);
//		}
//		uint32_t i;
//		i = dummy.id;
//		rgb.blue = 0;
//		Chip_CCAN_GetMsgObject(LPC_C_CAN0, CCAN_MSG_IF1, pos100, &dummy);
		if (event_CANReceived)
		{
			event_CANReceived = false;
			if (SNS_DataReceived(IDReceived))
			{
				ToggleLed(LED_VERDE);
				event_DataReceived = true;
				DSP_MainMode();
			}
			else if (SNS_ConfigReceived(IDReceived))
			{
				ToggleLed(LED_ROJO);
				event_ConfigReceived = true;
				SNS_LoadConfig(&dummy);
//				GUI_Window_EditText ("Main\n","_temp", "HOLAHOLA");
				DSP_RefreshDisplay(_pEnv);
			}
		}
	}
}

/*==================[end of file]============================================*/
