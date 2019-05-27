/* mascara para el boton externo */
#define BOTON (0x04) /* 0b00000100 */
#define LED_1 (0x08) /* 0b00001000 */
#define LED_2 (0x10) /* 0b00010000 */
#define LED_3 (0x20) /* 0b00100000 */

/* puertos de E/S */
extern volatile unsigned char * puerto_b;
extern volatile unsigned char * ddr_b;
extern volatile unsigned char * pin_b;


void esperar() {

    unsigned long i;
    /* delay manual para contar un segundo*/
    for (i=0; i<550000; i++);
}

/*
 * Configuración: Establecer el 5to bit del puerto B como entrada
 *
 * 	Poner en '0' el 5to bit de la dirección 0x24, que
 * 	es el la dirección del registro de control
 *	(direccion de los datos) del puerto B (DDRB - Data Direction Register).
 *      El 5to bit define la entrada o salida del
 * 	pin del atmega328p que tiene conectado un led en una board arduino
 */

void prender_led_1(void)
{
        *puerto_b = *puerto_b | LED_1;
}

void prender_led_2(void)
{
        *puerto_b = *puerto_b | LED_2;
}

void prender_led_3(void)
{
        *puerto_b = *puerto_b | LED_3;
}


void init(void)
{
		*puerto_b = *puerto_b & (~BOTON);
		*ddr_b = (*ddr_b) & (~BOTON);
		//	*ddr_b = (*ddr_b) & (~0b00000100);
		//	*ddr_b |=  (LEDS_EXT);/* Coloca '0' en el 5to bit del ddr_b y colocar '1' los bits 2do,3ro y 4to*/
		*puerto_b |= BOTON;

}

void apagar_led_1(void)
{
        *puerto_b = *puerto_b & (~LED_1);
}

void apagar_led_2(void)
{
        *puerto_b = *puerto_b & (~LED_2);
}

void apagar_led_3(void)
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

//funcion para verificar si se pulsa el boton
char btn_verificar(void){
	unsigned char aux = 0x00;
	aux = *pin_b & BOTON;
	return aux;
}

void leds_contador(char mascara){

	*puerto_b = *puerto_b & ~LED_1 & ~LED_2 & ~LED_3; //apagar todos los leds
 	*puerto_b = *puerto_b | mascara; 									//enciender solo los correspondendientes

}


void leds_prender(char numero){

	prender_led_1();
	prender_led_2();
	prender_led_3();
	apagar_led_1();
	apagar_led_2();
	apagar_led_3();

	switch (numero)
	{
					case 0:
									break;
					case 1:
									prender_led_1();
									break;
					case 2:
									prender_led_2();
									break;
					case 3:
									prender_led_1();
									prender_led_2();
									break;
					case 4:
									prender_led_3();
									break;
					case 5:
									prender_led_1();
									prender_led_3();
									break;
					case 6:
									prender_led_2();
									prender_led_3();
									break;
					case 7:
									prender_led_1();
									prender_led_2();
									prender_led_3();
									break;
					default:
									prender_led_3();
									break;

	}
}
