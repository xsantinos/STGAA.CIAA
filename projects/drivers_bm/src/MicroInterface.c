/*
   ********************* Authors *********************
   ***** Laboratorio de Sistemas Embebidos (LSE) *****
   *****    http://laboratorios.fi.uba.ar/lse    *****
   ******************* 20/12/2011 ********************
     Ezequiel Espósito <ezequiel.esposito@gmail.com>
         Alan Kharsansky <akharsa@gmail.com>
       Federico Roasio <federoasio@gmail.com>
     Daniel Schermuk <daniel.schermuk@gmail.com>
   ***************************************************
*/

#include <stdint.h>
#include "MicroInterface.h"
#include "chip.h"

uint32_t MaskedBuf;

//Mapeo de pines y seteo como salida
inline void MicroInterface_Init ()
{
	Chip_GPIO_Init(LPC_GPIO_PORT);

	// Mapeo pines de datos EDU-CIAA
	Chip_SCU_PinMux( D0_PACK, D0_PIN, MD_PUP, D0_FUNC); //D0
	Chip_SCU_PinMux( D1_PACK, D1_PIN, MD_PUP, D1_FUNC); //D1
	Chip_SCU_PinMux( D2_PACK, D2_PIN, MD_PUP, D2_FUNC); //D2
	Chip_SCU_PinMux( D3_PACK, D3_PIN, MD_PUP, D3_FUNC); //D3
	Chip_SCU_PinMux( D4_PACK, D4_PIN, MD_PUP, D4_FUNC); //D4
	Chip_SCU_PinMux( D5_PACK, D5_PIN, MD_PUP, D5_FUNC); //D5
	Chip_SCU_PinMux( D6_PACK, D6_PIN, MD_PUP, D6_FUNC); //D6
	Chip_SCU_PinMux( D7_PACK, D7_PIN, MD_PUP, D7_FUNC); //D7

	// Mapeo pines de datos CIAA-NXP
//	Chip_SCU_PinMux( 1, 16, MD_PUP, FUNC0); //D0 - GPIO3
//	Chip_SCU_PinMux( 1, 0, MD_PUP, FUNC0); //D1 - GPIO0[4]
//	Chip_SCU_PinMux( 6, 6, MD_PUP, FUNC0); //D2 - GPIO5
//	Chip_SCU_PinMux( 3, 6, MD_PUP, FUNC0); //D3 - GPIO6
//	Chip_SCU_PinMux( 2, 7, MD_PUP, FUNC0); //D4 - GPIO7
//	Chip_SCU_PinMux( 1, 1, MD_PUP, FUNC0); //D5 - GPIO8
//	Chip_SCU_PinMux( 1, 2, MD_PUP, FUNC0); //D6 - GPIO9
//	Chip_SCU_PinMux( 1, 3, MD_PUP, FUNC0); //D7 - GPIO10



	//Mapeo pines de controL EDU-CIAA
	Chip_SCU_PinMux( D_I_PACK, D_I_PIN, MD_PUP, D_I_FUNC); //DI
	Chip_SCU_PinMux( R_W_PACK, R_W_PIN, MD_PUP, R_W_FUNC);  //R_W
	Chip_SCU_PinMux( EN_PACK, EN_PIN, MD_PUP, EN_FUNC);  //EN
	Chip_SCU_PinMux( CSEL1_PACK, CSEL1_PIN, MD_PUP, CSEL1_FUNC);  //CS1
	Chip_SCU_PinMux( CSEL2_PACK, CSEL2_PIN, MD_PUP, CSEL2_FUNC);  //CS2
//	Chip_SCU_PinMux( 6, 10, MD_PUP, FUNC0); //RST - Activo por bajo, entonces lo dejo en alto.  // NO!!! - GPIO6
//	 Set as digital outputs LCD control lines

	//Mapeo pines de controL CIAA-NXP
//	Chip_SCU_PinMux( 0, 0, MD_PUP, FUNC0); //DI		- GPIO0
//	Chip_SCU_PinMux( 0, 1, MD_PUP, FUNC0);  //R_W		- GPIO1
//	Chip_SCU_PinMux( 1, 15, MD_PUP, FUNC0);  //EN		- GPIO2
//	Chip_SCU_PinMux( 1, 4, MD_PUP, FUNC0);  //CS1		- GPIO11
//	Chip_SCU_PinMux( 1, 17, MD_PUP, FUNC0);  //CS2		- GPIO12
//	Chip_SCU_PinMux( 1, 18, MD_PUP, FUNC0); //RST		- GPIO13 Activo por bajo, entonces lo dejo en alto.  // NO!!!



	Chip_GPIO_SetPinDIROutput (LPC_GPIO_PORT, D_I_PORT, D_I ); //DI
	Chip_GPIO_SetPinDIROutput (LPC_GPIO_PORT, R_W_PORT, R_W ); //R_W
	Chip_GPIO_SetPinDIROutput (LPC_GPIO_PORT, EN_PORT, EN ); //EN
	Chip_GPIO_SetPinDIROutput (LPC_GPIO_PORT, LCD_CSEL1_PORT, CSEL1 ); //CS1
	Chip_GPIO_SetPinDIROutput (LPC_GPIO_PORT, LCD_CSEL2_PORT, CSEL2 ); //CS2

	// Set as digital outputs LCD data lines

	Chip_GPIO_SetPinDIROutput (LPC_GPIO_PORT, D0_PORT, D0 ); //D0
	Chip_GPIO_SetPinDIROutput (LPC_GPIO_PORT, D1_PORT, D1 ); //D1
	Chip_GPIO_SetPinDIROutput (LPC_GPIO_PORT, D2_PORT, D2 ); //D2
	Chip_GPIO_SetPinDIROutput (LPC_GPIO_PORT, D3_PORT, D3 ); //D3
	Chip_GPIO_SetPinDIROutput (LPC_GPIO_PORT, D4_PORT, D4 ); //D4
	Chip_GPIO_SetPinDIROutput (LPC_GPIO_PORT, D5_PORT, D5 ); //D5
	Chip_GPIO_SetPinDIROutput (LPC_GPIO_PORT, D6_PORT, D6 ); //D6
	Chip_GPIO_SetPinDIROutput (LPC_GPIO_PORT, D7_PORT, D7 ); //D7

//	Chip_GPIO_SetPinDIROutput(LPC_GPIO_T, LCD_DATA_PORT,D0);
//	Chip_GPIO_SetPinDIROutput(LPC_GPIO_T, LCD_DATA_PORT,D1);
//	Chip_GPIO_SetPinDIROutput(LPC_GPIO_T, LCD_DATA_PORT,D2);
//	Chip_GPIO_SetPinDIROutput(LPC_GPIO_T, LCD_DATA_PORT,D3);
//	Chip_GPIO_SetPinDIROutput(LPC_GPIO_T, LCD_DATA_PORT,D4);
//	Chip_GPIO_SetPinDIROutput(LPC_GPIO_T, LCD_DATA_PORT,D5);
//	Chip_GPIO_SetPinDIROutput(LPC_GPIO_T, LCD_DATA_PORT,D6);
//	Chip_GPIO_SetPinDIROutput(LPC_GPIO_T, LCD_DATA_PORT,D7);

//	Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT, 3, 6); //Dejo RST en alto. NOOOO
}

