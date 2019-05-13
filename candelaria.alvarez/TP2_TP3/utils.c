
/* TP1 */

/* El puerto B de un atmega328 tiene los bits 0-5 mapeados a los 
 * pines 8-13 de arduino. En este código se utilizan los 
 * puertos 8, 9 y 10 para los 3 leds
 */


//pinb_b (0x23)
// ddr_b (0x24) Direccion del PIN - 0 (entrada) 1 (salida)
// puerto_b (0x25) Datos de salida para los pines de salida. Para los de entrada, indica pullup activado (1) o desactivado (0)


/* mascara para el led en el arduino pro mini */
#define LED_1 (0x01) /* 0b0000 0001 - pin 8 en arduino*/
#define LED_2 (0x02) /* 0b0000 0010 - pin 9 en arduino*/
#define LED_3 (0x04) /* 0b0000 0100 - pin 10 en arduino*/
#define BOTON (0x08) /* 0b0000 1000 - pin 11 en arduino*/


/* puertos de E/S */
extern volatile unsigned char * puerto_b;
extern volatile unsigned char * ddr_b;
extern volatile unsigned char * pin_b;

void led_init()
{
	//Coloca 0 para 'apagar' lo que haya
   	*puerto_b = *puerto_b & (~LED_1);
	*puerto_b = *puerto_b & (~LED_2);
	*puerto_b = *puerto_b & (~LED_3);

	//Indica que son pines de SALIDA
	*(ddr_b) = *(ddr_b) | (LED_1);
	*(ddr_b) = *(ddr_b) | (LED_2);
	*(ddr_b) = *(ddr_b) | (LED_3);

	//Indica que el pin del boton es de ENTRADA
	*(ddr_b) = *(ddr_b) & (~BOTON);

	//Indica que el pin del botón tendrá la resistencia PULL-UP activada
	*puerto_b = *puerto_b | (BOTON);

	//Inicia en modo O
	*pin_b = *pin_b & (~BOTON);
}

char hubo_click(){
	volatile unsigned long i;
	char res = (*pin_b & BOTON);
	for (i=0; i<500000; i++){
		res &= (*pin_b & BOTON);
	}
	return (res==0x00);
}

void esperar(long tope) {

    volatile unsigned long i;

    /* delay manual */
    for (i=0; i<tope; i++);
}

void led1_prender() 
{
    *puerto_b = *puerto_b | LED_1;
}

void led2_prender() 
{
    *puerto_b = *puerto_b | LED_2;
}

void led3_prender() 
{
    *puerto_b = *puerto_b | LED_3;
}

void led1_apagar() 
{
    *puerto_b = *puerto_b & (~LED_1);
}

void led2_apagar() 
{
    *puerto_b = *puerto_b & (~LED_2);
}

void led3_apagar() 
{
    *puerto_b = *puerto_b & (~LED_3);
}

void modo_0() {

	volatile unsigned long i;

	i = 500000;

	led1_prender();
	led2_prender();
	led3_prender();

	esperar(i);

	led1_apagar();
	led2_apagar();
	led3_apagar();
}

void leds_prender(char c) {

	led1_apagar();
	led2_apagar();
	led3_apagar();

	switch(c)
	{
		case 0:
			break;
		case 1:
			led1_prender();
			break;
		case 2:
			led2_prender();			
			break;
		case 3:
			led1_prender();	
			led2_prender();			
			break;
		case 4:
			led3_prender();	
			break;
		case 5:
			led3_prender();
			led1_prender();		
			break;
		case 6:
			led3_prender();	
			led2_prender();	
			break;
		case 7:
			led1_prender();	
			led2_prender();	
			led3_prender();	
			break;
		default:
			led2_prender();
			break;
		
	}

	unsigned long i =50000;
	esperar(i);
	led1_apagar();
	led2_apagar();
	led3_apagar();
}


