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

// ********************************
// Microcontroller Interface (Head)
// ********************************

#ifndef _MICROINTERFACE_H_
#define _MICROINTERFACE_H_

#include <stdint.h>

// ********************************
// LPC pins assigned to LCD WG12864
// ********************************
#define CSEL2_PACK			1
#define CSEL2_PIN			18		// CS2 P1_18
#define CSEL2_FUNC			0

#define CSEL1_PACK			1
#define CSEL1_PIN			20		// CS1 P1_20
#define CSEL1_FUNC			0

#define D_I_PACK			6		// D/I Bit
#define D_I_PIN				12
#define D_I_FUNC			0

#define R_W_PACK			6		// R/W Bit
#define R_W_PIN				11
#define R_W_FUNC			0

#define EN_PACK				6		// EN Bit
#define EN_PIN				9
#define EN_FUNC				0

//#define LCD_DATA_PORT		0
#define D0_PACK				6
#define D0_PIN				7
#define D0_FUNC				4

#define D1_PACK				6
#define D1_PIN				4
#define D1_FUNC				0

#define D2_PACK				4
#define D2_PIN				4
#define D2_FUNC				0

#define D3_PACK				4
#define D3_PIN				5
#define D3_FUNC				0

#define D4_PACK				4
#define D4_PIN				6
#define D4_FUNC				0

#define D5_PACK				4
#define D5_PIN				8
#define D5_FUNC				4

#define D6_PACK				4
#define D6_PIN				10
#define D6_FUNC				4

#define D7_PACK				1
#define D7_PIN				3
#define D7_FUNC				0


#define LCD_CSEL2_PORT		0
#define CSEL2				13		// CS2 P1_18

#define LCD_CSEL1_PORT		0
#define CSEL1				15		// CS1 P1_20

#define D_I_PORT			2		// D/I Bit
#define D_I					8

#define R_W_PORT			3		// R/W Bit
#define R_W					7

#define EN_PORT				3		// EN Bit
#define EN					5

//#define LCD_DATA_PORT		0
#define D0_PORT				5
#define D0					15
#define D1_PORT				3
#define D1					3
#define D2_PORT				2
#define D2					4
#define D3_PORT				2
#define D3					5
#define D4_PORT				2
#define D4					6
#define D5_PORT				5
#define D5					12
#define D6_PORT				5
#define D6					14
#define D7_PORT				0
#define D7					10

#define true 1
#define false 0


// ******************************
// LPC digital I/O pins Functions
// ******************************
inline void MicroInterface_Init ();
inline void MicroInterface_Bit_WriteLow (uint8_t port, uint8_t pin);
inline void MicroInterface_Bit_WriteHigh (uint8_t port, uint8_t pin);
inline void MicroInterface_Byte_WriteData (uint8_t buf);

// ******
// Macros
// ******
#define EN_DELAY() for (_delayCounter=0; _delayCounter<10; _delayCounter++);

#endif