inline void MicroInterface_Bit_WriteLow (uint8_t port, uint8_t pin)
{

	Chip_GPIO_SetPinState(LPC_GPIO_PORT, port, pin, false);
}

inline void MicroInterface_Bit_WriteHigh (uint8_t port, uint8_t pin)
{
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, port, pin, true);
}

inline void MicroInterface_Byte_WriteData (uint8_t buf)
{

	Chip_GPIO_SetPinState (LPC_GPIO_PORT, D0_PORT, D0, (buf>>0 & 0x01) ); //D0
	Chip_GPIO_SetPinState (LPC_GPIO_PORT, D1_PORT, D1,  (buf>>1 & 0x01) ); //D1
	Chip_GPIO_SetPinState (LPC_GPIO_PORT, D2_PORT, D2,  (buf>>2 & 0x01) ); //D2
	Chip_GPIO_SetPinState (LPC_GPIO_PORT, D3_PORT, D3,  (buf>>3 & 0x01) ); //D3
	Chip_GPIO_SetPinState (LPC_GPIO_PORT, D4_PORT, D4,  (buf>>4 & 0x01) ); //D4
	Chip_GPIO_SetPinState (LPC_GPIO_PORT, D5_PORT, D5,  (buf>>5 & 0x01) ); //D5
	Chip_GPIO_SetPinState (LPC_GPIO_PORT, D6_PORT, D6,  (buf>>6 & 0x01) ); //D6
	Chip_GPIO_SetPinState (LPC_GPIO_PORT, D7_PORT, D7, (buf>>7 & 0x01) ); //D7

//	Chip_GPIO_SetPinState (LPC_GPIO_PORT, 5, 12, (MaskedBuf>>0 & 0x01) ); //D0
//		Chip_GPIO_SetPinState (LPC_GPIO_PORT, 2, 6,  (MaskedBuf>>1 & 0x01) ); //D1
//		Chip_GPIO_SetPinState (LPC_GPIO_PORT, 2, 5,  (MaskedBuf>>2 & 0x01) ); //D2
//		Chip_GPIO_SetPinState (LPC_GPIO_PORT, 2, 4,  (MaskedBuf>>3 & 0x01) ); //D3
//		Chip_GPIO_SetPinState (LPC_GPIO_PORT, 3, 0,  (MaskedBuf>>4 & 0x01) ); //D4
//		Chip_GPIO_SetPinState (LPC_GPIO_PORT, 3, 3,  (MaskedBuf>>5 & 0x01) ); //D5
//		Chip_GPIO_SetPinState (LPC_GPIO_PORT, 3, 4,  (MaskedBuf>>6 & 0x01) ); //D6
//		Chip_GPIO_SetPinState (LPC_GPIO_PORT, 5, 15, (MaskedBuf>>7 & 0x01) ); //D7
//
	//Chip_GPIO_SetPortOutHigh(LPC_GPIO_T, LCD_DATA_PORT, MaskedBuf);
	//Chip_GPIO_SetPortOutLow(LPC_GPIO_T, LCD_DATA_PORT, buf);
}


