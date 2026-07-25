/*
 * stack.h
 *
 *  Created on: 22 Jul 2026
 *      Author: tooka
 */

#ifndef INC_STACK_H_
#define INC_STACK_H_

typedef struct {
	uint32_t * stackPointer;
	uint32_t * basePointer;
	uint32_t * topOfStackPointer;
	uint32_t * taskFunction;
} TransferControlBlock_def;


void psp_switch(uint32_t * taskStack, uint32_t sizeOfStack);
int assemblyAdd(int a, int b);
void taskOne(void);
void taskTwo(void);


#endif /* INC_STACK_H_ */
