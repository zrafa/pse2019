
#include "utils.h"

int main(void)
{
	led_init(); 
	char modo = 0, click = 0;
    while (1) {
		click = hubo_click();
		if(click) { /*Cambia de Modo*/
			if(modo){
				modo = 0;
				modo_0();

			} else { 
				modo = 1;
				modo_1();
			}	
		}else {/*NO cambia de Modo*/
				
			if(modo){
				modo_1();
			} 
			else {
				modo_0();
			}
		}
	}
}


