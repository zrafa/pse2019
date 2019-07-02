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
unsigned int valor_actual=380;

#define INIT_TCCR1A 0xA2  /*0b10100010*/
#define INIT_TCCR1B 0x18  /*0b00011000*/
#define PB_1 0x02         /*0b00000010*/
#define PASO 5
#define TOPE_IZQ 700
#define TOPE_DER 140

volatile unsigned char *ddr_b2 = (unsigned char *)0x24;    /* direccion de DDR B (registro de control) */

void set_ocr1a(unsigned int val)
{
    pwm->pwm_ocrah= (val >> 8);
    pwm->pwm_ocral= val;
}

void pwm_init(unsigned int tope, char preescalar)
{
    pwm->pwm_tccra = (unsigned char) INIT_TCCR1A;
    pwm->pwm_tccrb = (unsigned char) INIT_TCCR1B | (preescalar & 7);
    pwm->pwm_icrh = (tope >> 8);
    pwm->pwm_icrl = tope;
    *(ddr_b2) = (*(ddr_b2) | (PB_1)); /* Se activa el  PB1 como salida */
    set_ocr1a(380); //Lleva al grado 0
}

//-90 grados es 700 en pwm
//+90 grados es 140 en pwm
//Estos valores se toman como topes maximos
void servo_izquierda(){

    if(valor_actual+PASO<=TOPE_IZQ){
        valor_actual+=PASO;
        set_ocr1a(valor_actual);
    }
               
}

void servo_derecha(){
    if(valor_actual-PASO>=TOPE_DER){
        valor_actual-=PASO;
        set_ocr1a(valor_actual);
    }
}


