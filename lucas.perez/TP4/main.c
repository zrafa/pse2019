#include "utils.h"
#include "serial.h"
#include "adc.h"

int main(void)
{
    int adc_val = 0;
    char c = 0;
    int ajuste = 128; /* by cande alvarez */
    
    led_init();
    serial_init();
    adc_init();
    serial_put_char('7');
    esperar();
    serial_put_char('0');

    while (1)
    {
        if (serial_recibido()){
            c = serial_get_char();
            leds_prender(c);
        }

        if(leer_boton() == 0){
            adc_val = adc_get(0);
            c = (adc_val/ajuste)%10; /* by cande alvarez */
            serial_put_char(c);
            // serial_put_int(adc_val, 4);
            esperar();
        }
    }

    return 0;
}
