/*
VM.h
----
Defines the skvm structure and it's public API.

qeaml 18.10.2022
*/

#ifndef SKVM_VM
#define SKVM_VM

#include "Common.h"
#include "Object.h"
#include "Stack.h"

#define SKVM_DEFAULT_STACK_SIZE 16
#define SKVM_DEFAULT_LOCALS_SIZE 16

struct skvm {
  // P and S are the two main registers of skvm
  skvmObject P, S;
  skvmStack stk;
};

#endif // SKVM_VM
