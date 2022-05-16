#ifndef VALUE_H
#define VALUE_H

#include <stdlib.h>

// value_type represents the 3 types recognized by the VM
enum value_type {
	v_byte, // uint8
	v_ptr,  // uint16
	v_int,  // int32
};

// value represents a singular value of any tuype
struct value {
	// type of this value
	enum value_type type;
	// value points to the value in memory, the size of the value pointed to is
	// dependent on the value_type of this value
	void* value;
};

#endif
