
/* mascara para leds arduino mini */
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
	/*Apagamos antes de cualquier cambio por seguridad*/
  *puerto_b = *puerto_b & (~LED_1);
	*puerto_b = *puerto_b & (~LED_2);
	*puerto_b = *puerto_b & (~LED_3);

	//Marcamos la entrada para el boton y que pines son de salida
	*(ddr_b) = *(ddr_b) & (~BOTON);
	*(ddr_b) = *(ddr_b) | (LED_1);
	*(ddr_b) = *(ddr_b) | (LED_2);
	*(ddr_b) = *(ddr_b) | (LED_3);

	//Activamos el pull-up para boton
	*puerto_b = *puerto_b | (BOTON);
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


//Sumador binario simple
void suma_bin(char* contador)
{
	unsigned char carry, aux;
	aux = 0x01;
	if(*contador != 0x07){
		do{
			//Calcular carry y shift left
			carry = (*contador & aux) << 1;
			//Calcular la suma
			*contador = *contador^aux;
			aux = carry;
		}while (carry != 0x00);
	}
	else{
		*contador = 0x00;
	}
}


void leds_rutina() {

	volatile unsigned long i;
	i = 440000;

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
