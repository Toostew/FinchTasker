/*
 * debugHelp.c
 *
 *  Created on: 24 Jul 2026
 *      Author: tooka
 */
#include "main.h"

//config to configure pin PB1 as GPIO out
void blinkConfig(){

	RCC->AHB2ENR |= (1 << 1); //enable AHB2 for GPIOB
	GPIOB->MODER &= ~(0b11 << 2); //2 bit region
	GPIOB->MODER |= (1 << 2); //set mode to GP output
}

void setResetBlink(int setReset){
	if(setReset == 0){
		GPIOB->BSRR |= (1 << 17); // reset blink
	} else {
		GPIOB->BSRR |= (1 << 1); //set blink
	}
}
