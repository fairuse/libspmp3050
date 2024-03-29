#include <stdint.h>
#include "../spmp3050/spmp3050.h"

extern inline void GPIO_Init(){
	GPIO_DISABLE = 0x00;
}

void GPIO_SetPower(int val){
	GPIO_A_DIR |= 0x02;
	if(val)
		GPIO_A_OUT |= 0x02;
	else
		GPIO_A_OUT &= ~0x02;
}