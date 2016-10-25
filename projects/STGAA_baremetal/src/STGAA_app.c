

/*==================[inclusions]=============================================*/
#include "main.h"
#include "string.h"
#include "led.h"
#include "teclas.h"
#include "ccan.h"

/*==================[macros and definitions]=================================*/
#define AskForData_Interval 5000

typedef enum{
	RESTING = 1,
	REQUESTING_DATA,
	PROCESSING_DATA,
	REFRESHING_GUI
} STATE;

/*==================[internal data declaration]==============================*/

/*==================[en archivo display.c]=========================*/
void DSP_Init (void)
{
	GUI_StartLibrary();
	GUI_Window_ListInit();

	GUI_Window_Create ( "Start", BLACK, "STGAA-CIAA-NXP" );
	/*Dibujar esta ventana completa */

	GUI_Window_Create ( "Main", BLACK, "STGAA-CIAA-NXP" );
	/*Dibujar esta ventana completa*/

	GUI_Window_Draw ("Start");
}

void DSP_MainMode (void)
{
	GUI_Window_Draw ("Main");
}

void DSP_RefreshDisplay(losdatosdelossensores)
{
	/*Armar para que actualice los valores*/
	// 1-Pasar los datos a char
	GUI_Window_ChangeText(); // 2- Inventar esto!
}

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/
edu_CIAA_teclado tec;
CCAN_MSG_OBJ_T msg_buf;
STATE current_state;
/*==================[internal functions definition]==========================*/
void STGAA_Init(void)
{
	InitGPIO_EDUCIAA_Teclas();
	tec.T1 = 1;
	tec.T2 = 1;
	tec.T3 = 1;
	tec.T4 = 1;

	CCAN0_PORT_Init();

	RIT_Init();
	RIT_SetInterval(AskForData_Interval);

//	GUI_StartLibrary(); EN DISPLAY
	DSP_Init();

}

void CAN0_IRQHandler(void)
{
	if (entró acá por un mensaje posta)
	{	event_llegóCAN = true;
		despertameElMicro();
	}
	CCAN0_Clear();
}

void RIT_IRQHandler(void)
{
	event_5sec = true;
	despertameElMicro();
	RIT_Clear();
}
/*==================[external functions definition]==========================*/

int main(void)
{
	STGAA_Init();

	while (1){
		EscaneoTeclado(&tec);
		if (tec.T1 == 0)
			break;
	}
	current_state = RESTING;

	for (;;)
	{
		switch (current_state)
		{
		case RESTING:
				if (event_5sec) {current_state = REQUESTING_DATA; break;}
				if (event_rcv_msg) {current_state = PROCESSING_DATA; break;}
				Sleep();
				break;

		case REQUESTING_DATA:
				/*Armar mensaje para pedir info a los sensores*/
				CCAN0_Send_Message (elmensaje);
				event_5sec = false; //bajar las banderas que me trajeron
				current_state = RESTING;
				break;

		case PROCESSING_DATA:
				/*Armar para leer el mensaje del CCAN, cargarlo en memoria
				 * y después aumentar un contador que cuando cargo todos
				 * los sensores, me lleva a refresh.
				 * OJO!!!! Que primero tengo que chequear si el mensaje es posta
				 * toddo eso a drivers.*/
				CCAN0_Read_Message (unespaciodememoriatamañomensaje)
				mensajes_recibidos++;
				if(mensajes_recibidos == CANT_DE_SENS) //Armar en define
				{
					current_state = REFRESHING_GUI;
					mensajes_recibidos = 0;
				}
				else
					current_state = RESTING;
				event_llegoporCAN = false;
				break;

		case REFRESHING_GUI:
				DSP_Redibujamela4(lainfodelossensores);
				current_state = RESTING;
				break;
		}
	}
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
