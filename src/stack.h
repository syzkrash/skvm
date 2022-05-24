#ifndef STACK_H
#define STACK_H

#include "value.h"
#include <stdbool.h>
#include <stdint.h>

typedef uint8_t stack_ptr;
#define STACK_SIZE UINT8_MAX

struct VM;

// stack represents a singular stack (all stacks have a constant size)
struct stack {
	struct VM* vm;
	// end ALWAYS points at the element AFTER the last element
	stack_ptr end;
	// values points to the array of the stack elements
	struct value values[STACK_SIZE];
};

// stack_push copies adds a value to the end of this stack
void stack_push(struct stack*, struct value*);
// stack_pop removes the last value from this stack and returns it
struct value stack_pop(struct stack*);

typedef uint16_t program_ptr;
typedef uint8_t  callstack_ptr;
#define CALLSTACK_SIZE UINT8_MAX



struct call {
	_Bool label;
	program_ptr addr;
};

// callstack represents a stack of function return addresses
struct callstack {
	struct VM* vm;
	callstack_ptr end;
	struct call calls[CALLSTACK_SIZE];
};

// callstack_push adds an address to the end of this callstack.
void callstack_push(struct callstack*, _Bool, program_ptr);
// callstack_pop removes the last address from this callstack and returns it
program_ptr callstack_pop(struct callstack*);

#endif // STACK_H
