/*
Object.c
--------
Implements the skvmObject API defined in [Object.h].

qeaml 18.10.2022
*/

#include "Object.h"
#include <stdlib.h>
#include <string.h>

void skvmObjectClear(skvmObject *this) {
  switch(this->type) {
  case skvmObjectTypeString:
    free(this->string);
    break;
  case skvmObjectTypeArray:
    for(size_t i = 0; i < this->array.len; i++) {
      skvmObjectClear(&this->array.data[i]);
    }
    free(this->array.data);
    break;
  case skvmObjectTypeStruct:
    for(size_t i = 0; i < this->_struct.size; i++) {
      skvmObjectClear(&this->_struct.data[i]);
    }
    free(this->_struct.data);
    break;
  default:
    break;
  }
}

void skvmObjectClone(skvmObject *from, skvmObject *to) {
  skvmObjectClear(to);
  to->type = from->type;
  switch(from->type) {
  case skvmObjectTypeBool:
    to->_bool = from->_bool;
    break;
  case skvmObjectTypeChar:
    to->_char = from->_char;
    break;
  case skvmObjectTypeInt:
    to->_int = from->_int;
    break;
  case skvmObjectTypeFloat:
    to->_float = from->_float;
    break;
  case skvmObjectTypeString:
    to->string = malloc(strlen(from->string)+1);
    strcpy(to->string, from->string);
    break;
  case skvmObjectTypeArray:
    to->array.cap = from->array.cap;
    to->array.len = from->array.len;
    to->array.data = calloc(from->array.cap, sizeof(skvmObject));
    for(size_t i = 0; i < from->array.len; i++)
      skvmObjectClone(&from->array.data[i], &to->_struct.data[i]);
    break;
  case skvmObjectTypeStruct:
    to->_struct.size = from->_struct.size;
    to->_struct.data = calloc(from->_struct.size, sizeof(skvmObject));
    for(size_t i = 0; i < from->_struct.size; i++)
      skvmObjectClone(&from->_struct.data[i], &to->_struct.data[i]);
    break;
  }
}

void skvmObjectSetBool(skvmObject *this, bool value) {
  skvmObjectClear(this);
  this->type = skvmObjectTypeBool;
  this->_bool = value;
}

void skvmObjectSetChar(skvmObject *this, u8 value) {
  skvmObjectClear(this);
  this->type = skvmObjectTypeChar;
  this->_char = value;
}

void skvmObjectSetInt(skvmObject *this, i32 value) {
  skvmObjectClear(this);
  this->type = skvmObjectTypeInt;
  this->_int = value;
}

void skvmObjectSetFloat(skvmObject *this, f32 value) {
  skvmObjectClear(this);
  this->type = skvmObjectTypeFloat;
  this->_float = value;
}

void skvmObjectSetString(skvmObject *this, char *value) {
  skvmObjectClear(this);
  this->type = skvmObjectTypeString;
  this->string = malloc(strlen(value)+1);
  strcpy(this->string, value);
}

bool skvmObjectGetArray(skvmObject *this, u32 idx, skvmObject *out) {
  if(this->type != skvmObjectTypeArray)
    return false;
  if(this->array.len <= idx)
    return false;
  if(out)
    *out = this->array.data[idx];
  return true;
}

bool skvmObjectSetArray(skvmObject *this, u32 idx, skvmObject val) {
  if(this->type != skvmObjectTypeArray)
    return false;
  if(this->array.cap <= idx)
    return false;
  this->array.data[idx] = val;
  if(this->array.len <= idx)
    this->array.len = idx-1;
  return true;
}

void skvmObjectGrowArray(skvmObject *this, u32 amt) {
  if(this->type != skvmObjectTypeArray) {
    logf("skvmObjectGrowArray called on value of type %d!", this->type);
    return;
  }
  this->array.cap += amt;
  this->array.data = realloc(this->array.data, this->array.cap*sizeof(skvmObject));
}

bool skvmObjectSetStruct(skvmObject *this, u32 idx, skvmObject val) {
  if(this->type != skvmObjectTypeStruct)
    return false;
  if(this->_struct.size <= idx)
    return false;
  this->_struct.data[idx] = val;
  return true;
}

bool skvmObjectGetStruct(skvmObject *this, u32 idx, skvmObject *out) {
  if(this->type != skvmObjectTypeStruct)
    return false;
  if(this->_struct.size <= idx)
    return false;
  if(out)
    *out = this->_struct.data[idx];
  return true;
}
