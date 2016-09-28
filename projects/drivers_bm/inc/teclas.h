
#ifndef TECLAS_H
#define TECLAS_H

/*==================[inclusions]=============================================*/
#include "chip.h"
#include "stdint.h"

/*==================[macros]=================================================*/
#define lpc4337            1
#define mk60fx512vlq15     2
#define num_teclas 4
/*==================[typedef]================================================*/

/*Defino la estructura "edu_CIAA_teclado", que almacena el estado de cada tecla.
 * 1 = tecla sin presionar. 0 = tecla presionada.*/

typedef struct {
	uint8_t T1;
	uint8_t T2;
	uint8_t T3;
	uint8_t T4;
}edu_CIAA_teclado;
/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

/*Función para configurar las teclas */
void InitGPIO_EDUCIAA_Teclas(void);

/*Función para detectar tecla presionada*/
uint8_t Detectar_Tecla (uint8_t tecla);

/*Escaneo de teclado. Recibe un puntero a una estructura edu_CIAA_teclado, y
 * finalizada la función, se actualizan los estados de cada tecla en la estructura.*/
void Escaneo_Teclado (edu_CIAA_teclado *teclado);

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef TECLAS_H */

