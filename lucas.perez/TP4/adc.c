#include <avr/io.h> /* para los tipos de datos uint8_t */

typedef struct
{
    uint8_t adcl;
    uint8_t adch;
    uint8_t adcsra; /* ADC Control and Status Register A */
    uint8_t adcsrb;
    uint8_t admux; /* ADC Multiplexer Selection Register */
    uint8_t reserved;
    uint8_t didr0;
} volatile adc_t;

/* puntero a la estructura de los registros del periferico */
volatile adc_t *adc = (adc_t *)(0x78);

#define INIT_ADMUX (0xc0)  /*0b11000000*/
#define INIT_ADCSRA (0x87) /*0b10000111*/
#define ADSC_BIT (0x40)    /*0b01000000*/

// Establecer los registros de control para usar la referencia
// interna y habilitar el periférico
void adc_init(void)
{
    /* Configura registros ADMUX y ADCSRA para utilizar el
        voltage de referencia interno y encender (habilitar) el periférico */
    adc->admux = (unsigned char)(INIT_ADMUX);
    adc->adcsra = (unsigned char)(INIT_ADCSRA);
}

// debería entrar por parameto el pin en el que está conectado el sensor para
// setear el multiplexor en el pin qe se usará
int adc_get(char mux)
{
    adc->admux = ((INIT_ADMUX) | mux);
    // adc->admux = ((INIT_ADMUX) | 0b00000001);
    int val;
    adc->adcsra |= ADSC_BIT;
    while (((adc->adcsra) & (ADSC_BIT))) //Hay que esperar a que ADSC_BIT sea cero para leer el valor.
        ;
    /* IMPORTANTE: hay que leer el registro L antes del H !!! */
    val = (adc->adcl);
    val = (adc->adch << 8) + val;
    return val;
}