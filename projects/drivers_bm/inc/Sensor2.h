/*
 * Sensor.h
 *
 *  Created on: 21/1/2016
 *      Author: Prototipado
 */

#ifndef INC_SENSOR2_H_
#define INC_SENSOR2_H_

#include "lpc_types.h"
#include "ccan.h"
#include "Descriptors.h" /*Sensors data*/
#include "Environmental.h" /*Environmental data*/

/**
 * @brief Sensor message command definitions
 */
typedef enum {
	CMD_CONFIG =0,
	CMD_DATA,
	CMD_STATE
}COMAND;

/*
 * @Sensors IDs
 */
#define  GPS_DATA_RECEIVED		10
#define  GPS_CFG_RECEIVED		2

#define  ANEM_DATA_RECEIVED		11
#define  ANEM_CFG_RECEIVED		3

#define  THYG_DATA_RECEIVED		12
#define  THYG_CFG_RECEIVED		4

#define  FLOW_DATA_RECEIVED		13
#define  FLOW_CFG_RECEIVED		5

#define TOTAL_ID 				8

typedef enum {
	SEND_CFG=0,
	ASKFOR_DATA,
	ASKFOR_CFG,
}SNS_COMAND;

//Status SNS_read( SNS_MSG_T *  InMsg);
//Status SNS_write( SNS_MSG_T * OutMsg);

//void vSnsHandlerTask( void *pvParameters );

void SNS_Init(void);

void SNS_AskForData (void);
Status SNS_LoadData(CCAN_MSG_OBJ_T* RcvMsg);

void SNS_AskForConfig(void);
void SNS_LoadConfig(CCAN_MSG_OBJ_T* RcvMsg);

void SNS_SendConfig(void);

bool SNS_ConfigReceived(uint8_t _ID);
bool SNS_DataReceived(uint8_t _ID);

void SNS_GetEnvironmental (ENV_ENVIRONMENTAL_T* pEnv);

#endif /* INC_SENSOR2_H_ */
