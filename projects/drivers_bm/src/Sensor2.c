/** @file Sensor.c
 *  @brief (agregar comentario).
 *
 *  Sensor is responsible for\n
 *  -.\n
 *  -.
 * @version		1.0
 * @date		20/01/2016
 * @author		Bioing. Martina Mauro
 * @note
 *  STGAA V3.0.0\n
 *  Facultad de Ingenieria - UNER.\n
 *  Laboratorio de prototipado Electronico &3D.\n
 *  All rights reserved. Copyright (C) 2016	.
 */


#include "Sensor2.h"

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

CCAN_MSG_OBJ_T RcvMsg;
char ReceivedDataCount = 0;
uint8_t IDList[TOTAL_ID];

ENV_ENVIRONMENTAL_T _Environmental;
/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/**
 * @brief 		ACQ_Acquiring thread
 * @param[in] 	CANx point to LPC_CAN_TypeDef object, should be:
 * 				- LPC_CAN1: CAN1 peripheral
 * 				- LPC_CAN2: CAN2 peripheral
 * @param[in]	baudrate: is the baud rate value will be set
 * @see publicVar()
 * @return 		None
 */
STATIC Status SNS_DataUnwrap(CCAN_MSG_OBJ_T* pReceivedMsg){

/*CAN id_standard has 11 bits, should be read according to the format xxxxxxxxzzz.
 * xxxx: Command; zzz:identifier; */
	ENV_GetEnvironmental(&_Environmental);
	switch(pReceivedMsg->id & 0x007)
	{
	case ID_GPS:
				_Environmental.gps.lat_deegres=pReceivedMsg->data[0];
				_Environmental.gps.lat_minutes=pReceivedMsg->data[1];
				_Environmental.gps.lat_seconds=((pReceivedMsg->data[2])*256 +(pReceivedMsg->data[3]))*0.006;
				_Environmental.gps.long_deegres=pReceivedMsg->data[4];
				_Environmental.gps.long_minutes=pReceivedMsg->data[5];
				_Environmental.gps.long_seconds=((pReceivedMsg->data[6])*256 +(pReceivedMsg->data[7]))*0.006;
				ENV_SetEnvironmental(&_Environmental);
				break;

	case ID_ANEMOMETER:
				_Environmental.wind.speed=((pReceivedMsg->data[0])*256 +(pReceivedMsg->data[1]))*0.01;
				_Environmental.wind.direction=((pReceivedMsg->data[2])*256 +(pReceivedMsg->data[3]));
				ENV_SetEnvironmental(&_Environmental);
				break;

	case ID_THERMOHYGROMETER:
				_Environmental.tyh.temperature=((pReceivedMsg->data[0])*256 +(pReceivedMsg->data[1]))*0.01;
				_Environmental.tyh.humidity=((pReceivedMsg->data[2])*256 +(pReceivedMsg->data[3]))*0.01;
				ENV_SetEnvironmental(&_Environmental);
				break;

	case ID_FLOWMETER:
				_Environmental.flow.value=((pReceivedMsg->data[0])*256 +(pReceivedMsg->data[1]));
				_Environmental.flow.on_off=pReceivedMsg->data[2];
				ENV_SetEnvironmental(&_Environmental);
				break;

	default:
				return ERROR;
	}

return SUCCESS;
}

STATIC Status SNS_DescriptorUnwrap(CCAN_MSG_OBJ_T* pReceivedMsg, DSC_DESCRIPTOR_T* pDescriptor)
{
//	pDescriptor->id=(pReceivedMsg->id<<4);
	pDescriptor->id=(pReceivedMsg->id&0x007);
	pDescriptor->config.FREQ=pReceivedMsg->data[0];
	pDescriptor->config.MODE=pReceivedMsg->data[1];
	pDescriptor->config.RESOL=pReceivedMsg->data[2];
    pDescriptor->state=pReceivedMsg->data[3];

    return SUCCESS;
}



/*****************************************************************************
 * Public functions
 ****************************************************************************/
