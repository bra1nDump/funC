#include "System.h"

list* systemParseOptions(int argCount, char** args) {
  return List.fromCArray(argCount, sizeof(char*), args);
}

const SystemModule System =
  { .parseOptions = systemParseOptions
  };
