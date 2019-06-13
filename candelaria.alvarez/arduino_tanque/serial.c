#include <avr/io.h>
//#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    uint8_t status_control_a;    /* ucsr0a USART Control and Status A */

    uint8_t status_control_b; /* ucsr0b USART Control and Status B */
    uint8_t status_control_c; /* ucsr0c USART Control and Status C */
    uint8_t _reserved; /* espacio sin utilizar */
    uint8_t baud_rate_l; /* ubrr0l baud rate low */
    uint8_t baud_rate_h; /* ubrr0h baud rate high */

    uint8_t data_es;    /* udr0 i/o data */

} volatile uart_t;

/* puntero a la estructura de los registros del periferico */
volatile uart_t *puerto_serial = (uart_t *) (0xc0);

char cadena[4];


#define USART_BAUDRATE 115200
#define BAUD_PRESCALE (((F_CPU/(USART_BAUDRATE*16UL))))
#define INIT 0x06
#define EN_RX_TX 0x18
#define EN_TX 0x20
#define EN_RX 0x80


char serial_recibido(void)
{
	//Si devuelve 0 significa que no se recibió nada
	//Si devuelve 1 significa que hay un dato para leer

	/*long i;
	char res;
	for (i=0; i<50000; i++){
		res |= ((puerto_serial->status_control_a) & (EN_RX));
	}

	return res;*/
	
	return(((puerto_serial->status_control_a) & (EN_RX)));
}


void serial_init() {

	/* Configurar los registros High y Low con BAUD_PRESCALE */

	/*puerto_serial->baud_rate_h = (unsigned char) (BAUD_PRESCALE>>8);
	puerto_serial->baud_rate_l = (unsigned char) (BAUD_PRESCALE);*/


	puerto_serial->baud_rate_h = (unsigned char) 0;
	puerto_serial->baud_rate_l = (unsigned char) 8;
	/* Configurar un frame de 8bits, con un bit de paridad y bit de stop */
	puerto_serial->status_control_c = (unsigned char)(INIT);

	/* Activar la recepcion y transmision */
	puerto_serial->status_control_b = (unsigned char)(EN_RX_TX);

}


/* enviar un byte a traves del del dispositivo inicializado */
void serial_put_char (char outputChar)
{
    /* Wait until the transmitter is ready for the next character. */

    /* completar con E/S programada */
    /* Se debe esperar verificando el bit UDREn del registro UCSRnA,
       hasta que el buffer esté listo para recibir un dato a transmitir */

    // while ( /* completar con E/S programada */ )
    //     ;

	while(!((puerto_serial->status_control_a) & (EN_TX)));


    /* Send the character via the serial port. */
    /* (escribir el dato al registro de datos de E/S */

	puerto_serial->data_es = outputChar;
}


char serial_get_char(void)
{
    /* Wait for the next character to arrive. */
    /* Completar con E/S programada similar a serial_put_char pero
       utilizando el bit correcto */

    // while ( /* completar con E/S programada */ )
    //     ;
	while(!((puerto_serial->status_control_a) & (EN_RX)));
    // return /* DEBE devolver el valor que se encuentra en el registro de datos de E/S */
	return (puerto_serial->data_es);

}

void serial_put_str (char * mensaje)
{
	int i = 0;
	while (mensaje[i] != '\0') {
		serial_put_char(mensaje[i]);
		i++;
	};
}


/////

int serial_potencia (int base, int exponente){
	int i, res = 1;
	for(i=0;i<exponente;i++)
	{
		res *= base; 	
	}
	return res;
}

void serial_put_int (int valor, int cant_digitos){
	int divisor = serial_potencia(10,cant_digitos-1);
	int i;
	char resultado[10];
	
	for(i=0;i<cant_digitos;i++)
	{
		resultado[i] = valor/divisor + 48;
		valor = valor % divisor;
		divisor = divisor/10; 
	}

	resultado[i]='\0'; //Fin de cadena
	serial_put_str(resultado);
}

void serial_put_double (double valor){
//Asumimos que el valor es de 3 digitos, por ej 0.23
	//int divisor = serial_potencia(10,cant_digitos-1);
	int i, divisor = 100;
	int aux = valor * 100;
	char resultado[5];

	resultado[1]='.';

	for(i=0;i<4;i++)
	{
		if(i!=1)
		{
			resultado[i] = aux/divisor + 48;
			aux = aux % divisor;
			divisor = divisor/10; 
		}

	}

	resultado[i]='\0'; //Fin de cadena
	serial_put_str(resultado);
}



/////


char* serial_get_str(void)
{
	int i = 0;
	char l = serial_get_char();
    while((l != '\r') && (l != '\n') && (l != '\0')){
		cadena[i]=l;
		i++;
		l = serial_get_char();
	};
	cadena[i]='\0';/*agrega el fin de cadena*/
	return cadena;

}
