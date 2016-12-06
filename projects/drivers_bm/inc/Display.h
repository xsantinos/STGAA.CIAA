/*
 * Display.h
 *
 *  Created on: 21/1/2016
 *      Author: Prototipado
 */

#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_

#include "lpc_types.h"
#include "GLCDgui.h"
#include "window.h"
#include "Environmental.h"

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/*****************************************************************************
 * Public functions
 ****************************************************************************/
void DSP_Init(void);

void DSP_MainMode (void);

void DSP_RefreshDisplay(ENV_ENVIRONMENTAL_T* pEnvironmental);

//void DSP_GetTemp (char* _temp, ENV_ENVIRONMENTAL_T* _pEnv);
//
//void DSP_GetHum (char* _temp, ENV_ENVIRONMENTAL_T* _pEnv);
#endif /* INC_DISPLAY_H_ */
