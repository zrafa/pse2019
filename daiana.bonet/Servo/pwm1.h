
#ifndef _PWM_H
#define _PWM_H

void pwm_init(unsigned int tope, char preescalar);
void set_ocr1a(unsigned int val);

#endif /* _PWM_H */
