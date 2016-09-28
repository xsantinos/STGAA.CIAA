
/*==================[inclusions]=============================================*/

#include "led.h"
/*==================[macros and definitions]=================================*/

/*Las siguientes constantes corresponden al número de paquete de pines
 * donde se encuentran los leds RGB.*/
	#define LED_RGB_R_PACK_NUMBER 2
	#define LED_RGB_G_PACK_NUMBER 2
	#define LED_RGB_B_PACK_NUMBER 2

/*Las siguientes constantes corresponden al pin dentro del paquete
 * donde se encuentran los leds RGB.*/
	#define LED_RGB_R_PACK_PIN 0
	#define LED_RGB_G_PACK_PIN 1
	#define LED_RGB_B_PACK_PIN 2

/*Las siguientes constantes simbólicas refieren al número de puerto
 * de propósito general donde se encuentran los leds R, G y B.
 * En los tres casos corresponde a GPIO05. */
	#define LED_RGB_R_GPIO_NUMBER 5
	#define LED_RGB_G_GPIO_NUMBER 5
	#define LED_RGB_B_GPIO_NUMBER 5

/*Las siguientes constantes simbólicas refieren al pin dentro del
 * puerto (GPIO05) donde se encuentran los leds R, G y B.*/
	#define LED_RGB_R_GPIO_PIN 0
	#define LED_RGB_G_GPIO_PIN 1
	#define LED_RGB_B_GPIO_PIN 2

/*Las siguientes constantes corresponden al número de paquete de pines
 * donde se encuentran los leds Rojo(1), Amarillo(2) y Verde(3).*/
	#define LED_1_PACK_NUMBER 2
	#define LED_2_PACK_NUMBER 2
	#define LED_3_PACK_NUMBER 2

/*Las siguientes constantes corresponden al pin dentro del paquete
 * donde se encuentran los leds Rojo(1), Amarillo(2) y Verde(3).*/
	#define LED_1_PACK_PIN 10
	#define LED_2_PACK_PIN 11
	#define LED_3_PACK_PIN 12

/*Las siguientes constantes toman el número del puerto de propósito
 * general (GPIO) donde se encuentran los led Rojo(1), Amarillo(2) y Verde(3)*/
	#define LED_1_GPIO_NUMBER 0
	#define LED_2_GPIO_NUMBER 1
	#define LED_3_GPIO_NUMBER 1

/*Las siguientes constantes toman el número del pin dentro del puerto
 * GPIO donde se encuentran cada uno de los leds Rojo(1), Amarillo(2) y Verde(3)*/
	#define LED_1_GPIO_PIN 14 // Rojo
	#define LED_2_GPIO_PIN 11  // Amarillo
	#define LED_3_GPIO_PIN 12 // Verde


/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/


/*Configuración de los pines/puertos*/
void InitGPIO_EDUCIAA_Leds(void)
{
	Chip_GPIO_Init(LPC_GPIO_PORT);
/*Mapeo de pines de los leds RGB:
 * El primer número corresponde al número de paquete de pines del micro.
 * El segundo número corresponde al pin dentro de ese paquete.
 * MD_PUP habilita el pull up de ese pin. Por lo tanto, se habilita para los tres.
 * FUNC4 establece la función del pin, que corresponde a GPIO para los tres.
 * De este modo, el mapeo resulta:
 * 		P2_0 (LED0R) en GPIO 5[0]
 * 		P2_1 (LED0G) en GPIO 5[1]
 * 		P2_2 (LED0B) en GPIO 5[2]*/
	Chip_SCU_PinMux( LED_RGB_R_PACK_NUMBER, LED_RGB_R_GPIO_PIN, MD_PUP, FUNC4);
    Chip_SCU_PinMux( LED_RGB_G_PACK_NUMBER, LED_RGB_G_GPIO_PIN, MD_PUP, FUNC4);
    Chip_SCU_PinMux( LED_RGB_B_PACK_NUMBER, LED_RGB_B_GPIO_PIN, MD_PUP, FUNC4);

/*Mapeo de pines de los leds 1, 2 y 3:
 * El primer número corresponde al número de paquete de pines del micro.
 * El segundo número corresponde al pin dentro de ese paquete.
 * MD_PUP habilita el pull up de ese pin. Por lo tanto, se habilita para los tres.
 * FUNC4 establece la función del pin, que corresponde a GPIO para los tres.
 * De este modo, el mapeo resulta:
 * 		P2_10 (LED1) en GPIO 0[14]
 * 		P2_11 (LED2) en GPIO 1[11]
 * 		P2_12 (LED3) en GPIO 1[12]*/
    Chip_SCU_PinMux( LED_1_PACK_NUMBER,LED_1_PACK_PIN, MD_PUP, FUNC0);
    Chip_SCU_PinMux( LED_2_PACK_NUMBER,LED_2_PACK_PIN, MD_PUP, FUNC0);
    Chip_SCU_PinMux( LED_3_PACK_NUMBER,LED_3_PACK_PIN, MD_PUP, FUNC0);

/* Configuración como salida para los leds RGB */
    Chip_GPIO_SetDir(LPC_GPIO_PORT, 5,(1<<0),1);
    Chip_GPIO_SetDir(LPC_GPIO_PORT, 5,(1<<2),1);
    Chip_GPIO_SetDir(LPC_GPIO_PORT, 5,(1<<1),1);



    /* Configuración como salida para el led LED1 */
    Chip_GPIO_SetDir(LPC_GPIO_PORT, LED_1_GPIO_NUMBER,(1<<14),1);
    /* Configuración como salida para los leds LED2 y LED3 */
    Chip_GPIO_SetDir(LPC_GPIO_PORT, 1,(1<<11)|(1<<12),1);

    /*Se apagan los leds.*/
    Chip_GPIO_ClearValue(LPC_GPIO_PORT, 5,(1<<0)|(1<<1)|(1<<2));
    Chip_GPIO_ClearValue(LPC_GPIO_PORT, 0,(1<<14));
    Chip_GPIO_ClearValue(LPC_GPIO_PORT, 1,(1<<11)|(1<<12));
}

