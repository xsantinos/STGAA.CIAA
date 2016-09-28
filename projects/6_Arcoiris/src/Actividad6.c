

/*==================[inclusions]=============================================*/
#include "main.h"
#include "led.h"
#include "teclas.h"
#include "timer.h"
/*==================[macros and definitions]=================================*/
#define base_de_tiempo 1
#define t_color 250
#define t_periodo 20
#define N_colores 16
#define T1 1 //Es la tecla 1, para la funci√≥n DetectarTecla(tecla);
/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/
uint8_t contador_toggle = 0;
uint32_t contador_color = 0;
uint8_t contador_periodo = 0;
uint8_t color = 0;
bool flag_T1 = TRUE;

uint8_t Paleta_R[N_colores] = {20,  0,   0,  20,  20,   0,  20,  20, 20,  20,  20,  15,   15,   20,   20,   15};
uint8_t Paleta_G[N_colores] = {0,  20,   0,  20,   0,  20,  20,  20, 5,  10,   5,  20,  8,   0,   15,   15};
uint8_t Paleta_B[N_colores] = {0,   0,  20,   0,  20,  20,  20,   5, 20,   5,   5,  12,  20,   10,   15,   0};


edu_CIAA_ledRGB rgb;

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

void Togglear (void)
{
	ToggleLed(LED_VERDE);
	ToggleLed(LED_ROJO);
}

void Arcoiris(void)
{
	if (contador_color == t_color)
	{
		contador_color = 0;
		if (color == N_colores)
		{
			color = 0;
		}

		else
			color++;
	}

	if (contador_periodo == t_periodo)
	{
		rgb.blue = Paleta_B[color];
		rgb.red = Paleta_R[color];
		rgb.green = Paleta_G[color];
		contador_periodo = 0;
	}

	if (rgb.blue < contador_periodo)
		rgb.blue = 0;
	if (rgb.red < contador_periodo)
		rgb.red = 0;
	if (rgb.green < contador_periodo)
		rgb.green = 0;

	RGBon(&rgb);
	RGBoff(&rgb);
	contador_periodo++;
	contador_color++;
}


void InterrupcionRIT(void)
{
	if (!flag_T1)
		Arcoiris();
//	else
//		LEDoff(LED_AMARILLO);
/*Hasta ac·, la parte del arcoiris*/

	contador_toggle++;
	if (contador_toggle == 250)
	{
		Togglear();
		contador_toggle = 0;
	}
	Limpiar_RIT();
/*Esta ˙ltima parte sÛlo se encarga de Togglear los leds cada 250 ms.
 * proceso que es independiente del arcoiris y siempre se lleva  acabo*/
}



int main (void)
{
	InitGPIO_EDUCIAA_Teclas();
	InitGPIO_EDUCIAA_Leds();
	Inicializar_RIT();
	Setear_RIT(base_de_tiempo);

	RGBoff(&rgb);
	LEDon(LED_ROJO);


	while(1)
	{
		flag_T1 = Detectar_Tecla(T1);
		if (flag_T1 != 0)
		{
			rgb.red = 0;
			rgb.green = 0;
			rgb.blue = 0;
			RGBoff(&rgb);
			color = 0;
			contador_periodo = 0;
			contador_color = 0;
			rgb.red = Paleta_R[color];
			rgb.green = Paleta_G[color];
			rgb.blue = Paleta_B[color];
		}
	}
}
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

