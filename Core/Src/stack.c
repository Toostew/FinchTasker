/*
 * stack.c
 *
 *  Created on: 22 Jul 2026
 *      Author: tooka
 */

#include "main.h" //master header file


//this function switches from Main Stack Pointer to Process Stack Pointer
//ARM's core has two physical stack pointers. MSP is used by exception/interrupt handlers
//(and by everything, before a scheduler exists) - this is fixed, not task-specific.
//PSP is for our own tasks - whichever task is currently running uses PSP as its active stack.
//we need to provide a region of memory, and provide the location of the topmost address
//During task execution, PSP holds the address one word past the last valid stack element
//(since ARM stacks grow downward, the initial SP points just past the array's top end)
//This region of memory is part of a larger whole, and is usually part of a Task Control block
//this region of memory will store everything local to the task like variables, constants, etc.
//During a context switch, the CPU will automatically push certain Register states into this region of memory. Keep in mind
//that there is no "special region" to store it within this region, they load the values to wherever the stack pointer was pointing within this stack region
//Each task gets its own separate stack region so its local data never collides
//with another task's stack, or with the kernel/handler stack (MSP).
//I say "certain" registers, it is not enough. We need to manually push other registers ourselves

//understand byte alignment: When you specify a variable to be, say, of 8, 16, 32, or 64 bits (1,2,4,8 bytes respectively),
//the compiler enforces memory allignment such that the address of the given variable is always divisible by it's size in bytes.
//so, an 8 bit and 16 bit value (1 and 2 bytes), the 8 bit value can be placed at any address (since any address is divisible by 1)
//but the 16 bit value (2 bytes) will only be placed on addresses that are divisible by 2.
//so an 8 bit value could exist on addresses 0x00000001, 0x00000002, 0x00000003.. so on
//but a 16 bit value can only exist on 0x00000002, 0x00000004, ... so on
//this applies to the higher bit numbers
//32 bit numbers are alligned to 4-divisible addresses, so 0x00000004, 0x00000008, 0x0000000C.. so on
//64 bit number are alligned to 8-divisible addresses, like 0x00000008, 0x00000010, 0x00000018.. so on

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


int assemblyAdd(int a, int b){
	int value;

	/*
 __asm__ volatile (
    " ASSEMBLY CODE ZONE "   // Raw Assembly goes here, %x are positional placeholders
    : OUTPUT OPERANDS ZONE   // Map C variables you want to WRITE to
    : INPUT OPERANDS ZONE    // Map C variables you want to READ from
    : CLOBBER ZONE           // Tell the compiler which registers you modified (optional)
	);

	  */



	__asm__ volatile (
			"ADD %0, %1, %2" //ADD 0(value), 1(a), 2(b)  %0, %1, %2 are placeholders that are evaluated in order
			: "=r" (value) //the characters inside "" like "=r" are called constraints, and do some small operations or conditions
			  //all output must have "=". and "r" is a contraint to use a general-purpose register r0-r12
			: "r"  	(a), // bind the value of a to the 2nd operand
			  "r"	(b) //bind the value of b to the 3rd operand; for more info look up GCC Extensions

	);

	return value;
}

//empty for test
void taskOne(void){
	for(;;){}
}
//empty for test
void taskTwo(void){
	  SCB->ICSR |= (1 << 28); //turn on PENSVSET, which sets the pendSV interrupt to PENDING, waiting to be serviced
	  while(1);
}












