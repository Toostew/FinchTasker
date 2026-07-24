/*
 * stack.h
 *
 *  Created on: 22 Jul 2026
 *      Author: tooka
 */

#ifndef INC_STACK_H_
#define INC_STACK_H_

typedef struct {
	uint32_t * basePointer;
	uint32_t * topOfStackPointer;
} TransferControlBlock_def;


void psp_switch(uint32_t * taskStack, uint32_t sizeOfStack);
int assemblyAdd(int a, int b);


#endif /* INC_STACK_H_ */
