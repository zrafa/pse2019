/**********************************************************************
 *
 * Filename:    main.c
 *
 * Description: The main program file the serial UART driver example.
 *
 **********************************************************************/

#include "serial.h"
#include "utils.h"


int main(void)
{
    char numero = 0;

    /* Configure the UART for the serial driver. */
    serial_init();
    init();
    // Impresion de comienzo para verificacion
    // serial_put_char('s');
    // serial_put_char('t');
    // serial_put_char('a');
    // serial_put_char('r');
    // serial_put_char('t');
    // serial_put_char('\r');
    // serial_put_char('\n');

    while ( 1)
    {

    	if (serial_recibido()){
            prender_led_3();
            esperar();
            apagar_led_3();
            numero = serial_get_char();/*se recibe un valor del 0 al 7*/
        	leds_prender(numero);/*se representa imprime el numero recibido*/

    	};
    	if(btn_verificar()){
            prender_led_1();
            prender_led_2();
            prender_led_3()
            esperar();
            apagar_led_1();
            esperar();
            apagar_led_2();
            esperar();
            apagar_led_3();
            numero = '3';            /* numero 'aleatorio' */
    		serial_put_char(numero); /*se envia el numero*/
    	};

    }

    return 0;
}
