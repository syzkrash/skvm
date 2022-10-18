/*
Stack.c
-------
Implements the skvmStack API from [Stack.h].

qeaml 18.10.2022
*/

#include "Stack.h"
#include <stdlib.h>

void skvmStackInit(skvmStack *this, u32 cap) {
  this->cap = cap;
  this->top = 0;
  this->data = calloc(cap, sizeof(skvmObject));
}

void skvmStackClear(skvmStack *this) {
  skvmObject obj;
  while(skvmStackPop(this, &obj))
    skvmObjectClear(&obj);
}

void skvmStackPush(skvmStack *this, skvmObject val) {
  if(this->top+1 >= this->cap) {
    this->cap *= 2;
    this->data = realloc(this->data, this->cap*sizeof(skvmObject));
  }
  this->data[this->top++] = val;
}

bool skvmStackPop(skvmStack *this, skvmObject *out) {
  if(this->top == 0)
    return false;
  *out = this->data[--this->top];
  return true;
}
