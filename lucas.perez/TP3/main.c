#include "utils.h"
#include "serial.h"
#include <stdlib.h>

int main(void)
{
    char rcvChar = 0;
    char rdm = 0;

    led_init();
    serial_init();

    while (1)
    {
        if (leer_boton() == 0)
        {
            rdm = rand() % 8;
            serial_put_char(rdm);
        }
        /* Wait for an incoming character. */
        if (serial_recibido())
        {
            led_apagar();
            rcvChar = serial_get_char();
            leds_prender(rcvChar);
            // esperar();
        }
    }

    return 0;
}
