// Generated with gen_op.py
// Don't edit manually
#ifndef OPCODES_H
#define OPCODES_H

typedef op uint8_t;

#define OP_NOOP ((op)0x00)
#define OP_PANIC ((op)0x01)
#define OP_DROP ((op)0x10)
#define OP_SWAP ((op)0x11)
#define OP_ROT ((op)0x12)
#define OP_OVER ((op)0x13)
#define OP_PUSHB ((op)0x14)
#define OP_PUSHP ((op)0x15)
#define OP_PUSHI ((op)0x16)
#define OP_PUSHF ((op)0x17)
#define OP_PUSHL ((op)0x18)
#define OP_GETB ((op)0x20)
#define OP_SETB ((op)0x21)
#define OP_GETP ((op)0x22)
#define OP_SETP ((op)0x23)
#define OP_GETI ((op)0x24)
#define OP_SETI ((op)0x25)
#define OP_GETF ((op)0x26)
#define OP_SETF ((op)0x27)
#define OP_ADD ((op)0x30)
#define OP_SUB ((op)0x31)
#define OP_MUL ((op)0x32)
#define OP_DIMD ((op)0x33)
#define OP_LSH ((op)0x34)
#define OP_RSH ((op)0x35)
#define OP_AND ((op)0x36)
#define OP_OR ((op)0x37)
#define OP_XOR ((op)0x38)
#define OP_NOT ((op)0x39)
#define OP_LABEL ((op)0x40)
#define OP_FUNC ((op)0x41)
#define OP_JUMP ((op)0x42)
#define OP_CALL ((op)0x43)
#define OP_RET ((op)0x44)
#define OP_JMPIF ((op)0x4F)

#endif
