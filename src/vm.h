#ifndef VM_H
#define VM_H

#include "stack.h"
#include "opcodes.h"
#include <stdio.h>

#define memory_ptr  uint16_t
#define MEMORY_SIZE UINT16_MAX

// VM represents the state of one skvm virtual machine
struct VM {
	// stack contains the VM's value stack
	struct stack stack;
	// callstack contains the return address tack
	struct callstack callstack;
	// memory is the memory allocated to the machine (it's size is always 0xFFFF)
	uint8_t memory[MEMORY_SIZE];
	// program is any source of bytes to read the opcodes from
	FILE* program;
};

// vm_new allocates a new and completely empty virtual machine
struct VM* vm_new(FILE*);
// vm_next performs one tick on the virtual machine. This will read whatever
//         the next section present in the source stream and act on it. This
//         returns 0 if the tick was successful, anything else will be an
//         ERR_VM_... value.
uint8_t vm_next(struct VM*);


#endif // VM_H
