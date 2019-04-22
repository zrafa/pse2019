
/* Enciende y apaga un led conectado al puerto B bit 5 de un atmega328 */

/* 
 * El puerto B de un atmega328 tiene los bits 0-5 mapeados a los 
 * pines 8-13 de arduino 
 */

#include "utils.h"

int main(void)
{	
	volatile unsigned char vboton = 0x00;
	volatile unsigned char modo = 0x00;
	volatile unsigned char contador = 0x00;
	volatile unsigned long i;
	init();

	while (1) {
		//vboton = (*pin_b)&BOTON;
		for (i=0;i<450000; i++){
			vboton = (*pin_b)&BOTON;
		}
		if(vboton == 0x00){
			for (i=0;i<450000; i++){
				vboton = (*pin_b)&BOTON;
			}
			//vboton = (*pin_b)&BOTON;
			if(vboton = 0x01){
				modo = ~modo;
			}
		}
		if (modo ==0x00){
			leds_prender();
			esperar();
			leds_apagar();
		}else{
			incremento_binario(&contador);
			leds_contador(contador << 3);
		}
		esperar();
		//init();
    	}
}


