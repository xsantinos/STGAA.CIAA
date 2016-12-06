/** @file Display.c
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


#include "Display.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "Bitmaps.h"
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
void DSP_Init (void)
{
	GUI_StartLibrary();
	GUI_Window_ListInit();

	char Start[10] = "Start";
	char text_start[20] = "STGAA ADSCRIPCION";
	GUI_Window_Create (Start, WHITE, text_start );

	GUI_Window_AddText (Start, "row1", 55, 13, "SystemFont5x7", WHITE,  "LAB DE PROTOTIPADO");
	GUI_Window_AddText (Start, "row1", 55, 21, "SystemFont5x7", WHITE,  " ELECTRONICO Y 3D");
	GUI_Window_AddText (Start, "row2", 55, 30, "SystemFont5x7", WHITE,  " -Director:");
	GUI_Window_AddText (Start, "row3", 55, 38, "SystemFont5x7", WHITE,  "Bioing. Martina M.");
	GUI_Window_AddText (Start, "row4", 55, 48, "SystemFont5x7", WHITE,  " -Adscripto:");
	GUI_Window_AddText (Start, "row5", 55, 56, "SystemFont5x7", WHITE,  "Borghi Santiago");

	GUI_Window_AddPicture (Start, "Logo", 5, 23, 48, 40, InicioBitmaps, BLACK );
	/*Dibujar esta ventana completa */

	char Main[10] = "Main";
	char text_main[20] = "STGAA - SENSADO";

	GUI_Window_Create  (Main, WHITE, text_main);

	GUI_Window_AddPicture (Main, "thy",  81, 20,  9, 16, TyhBitmaps,   WHITE);
	GUI_Window_AddPicture (Main, "wind",  6, 40, 11, 16, WindsBitmaps, WHITE);
	GUI_Window_AddPicture (Main, "gps",   6, 20, 11, 16, GpsBitmaps,   WHITE);
	GUI_Window_AddPicture (Main, "flow", 81, 40,  7, 16, FlowBitmaps,  WHITE);

	GUI_Window_AddText (Main, "_temp", 93, 15, "SystemFont5x7", WHITE,  "T:32.51C");
	GUI_Window_AddText (Main, "_hum",  93, 25, "SystemFont5x7", WHITE,   "H: 63%  ");

	GUI_Window_AddText (Main, "_lat",  22, 15, "SystemFont5x7", WHITE, "20 15 17.16 S");
	GUI_Window_AddText (Main, "_long", 22, 25, "SystemFont5x7", WHITE, "17 18 23.08 O");

	GUI_Window_AddText (Main, "_wind", 22, 44, "SystemFont5x7", WHITE, "15.3 km/h SE");

	GUI_Window_AddText (Main, "_flow", 93, 44, "SystemFont5x7", WHITE, "1.3 L/h");

	GUI_Window_Draw (Start);
}

void DSP_MainMode (void)
{
	GUI_Window_Draw ("Main\n");
}

