/*
Object.h
--------
Defines the skvmObject structure and it's public API.

qeaml 18.10.2022
*/

#ifndef SKVM_OBJECT
#define SKVM_OBJECT

#include "Common.h"

enum skvmObjectType {
  skvmObjectTypeBool,
  skvmObjectTypeChar,
  skvmObjectTypeInt,
  skvmObjectTypeFloat,
  skvmObjectTypeString,
  skvmObjectTypeArray,
  skvmObjectTypeStruct,
};

typedef enum skvmObjectType skvmObjectType;

struct skvmObject {
  skvmObjectType type;
  union {
    bool  _bool;
    u8    _char;
    i32   _int;
    f32   _float;
    char* string;
    struct {
      u32 len, cap;
      struct skvmObject* data;
    } array;
    struct {
      u32 size;
      struct skvmObject* data;
    } _struct;
  };
};

typedef struct skvmObject skvmObject;

void skvmObjectSetBool  (skvmObject* this, bool value);
void skvmObjectSetChar  (skvmObject* this, u8   value);
void skvmObjectSetInt   (skvmObject* this, i32  value);
void skvmObjectSetFloat (skvmObject* this, f32  value);
void skvmObjectSetString(skvmObject* this, char* value);

bool skvmObjectGetArray (skvmObject* this, u32 idx, skvmObject* out);
bool skvmObjectSetArray (skvmObject* this, u32 idx, skvmObject  val);
void skvmObjectGrowArray(skvmObject* this, u32 amt);
bool skvmObjectGetStruct(skvmObject* this, u32 idx, skvmObject* out);
bool skvmObjectSetStruct(skvmObject* this, u32 idx, skvmObject  val);

void skvmObjectClone(skvmObject* from, skvmObject* to);
void skvmObjectClear(skvmObject* this);

#endif // SKVM_OBJECT
