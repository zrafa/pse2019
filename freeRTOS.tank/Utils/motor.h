/**********************************************************************
 *
 * Filename:    motor.h
 * 
 * API para la aplicacion embebida 
 *
 * META : ocultar el hardware a la aplicacion 
 *
 **********************************************************************/

#ifndef _MOTOR_H
#define _MOTOR_H


void motor_init(void);
void adelante(void);
void atras(void);
void parar(void);
void derecha(void);
void izquierda(void);
#endif /* _MOTOR_H */
