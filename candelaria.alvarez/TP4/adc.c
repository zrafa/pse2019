#include <avr/io.h>
#include <stdlib.h>

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
volatile adc_t *adc = (adc_t *) (0x78);




void adc_init() 
{
	/* 
		Registro ADMUX 
		Voltaje interno: bit 6 y 7 en 1. 
		Ajuste a derecha : bit 5 en 0.
		Entrada análoga: bit [0-3]. Por defecto es 000
	*/

	adc->admux = 0xC0; /* 1100 0000 */
	/* 
		Registro ADCSRA 
		Habilitar/encender conversor ADC: bit 7 en 1.
		Seleccionar preescalar: bits [0-2]
		Por defecto el prescalar es de 128 bits. 
	*/
	
	adc->adcsra = adc->adcsra | 0x80; /* 1000 0000 Habilita ADC*/
	adc->adcsra = adc->adcsra | 0x07; /* 0000 0111 Prescalar 128 */
}

int adc_get(char adc_input)
{
	int valor_leido;
	/* 
		Registro ADMUX 
		Entrada análoga: bit [0-3]. Se setea con adc_input
	*/

	adc->admux = adc->admux | adc_input;

	/* 
		Registro ADCSRA 
		Iniciar conversion ADC: bit 6 ADSC en 1.
		Mientras dura la conversión, ADSC es 1
	*/

	adc->adcsra = adc->adcsra | 0x40; /* 0100 0000*/

	/* Ejecuta hasta que ADSC es 0, significa fin de conversión */
	while((adc->adcsra & 0x40)!=0);

	/* Lee primero el registro LOW y luego HIGH, desplazado al byte mas significativo*/
	valor_leido = adc->adcl;
	valor_leido = (adc->adch << 8) + valor_leido;

	return valor_leido;
}

