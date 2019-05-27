#include "utils.h"
#include "serial.h"
#include "adc.h"
#include <stdlib.h>
#include <util/delay.h>

/* 	
	ACLARACION
	Si se trabaja con minicom para verificar el funcionamiento,
	debe tenerse en cuenta el valor ascii de los números.
	Arduino->Minicom: Se debe sumar 48 al valor char para que pueda ser visto en la terminal.
	Minicom->Arduino: Se debe restar 48 al valor leido por serial ya que leds_prender espera
	valores entre 0 y 7	
*/

/* 
	La fotoresistencia en un ambiente con luz da 4.6k
	En completa oscuridad da 200ohm
*/


int main(void)
{
	char c;
	int valor_luz, valor_led;
	int cant_val_rango=1024/8; /* Los 1024 valores posibles del ADC se mapean a 8 valores del rango [0-7] */
	
	led_init(); 
	serial_init();
	adc_init();

	while (1) 
	{         
		if (serial_recibido()) 
		{ 
			c = serial_get_char();
			leds_prender(c);
               
		}        
		if (hubo_click()) 
		{  
			valor_luz = adc_get(0); //int
			valor_led =  valor_luz/cant_val_rango; //int
			c = valor_led%10;       //char
			serial_put_char(c);
			_delay_ms(1000);
		}    

		
	}

}

	




