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

uint8_t op_getb(struct VM* vm)
{
	if(vm->stack.end < 1)
		return ERR_VM_STACK_UNDER;

	struct value addr_val = vm->stack.values[vm->stack.end-1];
	if(addr_val.type != v_ptr)
		return ERR_VM_EXPCT_PTR;

	memory_ptr addr = *((memory_ptr*)&addr_val.data);
	uint8_t the_byte = *((uint8_t*)&vm->memory + addr);

	struct value byte_value;
	byte_value.type = v_byte;
	*((uint8_t*)&byte_value.data) = the_byte;
	vm->stack.values[vm->stack.end-1] = byte_value;

	return 0;
}

uint8_t op_getp(struct VM* vm)
{
	if(vm->stack.end < 1)
		return ERR_VM_STACK_UNDER;

	struct value addr_val = vm->stack.values[vm->stack.end-1];
	if(addr_val.type != v_ptr)
		return ERR_VM_EXPCT_PTR;

	memory_ptr addr = *((memory_ptr*)&addr_val.data);
	memory_ptr the_ptr = *((memory_ptr*)&vm->memory + addr);

	struct value ptr_value;
	ptr_value.type = v_ptr;
	*((memory_ptr*)&ptr_value.data) = the_ptr;
	vm->stack.values[vm->stack.end-1] = ptr_value;

	return 0;
}

uint8_t op_geti(struct VM* vm)
{
	if(vm->stack.end < 1)
		return ERR_VM_STACK_UNDER;

	struct value addr_val = vm->stack.values[vm->stack.end-1];
	if(addr_val.type != v_ptr)
		return ERR_VM_EXPCT_PTR;

	memory_ptr addr = *((memory_ptr*)&addr_val.data);
	int32_t the_int = *((int32_t*)&vm->memory + addr);

	struct value int_value;
	int_value.type = v_int;
	*((int32_t*)&int_value.data) = the_int;
	vm->stack.values[vm->stack.end-1] = int_value;

	return 0;
}

uint8_t op_getf(struct VM* vm)
{
	if(vm->stack.end < 1)
		return ERR_VM_STACK_UNDER;

	struct value addr_val = vm->stack.values[vm->stack.end-1];
	if(addr_val.type != v_ptr)
		return ERR_VM_EXPCT_PTR;

	memory_ptr addr = *((memory_ptr*)&addr_val.data);
	float the_float = *((float*)&vm->memory + addr);

	struct value float_value;
	float_value.type = v_float;
	*((float*)&float_value.data) = the_float;
	vm->stack.values[vm->stack.end-1] = float_value;

	return 0;
}

uint8_t op_setb(struct VM* vm)
{
	if(vm->stack.end < 2)
		return ERR_VM_STACK_UNDER;

	struct value addr_val = vm->stack.values[vm->stack.end-1];
	if(addr_val.type != v_ptr)
		return ERR_VM_EXPCT_PTR;
	struct value byte_val = vm->stack.values[vm->stack.end-2];
	if(byte_val.type != v_byte)
		return ERR_VM_EXPCT_BYTE;
	vm->stack.end -= 2;

	memory_ptr addr = *((memory_ptr*)&addr_val.data);
	uint8_t the_byte = *((uint8_t*)&byte_val.data);

	*((uint8_t*)&vm->memory + addr) = the_byte;

	return 0;
}

uint8_t op_setp(struct VM* vm)
{
	if(vm->stack.end < 2)
		return ERR_VM_STACK_UNDER;

	struct value addr_val = vm->stack.values[vm->stack.end-1];
	if(addr_val.type != v_ptr)
		return ERR_VM_EXPCT_PTR;
	struct value ptr_val = vm->stack.values[vm->stack.end-2];
	if(ptr_val.type != v_ptr)
		return ERR_VM_EXPCT_PTR;
	vm->stack.end -= 2;

	memory_ptr addr = *((memory_ptr*)&addr_val.data);
	memory_ptr the_ptr = *((memory_ptr*)&ptr_val.data);

	*((memory_ptr*)&vm->memory + addr) = the_ptr;

	return 0;
}

uint8_t op_seti(struct VM* vm)
{
	if(vm->stack.end < 2)
		return ERR_VM_STACK_UNDER;

	struct value addr_val = vm->stack.values[vm->stack.end-1];
	if(addr_val.type != v_ptr)
		return ERR_VM_EXPCT_PTR;
	struct value int_val = vm->stack.values[vm->stack.end-2];
	if(int_val.type != v_int)
		return ERR_VM_EXPCT_INT;
	vm->stack.end -= 2;

	memory_ptr addr = *((memory_ptr*)&addr_val.data);
	int32_t the_int = *((int32_t*)&int_val.data);

	*((int32_t*)&vm->memory + addr) = the_int;

	return 0;
}

uint8_t op_setf(struct VM* vm)
{
	if(vm->stack.end < 2)
		return ERR_VM_STACK_UNDER;

	struct value addr_val = vm->stack.values[vm->stack.end-1];
	if(addr_val.type != v_ptr)
		return ERR_VM_EXPCT_PTR;
	struct value float_val = vm->stack.values[vm->stack.end-2];
	if(float_val.type != v_float)
		return ERR_VM_EXPCT_FLOAT;
	vm->stack.end -= 2;

	memory_ptr addr = *((memory_ptr*)&addr_val.data);
	float the_float = *((float*)&float_val.data);

	*((float*)&vm->memory + addr) = the_float;

	return 0;
}

