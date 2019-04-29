
/* Enciende y apaga un led conectado al puerto B bit 5 de un atmega328 */

/* 
 * El puerto B de un atmega328 tiene los bits 0-5 mapeados a los 
 * pines 8-13 de arduino 
 */

#ifndef _UTILS_H
#define _UTILS_H

/* mascara para el led en el arduino pro mini */
#define LED_ROJO (0x20) /* 0b00100000 */

/* puertos de E/S */

volatile unsigned char * pin_b = (unsigned char *) 0x23;
volatile unsigned char * puerto_b = (unsigned char *) 0x25; /* direccion de PORTB: SALIDA */
volatile unsigned char * ddr_b = (unsigned char *) 0x24; /* direccion de DDR B (registro de control) */

char hubo_click();
void led_init();
void modo_0();
void modo_1();


#endif	/* _UTILS_H */
