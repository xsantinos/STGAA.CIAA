/*
 * Sensor.h
 *
 *  Created on: 21/1/2016
 *      Author: Prototipado
 */
//
//#ifndef INC_SENSOR_H_
//#define INC_SENSOR_H_
//
//#include "lpc_types.h"
//
//
//
//#define CAN_TX_MSG_STD_ID (0x200)
//#define CAN_TX_MSG_REMOTE_STD_ID (0x300)
//#define CAN_TX_MSG_EXT_ID (0x10000200)
//#define CAN_RX_MSG_ID (0x100)
//
///**
// * @brief Sensor message command definitions
// */
//
////enum {
////	CMD_CONFIG=0,
////	CMD_DATA,
////	CMD_STATE
////};
//
///**
// * @brief Sensor message command definitions
// */
//typedef struct{
//char ID;
//char CMD;
//} SNS_ID_T;
//
///**
// * @brief Sensor message definitions
// */
//typedef struct {
//SNS_ID_T head;
//char data[8];
//}SNS_MSG_T;
//
//Status SNS_read( SNS_MSG_T *  InMsg);
//Status SNS_write( SNS_MSG_T * OutMsg);
//
//void vSnsHandlerTask( void *pvParameters );
//
//#endif /* INC_SENSOR_H_ */
