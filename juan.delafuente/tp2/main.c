/**********************************************************************
 *
 * Filename:    main.c
 *
 * Description: The main program file the serial driver example.
 *
 **********************************************************************/

#include "serial.h"


int main(void)
{
    char rcvChar = 0;

    /* Configure the UART for the serial driver. */
    serial_init();
    // Mensaje inicial de validacion
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
        rcvChar = serial_get_char();
        /* Echo the character back along with a carriage return and line feed. */
        serial_put_char(rcvChar);
        serial_put_char('\r');
        serial_put_char('\n');
    }
    // Mensaje de validacion de salida
    serial_put_char('S');
    serial_put_char('a');
    serial_put_char('l');
    serial_put_char('i');
    return 0;
}
