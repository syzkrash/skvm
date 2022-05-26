#ifndef SECTIONS_H
#define SECTIONS_H

#include <stdint.h>

typedef uint8_t sec;

#define SEC_DATA ((sec)0x01)
#define SEC_TEXT ((sec)0x02)
#define SEC_TERM ((sec)0x80)

#endif
