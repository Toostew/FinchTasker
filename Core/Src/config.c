/*
 * config.c
 *
 *  Created on: 26 Jul 2026
 *      Author: tooka
 */
#include "main.h"

//config systick, does not fire
void systick_config(){

	SysTick->CTRL &= ~((1 << 2) | (1 << 1) | (1 << 0));
	SysTick->CTRL |= ((1 << 2) | (1 << 1)); //CLKSOURCE, TICKINT

	SysTick->LOAD = 16777214; //(period seconds - frequency) - 1, (10ms (0.01) x 170MHZ) - 1
	SysTick->VAL = 0; //read VAL once to reset VAL to 0
}


//toggles the systick
void systick_toggle(int i){
	if (i == 0){
		SysTick->CTRL &= ~(1 << 0);
	} else {
		SysTick->CTRL |= (1 << 0);
	}
}
