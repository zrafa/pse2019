#include <avr/io.h> /* para los tipos de datos uint8_t */

/* Completar la estructura de datos para que se superponga a los registros
   del periferico de hardware del USART del atmega328, segun sugerido
   en el apunte */

typedef struct
{
    uint8_t status_control_a; /* ucsr0a USART Control and Status A */
    uint8_t status_control_b; /* ucsr0b */
    uint8_t status_control_c; /* ucsr0c */
    uint8_t _reserved;
    uint8_t baud_rate_l; /* ubrr0l baud rate low */
    uint8_t baud_rate_h; /* ubrr0h baud rate high */
    uint8_t data_es;     /* udr0 i/o data */

} volatile uart_t;

/* puntero a la estructura de los registros del periferico */
uart_t *puerto_serial = (uart_t *)(0xc0);

#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)
#define INIT (0x06)     /*0b00000110*/
#define EN_RX_TX (0x18) /*0b00011000*/

#define EN_RX (0x80) /*0b10000000*/
#define EN_TX (0x40) /*0b01000000*/
#define UDREn (0x20) /*0b00100000*/

void serial_init()
{
    /* Configurar los registros High y Low con BAUD_PRESCALE */
    puerto_serial->baud_rate_l = (unsigned char)(BAUD_PRESCALE);
    puerto_serial->baud_rate_h = (unsigned char)(BAUD_PRESCALE >> 8);

    /* Configurar un frame de 8bits, con un bit de paridad y bit de stop */
    puerto_serial->status_control_c = (unsigned char)INIT;

    /* Activar la recepcion y transmicion */
    puerto_serial->status_control_b = (unsigned char)(EN_RX_TX);
}

/* enviar un byte a traves del del dispositivo inicializado */
void serial_put_char(char outputChar)
{
    /* Wait until the transmitter is ready for the next character. */
    /* Se debe esperar verificando el bit UDREn del registro UCSRnA, 
    hasta que el buffer esté listo para recibir un dato a transmitir */
    while (!((puerto_serial->status_control_a) & (UDREn)))
        ;

    /* Send the character via the serial port. */
    /* (escribir el dato al registro de datos de E/S */
    puerto_serial->data_es = outputChar;
}

char serial_get_char(void)
{
    /* Wait for the next character to arrive. */
    /* Completar con E/S programada similar a serial_put_char pero
    utilizando el bit correcto */
    while (!((puerto_serial->status_control_a) & (EN_RX)))
        ;

    /* DEBE devolver el valor que se encuentra en el registro de datos de E/S */
    return (puerto_serial->data_es);
}

char serial_recibido(void)
{
    return ((puerto_serial->status_control_a) & (EN_RX));
}
