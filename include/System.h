#include "List.h"

typedef list* (*GetArgs)(int, char**);




typedef struct {
  GetArgs getArgs;
} SystemModule

extern const SystemModule System;
