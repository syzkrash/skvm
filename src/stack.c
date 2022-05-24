#include "stack.h"

void stack_push(struct stack *s, struct value *v)
{
	s->values[s->end] = *v;
	s->end++;
}

struct value stack_pop(struct stack *s)
{
	s->end--;
	struct value v = s->values[s->end];
	return v;
}

void callstack_push(struct callstack *c, _Bool label, program_ptr addr)
{
	c->calls[c->end].label = label;
	c->calls[c->end].addr = addr;
	c->end++;
}

program_ptr callstack_pop(struct callstack *c)
{
	struct call step;

	do
	{
		c->end--;
		step = c->calls[c->end];
	}
	while(step.label);

	return step.addr;
}
