#include "List.h"

typedef list* (*ParseOptions)(int, char**);

typedef struct {
  ParseOptions parseOptions;
} SystemModule;

extern const SystemModule System;
