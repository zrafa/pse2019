#include "utils.h"
#include "serial.h"
#include "adc.c"
#include <stdlib.h>

/* 	
	ACLARACION
	Si se trabaja con minicom para verificar el funcionamiento,
	debe tenerse en cuenta el valor ascii de los números.
	Arduino->Minicom: Se debe sumar 48 al valor char para que pueda ser visto en la terminal.
	Minicom->Arduino: Se debe restar 48 al valor leido por serial ya que leds_prender espera
	valores entre 0 y 7	
*/

int main(void)
{
	char c;
	int valor_luz;
	int cant_val_rango=1024/8; /* Los 1024 valores posibles del ADC se mapean a 8 valores del rango [0-7] */

	led_init(); 
	serial_init();
	adc_init();

	while (1) 
	{         
		if (serial_recibido()) 
		{ /* Se recibe un valor desde el otro arduino */
			c = serial_get_char();
			leds_prender(c);                     
		}         
		if (hubo_click()) 
		{  /* Al presionar un boton se lee el ADC y se envia al otro arduino */    
			valor_luz = adc_get(0); /* Se lee la entrada analógica 0 */ 
			c = valor_luz/cant_val_rango;
			serial_put_char(c); 
		}        
	}
}

	




