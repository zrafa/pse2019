#include "utils.h"
#include "serial.h"
#include "motor.h"
#include "modem.h"
#include "pwm1.h"
#include <stdlib.h>
#include <util/delay.h>
#include <string.h>

int main(void)
{

	char comando='0';
    motor_init();	
    serial_init();
	modem_init();
	led_init();  
	led3_prender(); 
    motor_init();
    pwm_init(0x1387,0x03);
    
	while(1){ 

        //comando=get_comando();
        comando=modem_get_comando();

            //Izquierda Derecha Avanzar Atras Laser Parar
			//Usamos WASD para adelante-izquierda-atras-derecha
			
			//SERVO: j es izq, l es derecha
            
            switch(comando){
                case 'a':case 'A':
                    //Frenar rueda izquierda y avanzar rueda derecha
                    izquierda();
                    break;

                case 'd':case 'D':
                    //Frenar rueda derecha y avanzar rueda izquierda
                    derecha();
                    break;

                case 'w':case 'W':
                    //Avanzar ambas ruedas
                    adelante();
                    break;

                case 'p':case 'P':
                    //Parar ambas ruedas
                   parar();
                    break;
                    
                case 's':case 'S':
                    //Atras
                   atras();
                    break;
                   
                case 'k':case 'K':
                    //Disparar el laser
                    laser_disparar();
                    led3_apagar();
                    _delay_ms(500);
                    led3_prender();
                    
                    break;                    

                case 'j':case 'J':
                    
                    servo_izquierda();
                    break;   
                    
                case 'l':case 'L':
                    
                    servo_derecha();
                    break;                                      
            
            } //switch       

	}//cierra while
}//cierra main

	