uint8_t op_add(struct VM* vm)
{
	if(vm->stack.end < 2)
		return ERR_VM_STACK_UNDER;

	vm->stack.end--;
	struct value av = vm->stack.values[vm->stack.end];
	struct value bv = vm->stack.values[vm->stack.end-1];
	int32_t a = value2int(&av);
	int32_t b = value2int(&bv);

	vm->stack.values[vm->stack.end-1].type = v_int;
	*value2type(vm->stack.values[vm->stack.end-1], int32_t) = a + b;

	return 0;
}

uint8_t op_sub(struct VM* vm)
{
	if(vm->stack.end < 2)
		return ERR_VM_STACK_UNDER;

	vm->stack.end--;
	struct value av = vm->stack.values[vm->stack.end];
	struct value bv = vm->stack.values[vm->stack.end-1];
	int32_t a = value2int(&av);
	int32_t b = value2int(&bv);

	vm->stack.values[vm->stack.end-1].type = v_int;
	*value2type(vm->stack.values[vm->stack.end-1], int32_t) = a - b;

	return 0;
}

uint8_t op_mul(struct VM* vm)
{
	if(vm->stack.end < 2)
		return ERR_VM_STACK_UNDER;

	vm->stack.end--;
	struct value av = vm->stack.values[vm->stack.end];
	struct value bv = vm->stack.values[vm->stack.end-1];
	int32_t a = value2int(&av);
	int32_t b = value2int(&bv);

	vm->stack.values[vm->stack.end-1].type = v_int;
	*value2type(vm->stack.values[vm->stack.end-1], int32_t) = a * b;

	return 0;
}

uint8_t op_dimd(struct VM* vm)
{
	if(vm->stack.end < 2)
		return ERR_VM_STACK_UNDER;

	struct value av = vm->stack.values[vm->stack.end-1];
	struct value bv = vm->stack.values[vm->stack.end-2];
	int32_t a = value2int(&av);
	int32_t b = value2int(&bv);

	vm->stack.values[vm->stack.end-1].type = v_int;
	*value2type(vm->stack.values[vm->stack.end-1], int32_t) = a / b;
	vm->stack.values[vm->stack.end-21].type = v_int;
	*value2type(vm->stack.values[vm->stack.end-2], int32_t) = a % b;

	return 0;
}

uint8_t op_lsh(struct VM* vm)
{
	if(vm->stack.end < 2)
		return ERR_VM_STACK_UNDER;

	vm->stack.end--;
	struct value av = vm->stack.values[vm->stack.end];
	struct value bv = vm->stack.values[vm->stack.end-1];
	int32_t a = value2int(&av);
	int32_t b = value2int(&bv);

	vm->stack.values[vm->stack.end-1].type = v_int;
	*value2type(vm->stack.values[vm->stack.end-1], int32_t) = a << b;

	return 0;
}

uint8_t op_rsh(struct VM* vm)
{
	if(vm->stack.end < 2)
		return ERR_VM_STACK_UNDER;

	vm->stack.end--;
	struct value av = vm->stack.values[vm->stack.end];
	struct value bv = vm->stack.values[vm->stack.end-1];
	int32_t a = value2int(&av);
	int32_t b = value2int(&bv);

	vm->stack.values[vm->stack.end-1].type = v_int;
	*value2type(vm->stack.values[vm->stack.end-1], int32_t) = a >> b;

	return 0;
}

uint8_t op_and(struct VM* vm)
{
	if(vm->stack.end < 2)
		return ERR_VM_STACK_UNDER;

	vm->stack.end--;
	struct value av = vm->stack.values[vm->stack.end];
	struct value bv = vm->stack.values[vm->stack.end-1];
	int32_t a = value2int(&av);
	int32_t b = value2int(&bv);

	vm->stack.values[vm->stack.end-1].type = v_int;
	*value2type(vm->stack.values[vm->stack.end-1], int32_t) = a & b;

	return 0;
}

uint8_t op_or(struct VM* vm)
{
	if(vm->stack.end < 2)
		return ERR_VM_STACK_UNDER;

	vm->stack.end--;
	struct value av = vm->stack.values[vm->stack.end];
	struct value bv = vm->stack.values[vm->stack.end-1];
	int32_t a = value2int(&av);
	int32_t b = value2int(&bv);

	vm->stack.values[vm->stack.end-1].type = v_int;
	*value2type(vm->stack.values[vm->stack.end-1], int32_t) = a | b;

	return 0;
}

uint8_t op_xor(struct VM* vm)
{
	if(vm->stack.end < 2)
		return ERR_VM_STACK_UNDER;

	vm->stack.end--;
	struct value av = vm->stack.values[vm->stack.end];
	struct value bv = vm->stack.values[vm->stack.end-1];
	int32_t a = value2int(&av);
	int32_t b = value2int(&bv);

	vm->stack.values[vm->stack.end-1].type = v_int;
	*value2type(vm->stack.values[vm->stack.end-1], int32_t) = a ^ b;

	return 0;
}

uint8_t op_not(struct VM* vm)
{
	if(vm->stack.end < 1)
		return ERR_VM_STACK_UNDER;

	struct value v = vm->stack.values[vm->stack.end-1];
	int32_t i = value2int(&v);

	vm->stack.values[vm->stack.end-1].type = v_int;
	*value2type(vm->stack.values[vm->stack.end-1], int32_t) = ~i;

	return 0;
}

#warning TODO: implement the rest of the opcodes
