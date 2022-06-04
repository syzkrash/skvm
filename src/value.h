#ifndef VALUE_H
#define VALUE_H

#include <stdint.h>

// value_type represents the 4 types recognized by the VM
enum value_type {
	v_byte, // uint8
	v_ptr,  // uint16
	v_int,  // int32
	v_float // float
};

// value represents a singular value of any tuype
struct value {
	// type of this value
	uint8_t type;
	// data is the individual bytes of the value
	uint8_t data[4];
};

#define value2type(v, t) ((t*)&((v).data))

static int32_t value2int(struct value* v)
{
	switch(v->type)
	{
	case v_byte:
		return *((uint8_t*)&v->data);
	case v_ptr:
		return *((uint16_t*)&v->data);
	case v_int:
		return *((int32_t*)&v->data);
	case v_float:
		return *((float*)&v->data);
	default:
		return -1;
	}
}

#endif
