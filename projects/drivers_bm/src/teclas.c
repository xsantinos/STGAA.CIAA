
/*==================[inclusions]=============================================*/

#include "teclas.h"
/*==================[macros and definitions]=================================*/

/*Las siguientes constantes corresponden al número de paquete de pines
 * donde se encuentran las teclas.*/
	#define TECLA_1_PACK_NUMBER 1
	#define TECLA_2_PACK_NUMBER 1
	#define TECLA_3_PACK_NUMBER 1
	#define TECLA_4_PACK_NUMBER 1

/*Las siguientes constantes corresponden al pin dentro del paquete
 * donde se encuentran las teclas.*/
	#define TECLA_1_PACK_PIN 0
	#define TECLA_2_PACK_PIN 1
	#define TECLA_3_PACK_PIN 2
	#define TECLA_4_PACK_PIN 6

/*Las siguientes constantes corresponden a los puertos GPIO donde se
 * encuentran las distintas teclas. Para T1, T2 y T3, GPIO0. Para T4
 * GPIO1*/
	#define TECLA_1_GPIO_NUMBER 0
	#define TECLA_2_GPIO_NUMBER 0
	#define TECLA_3_GPIO_NUMBER 0
	#define TECLA_4_GPIO_NUMBER 1

/*Las siguientes constantes corresponden a los pines dentro de los
 * puertos GPIO de cada tecla. */
	#define TECLA_1_GPIO_PIN 4
	#define TECLA_2_GPIO_PIN 8
	#define TECLA_3_GPIO_PIN 9
	#define TECLA_4_GPIO_PIN 9



/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/


/*Configuración de los pines/puertos correspondientes a las teclas*/
void InitGPIO_EDUCIAA_Teclas(void)
{
	/*mapea P1 0 en GPIO 0[4], SW1*/
	Chip_SCU_PinMux(TECLA_1_PACK_NUMBER, TECLA_1_PACK_PIN, MD_PUP|MD_EZI|MD_ZI, FUNC0);
	/*mapea P1 1 en GPIO 0[8], SW2*/
	Chip_SCU_PinMux(TECLA_2_PACK_NUMBER, TECLA_2_PACK_PIN, MD_PUP|MD_EZI|MD_ZI, FUNC0);
	/*mapea P1 2 en GPIO 0[9], SW3*/
	Chip_SCU_PinMux(TECLA_3_PACK_NUMBER, TECLA_3_PACK_PIN, MD_PUP|MD_EZI|MD_ZI, FUNC0);
	/*mapea P1 6 en GPIO 1[9], SW4*/
	Chip_SCU_PinMux(TECLA_4_PACK_NUMBER, TECLA_4_PACK_PIN, MD_PUP|MD_EZI|MD_ZI, FUNC0);

	/*Configuro los pines de las teclas como entradas.*/
	Chip_GPIO_SetDir(LPC_GPIO_PORT, TECLA_1_GPIO_NUMBER, 1<<TECLA_1_GPIO_PIN, 0);
	Chip_GPIO_SetDir(LPC_GPIO_PORT, TECLA_2_GPIO_NUMBER, 1<<TECLA_2_GPIO_PIN, 0);
	Chip_GPIO_SetDir(LPC_GPIO_PORT, TECLA_3_GPIO_NUMBER, 1<<TECLA_3_GPIO_PIN, 0);
	Chip_GPIO_SetDir(LPC_GPIO_PORT, TECLA_4_GPIO_NUMBER, 1<<TECLA_4_GPIO_PIN, 0);
}

uint8_t Detectar_Tecla (uint8_t tecla)
{
	uint8_t estado_tecla;
	switch(tecla){
	case 1:
		estado_tecla = Chip_GPIO_ReadPortBit(LPC_GPIO_PORT, TECLA_1_GPIO_NUMBER, TECLA_1_GPIO_PIN);
		break;
	case 2:
		estado_tecla = Chip_GPIO_ReadPortBit(LPC_GPIO_PORT, TECLA_2_GPIO_NUMBER, TECLA_2_GPIO_PIN);
		break;
	case 3:
		estado_tecla = Chip_GPIO_ReadPortBit(LPC_GPIO_PORT, TECLA_3_GPIO_NUMBER, TECLA_3_GPIO_PIN);
		break;
	case 4:
		estado_tecla = Chip_GPIO_ReadPortBit(LPC_GPIO_PORT, TECLA_4_GPIO_NUMBER, TECLA_4_GPIO_PIN);
		break;
	}
	return estado_tecla;
}

/*Función de Escaneo del teclado.*/
void Escaneo_Teclado (edu_CIAA_teclado *teclado)
{
	teclado->T1 = Detectar_Tecla(1);
	teclado->T2 = Detectar_Tecla(2);
	teclado->T3 = Detectar_Tecla(3);
	teclado->T4 = Detectar_Tecla(4);
}
/*==================[external functions definition]==========================*/

/*==================[end of file]============================================*/

