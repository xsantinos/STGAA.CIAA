

/*==================[inclusions]=============================================*/
#include "main.h"
#include "string.h"
#include "led.h"
#include "teclas.h"
#include "Sensor2.h"
#include "timer.h"
#include "Display.h"

/*==================[macros and definitions]=================================*/
#define AskForData_Interval 5000
#define C_CAN0_IRQn 51

typedef enum{
	RESTING = 1,
	REQUESTING_DATA,
	PROCESSING_DATA,
	REFRESHING_GUI
} STATE;

/*==================[internal data declaration]==============================*/
bool event_CANReceived;
bool event_ConfigReceived;
bool event_DataReceived;
bool event_5sec;
uint8_t RcvMsgCount = 0;

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/
edu_CIAA_teclado tec;
CCAN_MSG_OBJ_T msg_buf;
STATE current_state;
ENV_ENVIRONMENTAL_T pEnv;
uint8_t aux;
/*==================[internal functions definition]==========================*/
void STGAA_Init(void)
{
	event_CANReceived = false;
	event_ConfigReceived = false;
	event_DataReceived = false;
	event_5sec = false;

	InitGPIO_EDUCIAA_Leds();
	InitGPIO_EDUCIAA_Teclas();
	tec.T1 = 1;
	tec.T2 = 1;
	tec.T3 = 1;
	tec.T4 = 1;

	SNS_Init();

	DSP_Init();
	SNS_SendConfig();
}

void CAN0_IRQHandler(void)
{
	uint32_t can_int = Chip_CCAN_GetIntID(LPC_C_CAN0);
	aux = can_int;
	while (can_int != 0) // Mientras sea != 0, significa que hay algún tipo de interrupción
	{

		if (can_int & CCAN_INT_STATUS)
		{
			Chip_CCAN_ClearStatus(LPC_C_CAN0, CCAN_STAT_TXOK);
			Chip_CCAN_ClearStatus(LPC_C_CAN0, CCAN_STAT_RXOK);
		}

		if ((1 <= CCAN_INT_MSG_NUM(can_int)) && (CCAN_INT_MSG_NUM(can_int) <= 0x20))
		{
			Chip_CCAN_GetMsgObject(LPC_C_CAN0, CCAN_MSG_IF1, can_int, &msg_buf);
			if (msg_buf.id)
			{
				event_CANReceived = true;
			}
		}
		can_int = Chip_CCAN_GetIntID(LPC_C_CAN0);
	}
	CCAN0_Clear();
}

void RIT_IRQHandler(void)
{
	RIT_Clear();
	event_5sec = true;
	ToggleLed(LED_VERDE);
}
/*==================[external functions definition]==========================*/

int main(void)
{
	STGAA_Init();

	while (1){
		Escaneo_Teclado(&tec);
		if (tec.T1 == 0)
			break;
	}
	current_state = RESTING;
	DSP_MainMode();
	SNS_AskForConfig();
	RIT_Init();
	RIT_SetInterval(AskForData_Interval);

	for (;;)
	{
		switch (current_state)
		{
		case RESTING:
				if (event_5sec) {current_state = REQUESTING_DATA; break;}
				if (event_CANReceived) {current_state = PROCESSING_DATA; break;}
				break;

		case REQUESTING_DATA:

				event_5sec = false;

				SNS_AskForData();
				current_state = RESTING;
				break;

		case PROCESSING_DATA:

				event_CANReceived = false;

				if(SNS_ConfigReceived(msg_buf.id))
				{
					event_ConfigReceived = false;
					SNS_LoadConfig(&msg_buf);
					current_state = RESTING;
				}
				else if (SNS_DataReceived(msg_buf.id))
				{
					event_DataReceived = false;
					if(SNS_LoadData(&msg_buf))
					{
						RcvMsgCount++;
					}
					if (RcvMsgCount == MAX_NUM_SNS)
					{	current_state = REFRESHING_GUI;
						RcvMsgCount = 0;	}
					else
						current_state = RESTING;
				}
				else
					current_state = RESTING;
				msg_buf.id = 0;
				break;

		case REFRESHING_GUI:

				SNS_GetEnvironmental(&pEnv);
				DSP_RefreshDisplay(&pEnv);
				current_state = RESTING;
				break;
		}
	}
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