void SNS_Init(void)
{
	CCAN0_PORT_Init();

	IDList[0] = Chip_CCAN_AddReceiveID2(LPC_C_CAN0, CCAN_MSG_IF1, GPS_DATA_RECEIVED);
	IDList[1] = Chip_CCAN_AddReceiveID2(LPC_C_CAN0, CCAN_MSG_IF1, GPS_CFG_RECEIVED);
	IDList[2] = Chip_CCAN_AddReceiveID2(LPC_C_CAN0, CCAN_MSG_IF1, ANEM_DATA_RECEIVED);
	IDList[3] = Chip_CCAN_AddReceiveID2(LPC_C_CAN0, CCAN_MSG_IF1, ANEM_CFG_RECEIVED);
	IDList[4] = Chip_CCAN_AddReceiveID2(LPC_C_CAN0, CCAN_MSG_IF1, THYG_DATA_RECEIVED);
	IDList[5] = Chip_CCAN_AddReceiveID2(LPC_C_CAN0, CCAN_MSG_IF1, THYG_CFG_RECEIVED);
	IDList[6] = Chip_CCAN_AddReceiveID2(LPC_C_CAN0, CCAN_MSG_IF1, FLOW_DATA_RECEIVED);
	IDList[7] = Chip_CCAN_AddReceiveID2(LPC_C_CAN0, CCAN_MSG_IF1, FLOW_CFG_RECEIVED);

	_Environmental.flow.on_off = 0;
	_Environmental.flow.value = 0;
	_Environmental.gps.lat_deegres = 0;
	_Environmental.gps.lat_minutes = 0;
	_Environmental.gps.lat_seconds = 0;
	_Environmental.gps.long_deegres = 0;
	_Environmental.gps.long_minutes = 0;
	_Environmental.gps.long_seconds = 0;
	_Environmental.tyh.humidity = 0;
	_Environmental.tyh.temperature = 0;
	_Environmental.wind.direction = 0;
	_Environmental.wind.speed = 0;
	ENV_SetEnvironmental(&_Environmental);
}

void SNS_AskForConfig(void)
{
	uint32_t id;
	uint32_t dlc = DATA_LENGTH;
	uint8_t data[8];

	id = ID_CPU;
	data[0] = ASKFOR_CFG;

	CCAN0_SendMessage (id, dlc, data);
}

void SNS_AskForData(void)
{
	uint32_t id;
	uint32_t dlc = DATA_LENGTH;
	uint8_t data[8];

	id = ID_CPU;
	data[0] = ASKFOR_DATA;

	CCAN0_SendMessage (id, dlc, data);
}

void SNS_SendConfig(void)
{
	uint32_t id;
	uint32_t dlc = DATA_LENGTH;
	uint8_t data[8];

	id = ID_CPU;
	data[0] = SEND_CFG;
	data[1] = FREQ_0;
	data[2] = MODE_ONDEMAND;
	data[3] = RESOL_0;
	data[4] = ENABLE;

	CCAN0_SendMessage (id, dlc, data);
}


void SNS_LoadConfig(CCAN_MSG_OBJ_T* RcvMsg)
{
	DSC_DESCRIPTOR_T myDescriptor;

	SNS_DescriptorUnwrap(RcvMsg, &myDescriptor);
	DSC_AddSensorToList(&myDescriptor);
}

Status SNS_LoadData(CCAN_MSG_OBJ_T* RcvMsg)
{

	if (SNS_DataUnwrap(RcvMsg))
		return SUCCESS;
	else
		return ERROR;
}

bool SNS_ConfigReceived(uint8_t _ID)
{
	_ID >>= 3; //Desplazo 3 bits a la derecha, descartando los que corresponden
			  //al id de quién lo envió al mensaje. Acá sólo me interesa saber
	          //si lo que se recibieron fueron datos o config.
	bool B;
	if ( _ID == CMD_CONFIG )
		B = true;
	else
		B = false;
	return B;
}

bool SNS_DataReceived(uint8_t _ID)
{
	_ID >>= 3; //Desplazo 3 bits a la derecha, descartando los que corresponden
			  //al id de quién lo envió al mensaje. Acá sólo me interesa saber
	          //si lo que se recibieron fueron datos o config.
	bool B;
	if ( _ID == CMD_DATA )
		B = true;
	else
		B = false;
	return B;
}

void SNS_GetEnvironmental (ENV_ENVIRONMENTAL_T* pEnv)
{
	ENV_GetEnvironmental(pEnv);
}
