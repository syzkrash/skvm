#ifndef STACK_H
#define STACK_H

#include "value.h"
#include <stdint.h>

#define stack_ptr  uint8_t
#define STACK_SIZE UINT8_MAX

// stack represents a singular stack (all stacks have a constant size)
struct stack {
	// end ALWAYS points at the element AFTER the last element
	stack_ptr end;
	// values points to the array of the stack elements
	struct value values[STACK_SIZE];
};

// stack_push adds a value to the end of this stack
void stack_push(struct stack, struct value);
// stack_pop removes the last value from this stack and returns it
struct value stack_pop(struct stack);

#define program_ptr    uint16_t
#define callstack_ptr  uint8_t
#define CALLSTACK_SIZE UINT8_MAX

// callstack represents a stack of function return addresses
struct callstack {
	callstack_ptr end;
	program_ptr calls[CALLSTACK_SIZE];
};

// callstack_push adds an address to the end of this callstack.
void callstack_push(struct callstack, program_ptr);
// callstack_pop removes the last address from this callstack and returns it
program_ptr callstack_pop(struct callstack);

#endif // STACK_H
