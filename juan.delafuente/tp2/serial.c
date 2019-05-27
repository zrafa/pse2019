#include <avr/io.h> /* para los tipos de datos uint8_t */

typedef struct
{
    uint8_t status_control_a;    /* ucsr0a USART Control and Status A */
    uint8_t status_control_b;    /* ucsr0a USART Control and Status B */
    uint8_t status_control_c;    /* ucsr0a USART Control and Status C */
    uint8_t reserved;            /* offset sin utilizar */
    uint8_t baud_rate_l;         /* ubrr0l baud rate low */
    uint8_t baud_rate_h;         /* ubrr0h baud rate high */
    uint8_t data_es;             /* udr0 i/o data */

} volatile uart_t;

/* puntero a la estructura de los registros del periferico */
uart_t *puerto_serial = (uart_t *) (0xc0);

#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU/(USART_BAUDRATE*16UL)))-1)
/* Bit para activar recepcion */
#define EN_RX 0x80
/* Bit para activar transmision */
#define EN_TX 0x20
/* Mascara de inicializacion: 8bits, 1stop, sin paridad, async */
#define INIT 0x06
/* Mascara para enviar y recibir */
#define EN_RX_TX 0x18

void serial_init() {
    /* Rutina de inicializacion */
    /*Set baud rate */ /* Configurar los registros High y Low con BAUD_PRESCALE */
    puerto_serial->baud_rate_h = (unsigned char)(BAUD_PRESCALE>>8);
    puerto_serial->baud_rate_l = (unsigned char)BAUD_PRESCALE;
    /* Configurar un frame de 8bits, con un bit de paridad y bit de stop */
    puerto_serial->status_control_c = (unsigned char)(INIT);
    /*Enable receiver and transmitter *//* Activar la recepcion y transmision */
    puerto_serial->status_control_b = (unsigned char)(EN_RX_TX);

}

char serial_recibido(void)
{	
    return (!((puerto_serial->status_control_a) & (EN_TX)));
}

/* enviar un byte a traves del del dispositivo inicializado */
void serial_put_char(char outputChar)
{
    /* Wait until the transmitter is ready for the next character. */
    // while (!((puerto_serial->status_control_a) & (0x20)))
    while (!((puerto_serial->status_control_a) & (EN_TX)))
        ;

    /* Send the character via the serial port. */
    puerto_serial->data_es = (outputChar);
}


char serial_get_char(void)
{
    /* Wait for the next character to arrive. */
    while ( ! ( puerto_serial->status_control_a & EN_RX));
    return (char) (puerto_serial->data_es);
}
