
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
void leds_prender(char c);
void esperar(long tope);
void led2_prender();
void led2_apagar();

void led1_prender();
void led1_apagar();

void led3_prender();
void led3_apagar();

void parpadeo_1(char t);
void parpadeo_2(char t);
void parpadeo_3(char t);

void laser_disparar();
#endif	/* _UTILS_H */
