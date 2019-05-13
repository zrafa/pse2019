/**********************************************************************
 *
 * Filename:    main.c
 * 
 * Description: The main program file the serial driver example.
 *
 **********************************************************************/

#include "utils.h"
#include "serial.h"

int main(void)
{
    char rcvChar = 0;
    char rdm = 0;

    led_init();
    serial_init();

    serial_put_char('s');
    serial_put_char('t');
    serial_put_char('a');
    serial_put_char('r');
    serial_put_char('t');
    serial_put_char('\r');
    serial_put_char('\n');

    while (rcvChar != 'q')
    {
        /* Wait for an incoming character. */
        if (serial_recibido())
        {
            rcvChar = serial_get_char();
            led_prender();
            esperar();
            led_apagar();
            serial_put_char(rcvChar);
            serial_put_char('\r');
            serial_put_char('\n');
        }
    }

    return 0;
}
