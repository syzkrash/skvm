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
	enum value_type type;
	// data is the individual bytes of the value
	uint8_t data[4];
};

#define value2type(v, t) ((t*)&((v).data))

#endif
