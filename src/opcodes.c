#include "opcodes.h"
#include "errors.h"

uint8_t op_noop(struct VM* vm)
{
	return 0;
}

uint8_t op_panic(struct VM* vm)
{
	return 0;
}

uint8_t op_drop(struct VM* vm)
{
	if(vm->stack.end < 1)
		return ERR_VM_STACK_UNDER;

	vm->stack.end--;

	return 0;
}

uint8_t op_dup(struct VM* vm)
{
	if(vm->stack.end >= STACK_SIZE)
		return ERR_VM_STACK_OVER;

	vm->stack.values[vm->stack.end] = vm->stack.values[vm->stack.end-1];
	vm->stack.end++;

	return 0;
}

uint8_t op_swap(struct VM* vm)
{
	if(vm->stack.end < 2)
		return ERR_VM_STACK_UNDER;

	struct value tmp = vm->stack.values[vm->stack.end-2];
	vm->stack.values[vm->stack.end-2] = vm->stack.values[vm->stack.end-1];
	vm->stack.values[vm->stack.end-1] = tmp;

	return 0;
}

uint8_t op_rot(struct VM* vm)
{
	if(vm->stack.end < 3)
		return ERR_VM_STACK_UNDER;

	struct value tmp = vm->stack.values[vm->stack.end-3];
	vm->stack.values[vm->stack.end-3] = vm->stack.values[vm->stack.end-2];
	vm->stack.values[vm->stack.end-2] = vm->stack.values[vm->stack.end-1];
	vm->stack.values[vm->stack.end-1] = tmp;

	return 0;
}

uint8_t op_over(struct VM* vm)
{
	if(vm->stack.end < 2)
		return ERR_VM_STACK_UNDER;
	if(vm->stack.end >= STACK_SIZE)
		return ERR_VM_STACK_OVER;

	vm->stack.values[vm->stack.end] = vm->stack.values[vm->stack.end-2];
	vm->stack.end++;

	return 0;
}

uint8_t op_pushb(struct VM* vm)
{
	if(vm->stack.end >= STACK_SIZE)
		return ERR_VM_STACK_OVER;

	struct value val;
	val.type = v_byte;
	val.data[0] = fgetc(vm->program);
	vm->stack.values[vm->stack.end] = val;
	vm->stack.end++;

	return 0;
}

uint8_t op_pushp(struct VM* vm)
{
	if(vm->stack.end >= STACK_SIZE)
		return ERR_VM_STACK_OVER;

	struct value val;
	val.type = v_ptr;
	val.data[0] = fgetc(vm->program);
	val.data[1] = fgetc(vm->program);
	vm->stack.values[vm->stack.end] = val;
	vm->stack.end++;

	return 0;
}

uint8_t op_pushi(struct VM* vm)
{
	if(vm->stack.end >= STACK_SIZE)
		return ERR_VM_STACK_OVER;

	struct value val;
	val.type = v_int;
	val.data[0] = fgetc(vm->program);
	val.data[1] = fgetc(vm->program);
	val.data[2] = fgetc(vm->program);
	val.data[3] = fgetc(vm->program);
	vm->stack.values[vm->stack.end] = val;
	vm->stack.end++;

	return 0;
}

uint8_t op_pushf(struct VM* vm)
{
	if(vm->stack.end >= STACK_SIZE)
		return ERR_VM_STACK_OVER;

	struct value val;
	val.type = v_float;
	val.data[0] = fgetc(vm->program);
	val.data[1] = fgetc(vm->program);
	val.data[2] = fgetc(vm->program);
	val.data[3] = fgetc(vm->program);
	vm->stack.values[vm->stack.end] = val;
	vm->stack.end++;

	return 0;
}

#warning TODO: properly implement PUSHL after labels & functions

uint8_t op_pushl(struct VM* vm)
{
	if(vm->stack.end >= STACK_SIZE)
		return ERR_VM_STACK_OVER;

	struct value val;
	val.type = v_ptr;
	val.data[0] = fgetc(vm->program);
	val.data[1] = fgetc(vm->program);
	vm->stack.values[vm->stack.end] = val;
	vm->stack.end++;

	return 0;
}

#warning TODO: implement the rest of the opcodes
