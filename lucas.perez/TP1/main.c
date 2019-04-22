#include "utils.h"

int main(void)
{
	char count = 0, mode = 0;
	led_init();

	while (1)
	{
		/* se consulta si el botón fué presionado para cambiar el modo
		 * de ejecución en caso afirmativo
		 */
		if (leer_boton() == 0)
		{
			if (mode == 1)
			{
				mode = 0;
			}
			else
			{
				mode = 1;
			}
		}
		/* El 1er modo envía por parametro un contador para encender los 
		 * leds según su valor
		 */
		if (mode == 0)
		{
			contador(count);
			if (count == 7)
			{
				count = 0;
			}
			else
			{
				count++;
			}
			esperar();
		}
		/* El 2do modo enciende y apaga los 3 leds juntos cada cierto
		 * de tiempo intervalo
		 */
		else
		{
			led_prender();
			esperar();
			led_apagar();
			esperar();
		}
	}
}
