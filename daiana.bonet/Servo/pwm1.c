#include <avr/io.h> /* para los tipos de datos uint8_t */

typedef struct
{
    uint8_t pwm_tccra; /* Registro de control A de PWM */
    uint8_t pwm_tccrb; /* Registro de control B de PWM */
    uint8_t pwm_tccrc; /* Registro de control C de PWM */
    uint8_t pwm_reserved;
    uint8_t pwm_tcntl;
    uint8_t pwm_tcnth;
    uint8_t pwm_icrl;
    uint8_t pwm_icrh;
    uint8_t pwm_ocral;
    uint8_t pwm_ocrah;
    uint8_t pwm_ocrbl;
    uint8_t pwm_ocrbh;

} volatile pwm1_t;

volatile pwm1_t *pwm = (pwm1_t *)(0x80);

#define INIT_TCCR1A 0xA2  /*0b10100010*/
#define INIT_TCCR1B 0x18  /*0b00011000*/
#define PB_1 0x02         /*0b00000010*/

volatile unsigned char *ddr_b = (unsigned char *)0x24;    /* direccion de DDR B (registro de control) */

void pwm_init(unsigned int tope, char preescalar)
{
    pwm->pwm_tccra = (unsigned char) INIT_TCCR1A;
    pwm->pwm_tccrb = (unsigned char) INIT_TCCR1B | (preescalar & 7);
    pwm->pwm_icrh = (tope >> 8);
    pwm->pwm_icrl = tope;
    *(ddr_b) = (*(ddr_b) | (PB_1)); /* Se activa el  PB1 como salida */
}

void set_ocr1a(unsigned int val)
{
    pwm->pwm_ocrah= (val >> 8);
    pwm->pwm_ocral= val;
}
