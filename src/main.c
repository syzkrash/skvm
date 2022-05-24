#include <stdio.h>
#include <stdlib.h>
#include "vm.h"

int main()
{
	struct VM* vm = vm_new(NULL);
	printf("VM address: %p\n", vm);
	printf("VM memory footprint: %db\n", sizeof(struct VM));
	printf("VM stack footprint: %db\n", sizeof(struct stack));
	printf("VM callstack footprint: %db\n", sizeof(struct callstack));
	printf("value footprint: %db\n", sizeof(struct value));
	struct value v;
	v.type = v_byte;
	v.data[0] = 0x69;
	stack_push(&vm->stack, &v);
	printf("VM stack end: %d\n", vm->stack.end);
	free(vm);
}
