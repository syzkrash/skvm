#ifndef ERRORS_H
#define ERRORS_H

#define ERR_VM_BAD_READ    0x10
#define ERR_VM_EOF         0x11
#define ERR_VM_UNKNOWN_SEC 0x12
#define ERR_VM_DATA2LARGE  0x13
#define ERR_VM_BAD_OP      0x14

#define ERR_VM_STACK_UNDER 0x1A
#define ERR_VM_STACK_OVER  0x1B
#define ERR_VM_CALLS_UNDER 0x1C
#define ERR_VM_CALLS_OVER  0x1D

#define ERR_VM_OOB_WRITE   0x20
#define ERR_VM_OOB_READ    0x21

#define ERR_VM_EXPCT_BYTE  0x2A
#define ERR_VM_EXPCT_PTR   0x21
#define ERR_VM_EXPCT_INT   0x22
#define ERR_VM_EXPCT_FLOAT 0x23

#endif // ERRORS_H
