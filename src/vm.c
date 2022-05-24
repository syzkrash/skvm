#include "vm.h"
#include "errors.h"
#include <stdlib.h>

struct VM* vm_new(FILE* source)
{
	struct VM* vm = calloc(1, sizeof(struct VM));
	vm->program = source;
	vm->stack.vm = vm;
	vm->callstack.vm = vm;
	return vm;
}

// file-private definitions for vm_next
uint8_t vm_do_data(struct VM* vm);
uint8_t vm_do_text(struct VM* vm);
#warning TODO: implement vm_do_text

uint8_t vm_next(struct VM* vm)
{
	// EOF isn't an error here -- it's just used as an indicator to pass back up
	// the call chain
	if(feof(vm->program))
		return ERR_VM_EOF;
	uint8_t section = fgetc(vm->program);
	if(ferror(vm->program))
		return ERR_VM_BAD_READ;

	switch(section)
	{
	case SEC_DATA:
		return vm_do_data(vm);
	case SEC_TEXT:
		return vm_do_text(vm);
	case SEC_TERM:
		return ERR_VM_EOF;
	default:
		return ERR_VM_UNKNOWN_SEC;
	}
}

uint8_t vm_do_data(struct VM* vm)
{
	while(1) // infinite loop go brrr
	{
		memory_ptr size_top = fgetc(vm->program);
		if(ferror(vm->program))
			return ERR_VM_BAD_READ;
		memory_ptr size_bot = fgetc(vm->program);
		if(ferror(vm->program))
			return ERR_VM_BAD_READ;
		memory_ptr size = (size_top << 8) | size_bot;
		// return early if size is 0: it does not make sense, use so we use it as
		// an end-of-section marker
		if(size == 0) break;

		memory_ptr addr_top = fgetc(vm->program);
		if(ferror(vm->program))
			return ERR_VM_BAD_READ;
		memory_ptr addr_bot = fgetc(vm->program);
		if(ferror(vm->program))
			return ERR_VM_BAD_READ;
		memory_ptr addr = (addr_top << 8) | addr_bot;

		if(addr+size > MEMORY_SIZE) return ERR_VM_DATA2LARGE;

		for(memory_ptr i = 0; i < size; i++)
		{
			vm->memory[addr+i] = fgetc(vm->program);
			if(ferror(vm->program))
				return ERR_VM_BAD_READ;
		}
	}
}

uint8_t vm_do_text(struct VM* vm)
{
	struct value tmp;
	while(1)
	{
		op opcode = fgetc(vm->program);
		if(ferror(vm->program))
			return ERR_VM_BAD_READ;


		switch(opcode)
		{
		case OP_NOOP:  break;
		case OP_PANIC: break;
		case OP_DROP:
			if(vm->stack.end == 0) {
				return ERR_VM_STACK_UNDER;
			}
			vm->stack.end--;
			free(vm->stack.values[vm->stack.end].value);
			break;
		case OP_SWAP:
			if(vm->stack.end < 2) {
				return ERR_VM_STACK_UNDER;
			}
			tmp = vm->stack.values[vm->stack.end-2];
			vm->stack.values[vm->stack.end-2] = vm->stack.values[vm->stack.end-1];
			vm->stack.values[vm->stack.end-1] = tmp;
			break;
		case OP_ROT:
			if(vm->stack.end < 3) {
				return ERR_VM_STACK_UNDER;
			}
			tmp = vm->stack.values[vm->stack.end-3];
			vm->stack.values[vm->stack.end-3] = vm->stack.values[vm->stack.end-2];
			vm->stack.values[vm->stack.end-2] = vm->stack.values[vm->stack.end-1];
			vm->stack.values[vm->stack.end-1] = tmp;
			break;
		case OP_OVER:
			if(vm->stack.end < 2) {
				return ERR_VM_STACK_UNDER;
			}
			if(vm->stack.end == STACK_SIZE) {
				return ERR_VM_STACK_OVER;
			}
			vm->stack.values[vm->stack.end] = vm->stack.values[vm->stack.end-2];
			vm->stack.end++;
			break;
		case OP_PUSHB:
			if(vm->stack.end == STACK_SIZE) {
				return ERR_VM_STACK_OVER;
			}
			uint8_t* the_byte = malloc(1);
			*the_byte = (uint8_t)fgetc(vm->program);
			vm->stack.values[vm->stack.end].type = v_byte;
			vm->stack.values[vm->stack.end].value = the_byte;
			vm->stack.end++;
			break;
		case OP_PUSHP:
			if(vm->stack.end == STACK_SIZE) {
				return ERR_VM_STACK_OVER;
			}
			uint8_t* the_ptr = malloc(2);
			* the_ptr    = (uint8_t)fgetc(vm->program);
			*(the_ptr+1) = (uint8_t)fgetc(vm->program);
			vm->stack.values[vm->stack.end].type = v_ptr;
			vm->stack.values[vm->stack.end].value = the_ptr;
			vm->stack.end++;
			break;
		case OP_PUSHI:
			if(vm->stack.end == STACK_SIZE) {
				return ERR_VM_STACK_OVER;
			}
			uint8_t* the_int = malloc(4);
			* the_int    = (uint8_t)fgetc(vm->program);
			*(the_int+1) = (uint8_t)fgetc(vm->program);
			*(the_int+2) = (uint8_t)fgetc(vm->program);
			*(the_int+3) = (uint8_t)fgetc(vm->program);
			vm->stack.values[vm->stack.end].type = v_int;
			vm->stack.values[vm->stack.end].value = the_int;
			vm->stack.end++;
			break;
		case OP_PUSHF:
			if(vm->stack.end == STACK_SIZE) {
				return ERR_VM_STACK_OVER;
			}
			uint8_t* the_float = malloc(4);
			* the_float    = (uint8_t)fgetc(vm->program);
			*(the_float+1) = (uint8_t)fgetc(vm->program);
			*(the_float+2) = (uint8_t)fgetc(vm->program);
			*(the_float+3) = (uint8_t)fgetc(vm->program);
			vm->stack.values[vm->stack.end].type = v_float;
			vm->stack.values[vm->stack.end].value = the_float;
			vm->stack.end++;
			break;
		}
	}
}