void DSP_RefreshDisplay(ENV_ENVIRONMENTAL_T* _pEnv)
{
	STATIC char Main[10] = "Main\n";

		uint32_t temp = (_pEnv->tyh.temperature)*100;
		uint8_t dec_grad, unid_grad, decima, centes, size;
		dec_grad = temp/1000;
		unid_grad = (temp-dec_grad*1000)/100;
		decima = (temp-dec_grad*1000-unid_grad*100)/10;
		centes = temp-dec_grad*1000-unid_grad*100-decima*10;
		char auxtemp[5];
		auxtemp[0] = dec_grad + 48;
		auxtemp[1] = unid_grad + 48;
		auxtemp[2] = 46; //punto
		auxtemp[3] = decima + 48;
		auxtemp[4] = centes + 48;
		char TEMP[8] = "T:";
		size = 8;
		strcat (TEMP,auxtemp);
		TEMP[7] = 67; // C
	GUI_Window_EditText (Main, "_temp", TEMP, size);

		uint32_t hum = (_pEnv->tyh.humidity);
		uint8_t dec, unid;

		dec = hum/10;
		unid = hum - dec*10;

		char auxhum[2];
		auxhum[0] = dec + 48;
		auxhum[1] = unid + 48;
		char HUM[6] = "H: ";
		strcat (HUM,auxhum);
		HUM[5] = 37; // %
		size = 6;
	GUI_Window_EditText (Main, "_hum", HUM, size);

		uint32_t lat_deg = (_pEnv->gps.lat_deegres);

		uint8_t latd_dec, latd_unid;
		latd_dec = lat_deg/10;
		latd_unid = lat_deg - latd_dec*10;


		uint32_t lat_min = (_pEnv->gps.lat_minutes);

		uint8_t latm_dec, latm_unid;
		latm_dec = lat_min/10;
		latm_unid = lat_min - latm_dec*10;


		uint32_t lat_sec = (_pEnv->gps.lat_seconds);

		lat_sec*= 100;
		uint8_t lats_dec, lats_unid, lats_decima, lats_centes;
		lats_dec = lat_sec/1000;
		lats_unid = lat_sec/100 - lats_dec*10;
		lats_decima = lat_sec/10 - lats_dec*100 - lats_unid*10;
		lats_centes = lat_sec - lats_dec*1000 - lats_unid*100 - lats_decima*10;

		char LAT[13];
		LAT[0] = latd_dec + 48;
		LAT[1] = latd_unid + 48;
		LAT[2] = 32;
		LAT[3] = latm_dec + 48;
		LAT[4] = latm_unid + 48;
		LAT[5] = 32;
		LAT[6] = lats_dec + 48;
		LAT[7] = lats_unid + 48;
		LAT[8] = 46;//punto
		LAT[9] = lats_decima + 48;
		LAT[10] = lats_centes + 48;
		LAT[11] = 32;
		LAT[12] = 83;
		size = 13;

	GUI_Window_EditText (Main, "_lat", LAT, size);


		uint32_t long_deg = (_pEnv->gps.long_deegres);

		uint8_t longd_dec, longd_unid;
		longd_dec = long_deg/10;
		longd_unid = long_deg - longd_dec*10;


		uint32_t long_min = (_pEnv->gps.long_minutes);

		uint8_t longm_dec, longm_unid;
		longm_dec = long_min/10;
		longm_unid = long_min - longm_dec*10;

		uint32_t long_sec = (_pEnv->gps.long_seconds);
		long_sec *= 100;
		uint8_t longs_dec, longs_unid, longs_decima, longs_centes;
		longs_dec = long_sec/1000;
		longs_unid = long_sec/100 - longs_dec*10;
		longs_decima = long_sec/10 - longs_dec*100 - longs_unid*10;
		longs_centes = long_sec - longs_dec*1000 - longs_unid*100 - longs_decima*10;

		char LON[13];
		LON[0] = longd_dec + 48;
		LON[1] = longd_unid + 48;
		LON[2] = 32;
		LON[3] = longm_dec + 48;
		LON[4] = longm_unid + 48;
		LON[5] = 32;
		LON[6] = longs_dec + 48;
		LON[7] = longs_unid + 48;
		LON[8] = 46;//punto
		LON[9] = longs_decima + 48;
		LON[10] = longs_centes + 48;
		LON[11] = 32;
		LON[12] = 79;// O(este)
		size = 13;

	GUI_Window_EditText (Main, "_long", LON, size);

		uint32_t wspeed = (_pEnv->wind.speed);
		uint8_t dir = (_pEnv->wind.direction);
		uint8_t speed_dec, speed_unid, speed_decima;
		wspeed*= 100;
		speed_dec = wspeed/100;
		speed_unid = wspeed/10 - speed_dec*10;
		speed_decima = wspeed - speed_dec * 100 - speed_unid * 10;

		char WIND[11];
		WIND[0] = speed_dec + 48;
		WIND[1] = speed_unid + 48;
		WIND[2] = 46; //punto
		WIND[3] = speed_decima + 48;
		WIND[4] = 32;
		WIND[5] = 107; //k
		WIND[6] = 109; //m
		WIND[7] = 47; // /
		WIND[8] = 104;// h
		WIND[9] = 32;
		WIND[10] = dir + 48; //suponiendo que dir está codificada en ascii

	size = 11;
	GUI_Window_EditText (Main, "_wind", WIND, size);

		uint32_t flow = (_pEnv->flow.value);
		flow *= 10;
		uint8_t flow_unid, flow_decima;
		flow_unid = flow/10;
		flow_decima = flow - flow_unid*10;

		char FLOW[7];
		FLOW[0] = flow_unid + 48;
		FLOW[1] = 46; // Punto
		FLOW[2] = flow_decima + 48;
		FLOW[3] = 32; //
		FLOW[4] = 76; // L
		FLOW[5] = 47; // /
		FLOW[6] = 104;

	size = 7;
	GUI_Window_EditText (Main, "_flow", FLOW, size);

	DSP_MainMode();
}
