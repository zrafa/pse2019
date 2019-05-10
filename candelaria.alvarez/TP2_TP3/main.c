#include "utils.h"
#include "serial.h"
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

	led_init(); 
	serial_init();

	while (1) 
	{         
		if (serial_recibido()) 
		{ /* Se recibe un valor desde el otro arduino */
			c = serial_get_char();
			leds_prender(c);                     
		}         
		if (hubo_click()) 
		{  /* Al presionar un boton se genera un num random y se envia al otro arduino */    
			c = rand()%8;       
			serial_put_char(c); 
		}        
	}
}

	




