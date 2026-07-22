/*
 * stack.c
 *
 *  Created on: 22 Jul 2026
 *      Author: tooka
 */

#include "main.h" //master header file


//this function switches from Main Stack Pointer to Process Stack Pointer
//provide the beginning address of the stack already set to 512 elements (512 * 32 bits (4 bytes))
//CAUTION: at the current moment, this function WILL fail. this is because the function, which initially starts off
//in MSP, converts to PSP before the function can terminate. This will cause hardfaults that are not immediately obvious
void psp_switch(uint32_t * taskStack, uint32_t sizeOfStack){

	  //__get_CONTROL() function is provided by ARM to get the CONTROL register
	  uint32_t controlRegister = __get_CONTROL();

	  //calculate the top of the stack, it is the tip of the array, plus 1 (so technically, 1 element outside)
	  //
	  uint32_t topOfTask_Stack = ((uint32_t)(taskStack) + (sizeOfStack * sizeof(uint32_t)));

	  //another ARM function to set the location of top of stack of PSP
	  __set_PSP(topOfTask_Stack);

	  //set SPSEL active stack pointer selection to PSP (bit 1)
	  controlRegister |= (1 << 1);

	  //write the changes to the control register
	  __set_CONTROL(controlRegister);

	  // Instruction Synchronization Barrier (ISB) instruction. It flushes the processor's pipeline and
	  //fetch buffers, ensuring that all subsequent instructions are fetched from cache or memory after
	  //previous system changes take effect. In short, big config changes, invoke __ISB for safety
	  __ISB();
}
