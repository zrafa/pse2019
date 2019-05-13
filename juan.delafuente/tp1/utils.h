
/* Enciende y apaga un led conectado al puerto B bit 5 de un atmega328 */

/* 
 * El puerto B de un atmega328 tiene los bits 0-5 mapeados a los 
 * pines 8-13 de arduino 
 */

#ifndef _UTILS_H
#define _UTILS_H

/* mascara para el led en el arduino pro mini */
#define BOTON (0x04) /* 0b00000100 */

/* puertos de E/S */
volatile unsigned char * puerto_b = (unsigned char *) 0x25; /* direccion de PORTB: SALIDA */
volatile unsigned char * ddr_b = (unsigned char *) 0x24; /* direccion de DDR B (registro de control) */
volatile unsigned char * pin_b = (unsigned char *) 0x23; /* direccion PIN B (registro de datos)*/

void esperar();
void init();
void leds_prender();
void leds_apagar();
void incremento_binario(volatile unsigned char *);
void btn_verificar(volatile unsigned char *);
void leds_contador(volatile unsigned char);
#endif	/* _UTILS_H */
