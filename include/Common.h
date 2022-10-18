/*
Common.h
--------
Contains various shared function and type definitions.

qeaml 18.10.2022
*/

#ifndef SKVM_COMMON
#define SKVM_COMMON

#include <stddef.h>
#include <stdbool.h>

typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef unsigned long long u64;
typedef char      i8;
typedef short     i16;
typedef int       i32;
typedef long long i64;
typedef float  f32;
typedef double f64;

#define UNUSED(expr) (void)(expr)

#ifdef DEBUG
#include <stdio.h>
#include <stdlib.h>
#define log(msg) fprintf(stderr, "(debug) "msg"\n")
#define logf(fmt, ...) fprintf(stderr, "(debug) "fmt"\n", __VA_ARGS__)
#define assert(expr, msg) if(!(expr)) {\
  fprintf("-- Assertion `"msg"` failed: "#expr);\
  exit(-1);\
}
#else
#define log(msg)
#define logf(fmt, ...)
#define assert(expr, msg)
#endif

#endif // SKVM_COMMON
