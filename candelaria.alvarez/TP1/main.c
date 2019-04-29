
/* Enciende y apaga un led conectado al puerto B bit 5 de un atmega328 */

/* 
 * El puerto B de un atmega328 tiene los bits 0-5 mapeados a los 
 * pines 8-13 de arduino 
 */

#include "utils.h"



int main(void)
{
	led_init(); 

	char modo = 0, click = 0;

    while (1) {

		click = hubo_click();

		if(click) { /*Cambia de Modo*/
			if(modo){
				modo = 0;
				modo_0();

			} else { 
				modo = 1;
				modo_1();
			}	
		}else {/*NO cambia de Modo*/
				
			if(modo){
				modo_1();
			} 
			else {
				modo_0();
			}
		}



	}

}


