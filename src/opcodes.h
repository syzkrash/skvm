#ifndef OPCODES_H
#define OPCODES_H

#define op uint8_t

// --- General instructions ---
// NOOP  - do nothing
// PANIC - quit due to unexpected error
#define OP_NOOP  ((op)0x00)
#define OP_PANIC ((op)0x01)

// --- Stack operations ---
// PUSH<T> - push a value onto the stack; T can be one of
//      B - push a byte
//      P - push a pointer
//      I - push an integer
//      F - push a float
// DROP - drop the last value from the stack
// SWAP - swap the last two values on the stack
// ROT  - rotate the last three values on the stack
// OVER - copy the second value on the stack to the top of the stack
#define OP_DROP  ((op)0x10)
#define OP_SWAP  ((op)0x11)
#define OP_ROT   ((op)0x12)
#define OP_OVER  ((op)0x13)
#define OP_PUSHB ((op)0x14)
#define OP_PUSHP ((op)0x15)
#define OP_PUSHI ((op)0x16)
#define OP_PUSHF ((op)0x17)

// --- Memory operations ---
// GET<T> - get a value from memory; T is the same as for PUSH
// SET<T> - set a value in memory; T is the same here too
#define OP_GETB ((op)0x20)
#define OP_SETB ((op)0x21)
#define OP_GETP ((op)0x22)
#define OP_SETP ((op)0x23)
#define OP_GETI ((op)0x24)
#define OP_SETI ((op)0x25)
#define OP_GETF ((op)0x26)
#define OP_SETF ((op)0x27)

// --- Arithmetic & binary logic ---
// ADD  - add two numeric values
// SUB  - subtract two numeric values
// MUL  - multiply two numeric values
// DIVM - divmod two numeric values, push both the division result and the
//        remainder onto the stack
// LSH  - bitshift left
// RSH  - bitshift right
// AND  - bitwise AND
// OR   - bitwise OR
// XOR  - bitwise XOR
// NOT  - bitwise NOT
#define OP_ADD  ((op)0x30)
#define OP_SUB  ((op)0x31)
#define OP_MUL  ((op)0x32)
#define OP_DIMD ((op)0x33)
#define OP_LSH  ((op)0x34)
#define OP_RSH  ((op)0x35)
#define OP_AND  ((op)0x36)
#define OP_OR   ((op)0x37)
#define OP_XOR  ((op)0x38)
#define OP_NOT  ((op)0x39)

// --- Section definitions ---
// DATA - defines data pieces that should be loaded into memory before the
//        should continue execution. Note that this section can appear in
//        between other sections, so it could be feasibly used to load a
//        constant into memory at a more convenient time.
// TEXT - contains the actual opcodes of the progam.
// TERM - terminates a TEXT section -- make sure not to use an opcode of this
//        exact value, as it will always take precedence.
#define SEC_DATA (0x01)
#define SEC_TEXT (0x02)
#define SEC_TERM (0x80)

#endif // OPCODES_H
