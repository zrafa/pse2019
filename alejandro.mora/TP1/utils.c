
#define BOTON (0x08) /* 0b1000  */
#define LED_3 (0x04) /* 0b100   */
#define LED_2 (0x02) /* 0b10    */
#define LED_1 (0x01) /* 0b1     */

/* puertos de E/S */
extern volatile unsigned char * puerto_b;
extern volatile unsigned char * ddr_b;
extern volatile unsigned char * pin_b;

unsigned long leds[3]={LED_1,LED_2,LED_3};

int binario[10];


void led_init()
{
	/*LEDs son pines de salida*/
	int led;
	for (led = 0; led < 3; led = led + 1){
		*ddr_b = *ddr_b | leds[led];
	}
	
	/*Apagar todo*/
	for (led = 0; led < 3; led = led + 1){
		*puerto_b = *puerto_b & (~leds[led]);
	}

	/*pin de BOTON es entrada*/
	*(ddr_b) = *(ddr_b) & (~BOTON);

	/* resistencia PULL-UP activada*/
	*puerto_b = *puerto_b | (BOTON);

	//Inicia en modo O
	*pin_b = *pin_b & (~BOTON);
	//*pin_b = *pin_b | (BOTON);
	
}

/* by cande*/
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



/* Enciende o Apaga un led, poniendo en HIGH/LOW el bit correspondiente del puerto_b 
/* led: numero de led
/* estado: 1 (encender) 0 (apagar)
/* leds: Array de LED */
void set_led(int led, int estado, unsigned long leds[]){
	if (estado == 1){//encender 
		*puerto_b = *puerto_b | leds[led-1];
	}else{//apagar
		*puerto_b = *puerto_b & (~leds[led-1]);
	}
}


void modo_0() {

	volatile unsigned long i;

	i = 500000;
	set_led(1,1,leds);
	set_led(2,1,leds);
	set_led(3,1,leds);
	esperar(i);

	set_led(1,0,leds);
	set_led(2,0,leds);
	set_led(3,0,leds);
}


/* dado un decimal entero, retorna un arreglo con el equivalente en binario*/
int* decimal_a_binario(int numero){
	
	/*Mejorar esta parte*/
	binario[0]=0;
	binario[1]=0;
	binario[2]=0;
	
	int i = 0;
	do{
	   binario[i] = numero%2;
	   numero = numero/2;
	   i++;
	}while (numero != 0);
	
	return binario;

}

void modo_1(){
	int i;
	int* valor;
	
	/* generar secuencia de 1 a 7 */
	for (i=0;i<=7;i++){
		valor = decimal_a_binario(i); /* convertir decimal a binario*/
		/*setear leds con valores correspondientes*/
		set_led(1,valor[0],leds);
		set_led(2,valor[1],leds);
		set_led(3,valor[2],leds);
		esperar(500000);
	}
	set_led(1,0,leds);
	set_led(2,0,leds);
	set_led(3,0,leds);

}
