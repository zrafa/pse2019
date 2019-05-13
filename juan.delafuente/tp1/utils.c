
/* Enciende y apaga un led conectado al puerto B bit 5 de un atmega328 */

/* 
 * El puerto B de un atmega328 tiene los bits 0-5 mapeados a los 
 * pines 8-13 de arduino 
 */


/* mascara para el led en el arduino pro mini */
#define BOTON (0x04)    /* 0b00000100 */
#define PARPADEO (0x38) /* 0b00111000 */
/* puertos de E/S */
extern volatile unsigned char * puerto_b;
extern volatile unsigned char * ddr_b;
extern volatile unsigned char * pin_b;



/* 
 * Configuración: Establecer el 5to bit del puerto B como entrada
 *
 * 	Poner en '0' el 5to bit de la dirección 0x24, que 
 * 	es el la dirección del registro de control
 *	(direccion de los datos) del puerto B (DDRB - Data Direction Register).
 *      El 5to bit define la entrada o salida del
 * 	pin del atmega328p que tiene conectado un led en una board arduino
 */

void esperar(){
	volatile unsigned long i;
	/* delay de 1 segundo */
	for (i=0; i<450000; i++);
}

void leds_prender() 
{
        *puerto_b = *puerto_b | PARPADEO;
}
void init()
{
	/*Por seguridad apagamos los pull-ups antes de modificar el ddr*/
        *puerto_b = *puerto_b & (~BOTON);
        //*puerto_b = *puerto_b & (0b00000000);
	/*Apagamos el 5to bit para usar el boton como entrada*/
	*(ddr_b) = *(ddr_b) & (~BOTON);
	/*Encendemos los bits 2do,3er y 4to para hacer salida hacia los leds*/
	//*(ddr_b) = (*ddr_b) & (0b11111011);
	*(ddr_b) = (*ddr_b) | (PARPADEO);
	/*Volvemos a encender el valor de puerto b*/
	*puerto_b |= BOTON;
	//*puerto_b |= 0b00000100;
	while ((*pin_b)&BOTON){
	
	}
	//leds_prender();
        //*puerto_b |= BOTON;
}



void leds_apagar() 
{
        *puerto_b = *puerto_b & (~PARPADEO);
}

/*Suma binaria simple*/
void incremento_binario(volatile unsigned char* a) 
{
	volatile unsigned char c; //carry
	volatile unsigned char b=0x01;
	if (*a != 0x07){
		do {
			//encuentro el carry
			c = (*a & b) << 1;
			/*Calculamos el incremento*/
			*a ^=b;
			b=c;
		}while (c != 0); 
	}else{
		*a=0x00;
	}
}

void btn_verificar(volatile unsigned char* modo){
	*modo = ((*pin_b) & BOTON); 		
}

void leds_contador(volatile unsigned char mascara){
	/*por seguridad bajamos esos bits*/
	*puerto_b = *puerto_b & (~PARPADEO);
	/*levantamos los bits del puerto*/
	*puerto_b = *puerto_b | mascara;

}
