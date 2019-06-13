#include "utils.h"
#include "serial.h"
#include "motor.h"
#include <stdlib.h>
#include <util/delay.h>
#include <string.h>

char *mensajeee;

void modem_init(){

    //IP del modem 192.168.4.1

       /* serial_put_str("AT+CWMODE=2\r\n"); //solo AP
        mensajeee = (char *) serial_get_str();*/

        serial_put_str("AT+CIPMUX=1\r\n"); //MULTIPLES CONEXIONES
        mensajeee = (char *) serial_get_str();

		/*serial_put_str("AT+CWSAP=\"TANQUE\",\"\",6,0\r\n"); //Configurar la red
        mensajeee = (char *) serial_get_str();*/

		serial_put_str("AT+CIPSERVER=1,100\r\n"); //Abre el servidor en el puerto 100
     
}

char get_comando(){

	char l = serial_get_char();
    while((l != ':')){
		l = serial_get_char();
	};

    char res = serial_get_char();

    return res;        
    
}

int main(void)
{

	char comando='0';
	serial_init();
	modem_init();
	led_init();   
    motor_init();

	while(1){ 

        comando=get_comando();
        

            //Izquierda Derecha Avanzar Atras Laser Parar
			//Usamos WASD para adelante-izquierda-atras-derecha
            
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

                case 'l':case 'L':
                    //Disparar el laser
                    parpadeo_2(2);
                    break;
            
            } //switch       

	}//cierra while
}//cierra main

	
