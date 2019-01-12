#ifndef SystemHeader
#define SystemHeader

#include "Core.h"
#include "List.h"

typedef struct {
  cString name;
  cString maybeArg;
} processOption;

typedef list* (*ParseOptions)(int, char**);

typedef struct {
  ParseOptions parseOptions;
} SystemModule;

extern const SystemModule System;

#endif
