#include "stack.h"

void stack_push(struct stack s, struct value v)
{
	s.values[s.end] = v;
	s.end++;
}

struct value stack_pop(struct stack s)
{
	s.end--;
	struct value v = s.values[s.end];
	return v;
}

void callstack_push(struct callstack c, program_ptr addr)
{
	c.calls[c.end] = addr;
	c.end++;
}

program_ptr callstack_pop(struct callstack c)
{
	c.end--;
	program_ptr addr = c.calls[c.end];
	c.calls[c.end] = 0;
	return addr;
}
