
/* macros útiles para consultar si se presionó el boton y para inicializar
 * el estado del port_b respectivamente
 */
#define BOTON (0x04)      /* 0b00000100 */
#define INIT_VALUE (0x38) /* 0b00111000 */

/* direcciones del registros de control y datos de interfaz b*/
volatile unsigned char *puerto_b = (unsigned char *)0x25; /* direccion de PORTB: SALIDA */
volatile unsigned char *ddr_b = (unsigned char *)0x24;    /* direccion de DDR B (reg de control) */
volatile unsigned char *pin_b = (unsigned char *)0x23;

void esperar()
{
        volatile unsigned long i;

        /* delay manual */
        for (i = 0; i < 300000; i++)
                ;
}

/* inicializar los registro de control y datos de la interfaz b */
void led_init()
{
        *(ddr_b) = *(ddr_b) | (INIT_VALUE) & (~BOTON);
        *puerto_b = *puerto_b & (~INIT_VALUE) | BOTON;
}

void contador(char value)
{
        value = value << 3;
        if (value == 0)
        {
                *puerto_b = *puerto_b & (~INIT_VALUE);
        }
        else
        {
                *puerto_b = *puerto_b & (~INIT_VALUE) | value;
        }
}

void led_prender()
{
        *puerto_b = *puerto_b | INIT_VALUE;
}

void led_apagar()
{
        *puerto_b = *puerto_b & (~INIT_VALUE);
}

char leer_boton()
{
        char valor = *pin_b & BOTON;
        return valor;
}
