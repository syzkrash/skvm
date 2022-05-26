// Generated with gen_op.py [2022-05-26 18:33:52.045932]
// Don't edit manually
#ifndef OPCODES_H
#define OPCODES_H

#include <stdint.h>

typedef uint8_t op;
typedef uint8_t(opfunc)(struct VM*);

#define OP_NOOP ((op)0x00)
uint8_t op_noop(struct VM*);
#define OP_PANIC ((op)0x01)
uint8_t op_panic(struct VM*);
#define OP_DROP ((op)0x10)
uint8_t op_drop(struct VM*);
#define OP_SWAP ((op)0x11)
uint8_t op_swap(struct VM*);
#define OP_ROT ((op)0x12)
uint8_t op_rot(struct VM*);
#define OP_OVER ((op)0x13)
uint8_t op_over(struct VM*);
#define OP_PUSHB ((op)0x14)
uint8_t op_pushb(struct VM*);
#define OP_PUSHP ((op)0x15)
uint8_t op_pushp(struct VM*);
#define OP_PUSHI ((op)0x16)
uint8_t op_pushi(struct VM*);
#define OP_PUSHF ((op)0x17)
uint8_t op_pushf(struct VM*);
#define OP_PUSHL ((op)0x18)
uint8_t op_pushl(struct VM*);
#define OP_GETB ((op)0x20)
uint8_t op_getb(struct VM*);
#define OP_SETB ((op)0x21)
uint8_t op_setb(struct VM*);
#define OP_GETP ((op)0x22)
uint8_t op_getp(struct VM*);
#define OP_SETP ((op)0x23)
uint8_t op_setp(struct VM*);
#define OP_GETI ((op)0x24)
uint8_t op_geti(struct VM*);
#define OP_SETI ((op)0x25)
uint8_t op_seti(struct VM*);
#define OP_GETF ((op)0x26)
uint8_t op_getf(struct VM*);
#define OP_SETF ((op)0x27)
uint8_t op_setf(struct VM*);
#define OP_ADD ((op)0x30)
uint8_t op_add(struct VM*);
#define OP_SUB ((op)0x31)
uint8_t op_sub(struct VM*);
#define OP_MUL ((op)0x32)
uint8_t op_mul(struct VM*);
#define OP_DIMD ((op)0x33)
uint8_t op_dimd(struct VM*);
#define OP_LSH ((op)0x34)
uint8_t op_lsh(struct VM*);
#define OP_RSH ((op)0x35)
uint8_t op_rsh(struct VM*);
#define OP_AND ((op)0x36)
uint8_t op_and(struct VM*);
#define OP_OR ((op)0x37)
uint8_t op_or(struct VM*);
#define OP_XOR ((op)0x38)
uint8_t op_xor(struct VM*);
#define OP_NOT ((op)0x39)
uint8_t op_not(struct VM*);
#define OP_LABEL ((op)0x40)
uint8_t op_label(struct VM*);
#define OP_FUNC ((op)0x41)
uint8_t op_func(struct VM*);
#define OP_JMP ((op)0x42)
uint8_t op_jmp(struct VM*);
#define OP_CALL ((op)0x43)
uint8_t op_call(struct VM*);
#define OP_RET ((op)0x44)
uint8_t op_ret(struct VM*);
#define OP_JMPIF ((op)0x4F)
uint8_t op_jmpif(struct VM*);


// get_op_func returns the function corresponding to the given opcode
opfunc *get_op_func(op opcode)
{
  switch(opcode)
  {
    case OP_NOOP: return &op_noop;
    case OP_PANIC: return &op_panic;
    case OP_DROP: return &op_drop;
    case OP_SWAP: return &op_swap;
    case OP_ROT: return &op_rot;
    case OP_OVER: return &op_over;
    case OP_PUSHB: return &op_pushb;
    case OP_PUSHP: return &op_pushp;
    case OP_PUSHI: return &op_pushi;
    case OP_PUSHF: return &op_pushf;
    case OP_PUSHL: return &op_pushl;
    case OP_GETB: return &op_getb;
    case OP_SETB: return &op_setb;
    case OP_GETP: return &op_getp;
    case OP_SETP: return &op_setp;
    case OP_GETI: return &op_geti;
    case OP_SETI: return &op_seti;
    case OP_GETF: return &op_getf;
    case OP_SETF: return &op_setf;
    case OP_ADD: return &op_add;
    case OP_SUB: return &op_sub;
    case OP_MUL: return &op_mul;
    case OP_DIMD: return &op_dimd;
    case OP_LSH: return &op_lsh;
    case OP_RSH: return &op_rsh;
    case OP_AND: return &op_and;
    case OP_OR: return &op_or;
    case OP_XOR: return &op_xor;
    case OP_NOT: return &op_not;
    case OP_LABEL: return &op_label;
    case OP_FUNC: return &op_func;
    case OP_JMP: return &op_jmp;
    case OP_CALL: return &op_call;
    case OP_RET: return &op_ret;
    case OP_JMPIF: return &op_jmpif;

    default: return NULL;
  }
}

#endif