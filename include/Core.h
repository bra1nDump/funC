#include <stdbool.h>

#ifndef CoreHeader
#define CoreHeader

// common function types
typedef void (*VoidToVoid)(void);
typedef int (*IntToInt)(int);
typedef bool (*IntToBool)(int);
typedef void (*VoidPointerToVoid)(void*);

// simple switches if else guard
typedef void (*Guard)(bool, VoidToVoid);
typedef int (*IntIfElse)(bool, int, int);
typedef void* (*VoidPointerIfElse)(bool, void*, void*);

// match
typedef void* (*VoidPointerMatch3)(int
				   , int, void*
				   , int, void*
				   , int, void*);
typedef int (*IntMatch3)(int
			 , int, int
			 , int, int
			 , int, int);

typedef int (*IntWhen2)(bool, int
			, bool, int
			, int);

// loops/generators
typedef void* (*IntForBody)(int, void*);
typedef void* (*IntControlFor)(int, IntToBool, IntToInt
			       , void*, IntForBody);

typedef enum { Less, Equal, Greater } Order;

typedef Order (*IntComparator)(int, int);

typedef struct {
  IntIfElse ifElse;
  IntMatch3 match3;
  IntWhen2 when2;
  IntControlFor controlFor;

  IntComparator compare;
  
  IntToInt increment;
  IntToInt decrement;
} IntModule;

typedef struct {
  Guard guard;
} VoidModule;

typedef struct {
  VoidPointerIfElse ifElse;
  VoidPointerMatch3 match3;
} VoidPointerModule;

extern const IntModule Int;
extern const VoidModule Void;
extern const VoidPointerModule VoidPointer;

#endif