/*Función para encender alguno de los leds 1, 2 y 3. Qué led se enciende
 * depende del parámetro "led", que recibe la función.*/
void LEDon(uint8_t led) {
	switch(led){
	case LED_ROJO: // Led 1
		Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT, LED_1_GPIO_NUMBER, LED_1_GPIO_PIN);
		break;
	case LED_AMARILLO: // Led 2
		Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT, LED_2_GPIO_NUMBER, LED_2_GPIO_PIN);
		break;
	case LED_VERDE: // Led 3
		Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT, LED_3_GPIO_NUMBER, LED_3_GPIO_PIN);
		break;
	}
}

/*Función para apagar alguno de los leds 1, 2 y 3. Qué led se apaga
 * depende del parámetro "led", que recibe la función.*/
void LEDoff(uint8_t led){
	switch(led){
		case LED_ROJO: // Led 1
			Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT, LED_1_GPIO_NUMBER, LED_1_GPIO_PIN);
			break;
		case LED_AMARILLO: // Led 2
			Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT, LED_2_GPIO_NUMBER, LED_2_GPIO_PIN);
			break;
		case LED_VERDE: // Led 3
			Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT, LED_3_GPIO_NUMBER, LED_3_GPIO_PIN);
			break;
	}
}

/*Función para alternar el estado de alguno de los leds 1, 2 y 3. Sobre qué led
 * se opera depende del parámetro "led", que recibe la función.*/
void ToggleLed(uint8_t led){
	switch(led){
	case LED_ROJO: // Led 1
		Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, LED_1_GPIO_NUMBER, LED_1_GPIO_PIN);
		break;
	case LED_AMARILLO: // Led 2
		Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, LED_2_GPIO_NUMBER, LED_2_GPIO_PIN);
		break;
	case LED_VERDE: // Led 3
		Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, LED_3_GPIO_NUMBER, LED_3_GPIO_PIN);
		break;
	}
}

/*Función para alternar el estado de uno o más leds dentro del led RGB.*/
void ToggleLedRGB(edu_CIAA_ledRGB *rgb){
	if (rgb->red == 1){
	Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, LED_RGB_R_GPIO_NUMBER, LED_RGB_R_GPIO_PIN);
	}
	if (rgb->green == 1){
		Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, LED_RGB_G_GPIO_NUMBER, LED_RGB_G_GPIO_PIN);
	}
	if (rgb->blue == 1){
		Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, LED_RGB_B_GPIO_NUMBER, LED_RGB_B_GPIO_PIN);
	}
}

/*Función para encender uno o más leds dentro del led RGB.*/
void RGBon (edu_CIAA_ledRGB *rgb){
	if (rgb->red != 0){
		Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT, LED_RGB_R_GPIO_NUMBER, LED_RGB_R_GPIO_PIN);
	}
	if (rgb->green != 0){
		Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT, LED_RGB_G_GPIO_NUMBER, LED_RGB_G_GPIO_PIN);
	}
	if (rgb->blue != 0){
		Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT, LED_RGB_B_GPIO_NUMBER, LED_RGB_B_GPIO_PIN);
	}
}

/*Función para apagar uno o más leds dentro del led RGB.*/
void RGBoff (edu_CIAA_ledRGB *rgb){
	if (rgb->red == 0){
		Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT, LED_RGB_R_GPIO_NUMBER, LED_RGB_R_GPIO_PIN);
	}
	if (rgb->green == 0){
		Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT, LED_RGB_G_GPIO_NUMBER, LED_RGB_G_GPIO_PIN);
	}
	if (rgb->blue == 0){
		Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT, LED_RGB_B_GPIO_NUMBER, LED_RGB_B_GPIO_PIN);
	}
}
/*==================[external functions definition]==========================*/

/*==================[end of file]============================================*/

