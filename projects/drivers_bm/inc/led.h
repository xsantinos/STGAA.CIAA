
#ifndef LED_H
#define LED_H

/*==================[inclusions]=============================================*/


#include "chip.h"
#include "stdint.h"
/*==================[macros]=================================================*/
#define lpc4337            1
#define mk60fx512vlq15     2

/*==================[typedef]================================================*/

/*Defino la estructura "edu_CIAA_ledRGB", dado que el led RGB
 * se maneja con tres valores, R, G y B.*/
typedef struct{
	uint8_t red;
	uint8_t green;
	uint8_t blue;
}edu_CIAA_ledRGB;

/*==================[external data declaration]==============================*/

/*Esta enumeración la voy a usar para indicar a qué led de los
 * individuales de la EDU-CIAA estoy accediendo en las funciones
 * que me permitan encenderlos, apagarlos o alternar sus estados
 * (toggle).*/
enum LED_COLOR {LED_ROJO, LED_AMARILLO, LED_VERDE, LED_RGB};

/*==================[external functions declaration]=========================*/

/*Función para inicializar los puertos de modo tal que después
 * pueda manejar los leds.*/
void InitGPIO_EDUCIAA_Leds(void);

/*Función que me permite encender un led (1,2,3). Para elegir cuál, es que
 * le paso el parámetro "led".*/
void LEDon(uint8_t led);

/*Función que me permite apagar un led (1,2,3). Para elegir cuál, es que
 * le paso el parámetro "led".*/
void LEDoff(uint8_t led);

/*Función que me permite cambiar el estado de un led (1,2,3). Para elegir
 * cuál, es que le paso el parámetro "led".*/
void ToggleLed(uint8_t led);

/*Función que me permite cambiar el estado del led RGB de la placa.
 * Recibe un puntero a una estructura "edu_CIAA_ledRGB", para
 *  trabajar con cada uno de los leds independientemente.*/
void ToggleLedRGB(edu_CIAA_ledRGB *rgb);

/*Función que enciende los leds del led RGB, de modo independiente. Los
 * estados de las variables de la estructura "rgb" indicarán qué led o leds
 * se desean encender.*/
void RGBon (edu_CIAA_ledRGB *rgb);

/*Función que apaga los leds del led RGB, de modo independiente. Los
 * estados de las variables de la estructura "rgb" indicarán qué led o leds
 * se desean apagar.*/
void RGBoff (edu_CIAA_ledRGB *rgb);


/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef MI_NUEVO_PROYECTO_H */

