#include "vm.h"
#include "errors.h"
#include "opcodes.h"
#include "sections.h"
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
	sec section = fgetc(vm->program);
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
		if(size == 0) return 0;

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
	op opcode = fgetc(vm->program);
	if(ferror(vm->program))
		return ERR_VM_BAD_READ;

	// SEC_TERM is reserved for ending SEC_TEXT, so just go to the next section
	if(opcode == SEC_TERM) return vm_next(vm);

	// get the function of this opcode
	opfunc* opf = get_op_func(opcode);
	// return an error if no function corresponds to this opcode
	if(opf == NULL) return ERR_VM_BAD_OP;

	// run opcode and return
	return opf(vm);
}
