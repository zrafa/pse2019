#include "serial.h"
#include <util/delay.h>               // for _delay_ms()

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

/*
* Si desde minicom se envia el mensaje "adelante"
* el modem recibe: "+IPD,0,8:adelante" 
* por lo que se consume la cadena hasta el caracter ':'
* Luego, el siguiente caracter a : indica el comando
* a ejecutar
*/

char modem_get_comando(){

	char l = serial_get_char();
    while((l != ':')){
		l = serial_get_char();
	};

    char res = serial_get_char();

    return res;           
}


