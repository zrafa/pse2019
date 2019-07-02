#include <avr/io.h>
#include <util/delay.h>               // for _delay_ms()



/* Motores usando portd del atmega328 */
#define MOTOR_DERECHO_A 0b10000000 // PD7 -> pin 7 placa
#define MOTOR_DERECHO_B 0b01000000 //PD6 -> pin 6 placa
#define MOTOR_IZQUIERDO_A 0b00100000 // PD5 -> pin 5 placa
#define MOTOR_IZQUIERDO_B 0b00010000 // PD4 -> pin 4 placa
#define TODOS 0b11110000

volatile unsigned char * puerto_d = (unsigned char *) 0x2B;
volatile unsigned char * ddr_d = (unsigned char *) 0x2A; /* direccion de DDR D */
const int tiempo = 100;


void parar(){
		*puerto_d = *puerto_d & (~TODOS);
}

/* MOTORES -> 1 en A y 0 en B*/
void adelante(){
		*puerto_d = *puerto_d | MOTOR_DERECHO_A | MOTOR_IZQUIERDO_A;
		*puerto_d = *puerto_d & (~MOTOR_DERECHO_B) & (~MOTOR_IZQUIERDO_B); 
		_delay_ms(tiempo);
		parar();

}

/* MOTORES -> 1 en B y 0 en A*/
void atras(){
		*puerto_d = *puerto_d | MOTOR_DERECHO_B | MOTOR_IZQUIERDO_B;
		*puerto_d = *puerto_d & (~MOTOR_DERECHO_A) & (~MOTOR_IZQUIERDO_A); 
		_delay_ms(tiempo); 
		parar();

}

void derecha(){
		*puerto_d = *puerto_d | MOTOR_DERECHO_B | MOTOR_IZQUIERDO_A;
		*puerto_d = *puerto_d & (~MOTOR_DERECHO_A) & (~MOTOR_IZQUIERDO_B); 
		_delay_ms(tiempo); 
		parar();
}

void izquierda(){
		*puerto_d = *puerto_d | MOTOR_DERECHO_A | MOTOR_IZQUIERDO_B;
		*puerto_d = *puerto_d & (~MOTOR_DERECHO_B) & (~MOTOR_IZQUIERDO_A); 
		_delay_ms(tiempo); 
		parar();
}

void motor_init(){
		*(ddr_d) = *(ddr_d) | TODOS;
		*puerto_d = *puerto_d & (~TODOS);
		adelante();
		_delay_ms(500);
		atras();
		_delay_ms(500);
}

