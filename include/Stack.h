/*
Stack.h
-------
Defines the skvmStack and it's public API.

qeaml 18.10.2022
*/

#ifndef SKVM_STACK
#define SKVM_STACK

#include "Common.h"
#include "Object.h"

struct skvmStack {
  u32 top, cap;
  skvmObject* data;
};

typedef struct skvmStack skvmStack;

void skvmStackInit (skvmStack* this, u32 cap);
void skvmStackPush (skvmStack* this, skvmObject val);
bool skvmStackPop  (skvmStack* this, skvmObject* out);
void skvmStackClear(skvmStack* this);

#endif // SKVM_STACK
