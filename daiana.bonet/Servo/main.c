/******************************************************************************

servo motors with AVR Microcontrollers.

Servo Motor: SG90
Servo Control PIN (orange): To OC1A PIN
Crystal: 16MHz


*******************************************************************************/
#include "pwm1.h"
#include <util/delay.h>
//Simple Wait Function
void Wait()
{
   uint8_t i;
   for(i=0;i<50;i++)
   {
      _delay_loop_2(0);
      _delay_loop_2(0);
      _delay_loop_2(0);
   }

}
void main()
{
   //Inicializa tope y prescalar
   pwm_init(0x1387,0x03);
   while(1){
      set_ocr1a(0x2BC); // -90 grados
      Wait();

      set_ocr1a(0x17C); // 0 grados
      Wait();

      set_ocr1a(0x8C); // 90 grados
      Wait();

   }
}
