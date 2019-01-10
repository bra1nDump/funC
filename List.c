#include "List.h"

// Operators, need to be factored out into a separate module
// individual to each data type
int increment(int x) { return x + 1; }
int decrement(int x) { return x - 1; }

bool intLessOrEqualThan(int a, int b) {
  return a <= b;
}

bool intGreaterOrEqualThan(int a, int b) {
  return a <= b;
}

bool intConstFalse(int a, int b) {
  return false;
}

// take this into Function module
typedef void (*VoidInVoid)(void);

void voidGuard(bool predicate, VoidInVoid action) {
  if (predicate) {
    (*action)();
  }
}

// multiplexer 2
int intIfElse(bool selector, int a, int b) {
  if (selector) {
    return a;
  } else {
    return b;
  }
}

// like cond in LISP, like when in F# in match statements
// F# is given preference when picking names
int intWhen2(bool selectA, int a
	     , bool selectB, int b
	     , int defaultValue) {
  if (selectA) {
    return a;
  } else if (selectB) {
    return b;
  } else {
    return defaultValue;
  }
}

typedef enum { First, Second, Third } Sum3;

// multiplexer, we can generalize this by making it multi-argument
// , like printf
// this does not have a default, this is 
int intMatch3(int selector
	      , int caseA, int a
	      , int caseB, int b
	      , int caseC, int c) {
  if (selector == caseA) {
    return a;
  } else if (selector == caseB) {
    return b;
  } else if (selector == caseC) {
    return c;
  } else {
    printf("The only thing you should pass to this function is an instance of Enum3\n");
    exit(1);
  }
}

void* voidPointerMatch3(int selector
			, int caseA, void* a
			, int caseB, void* b
			, int caseC, void* c) {
  if (selector == caseA) {
    return a;
  } else if (selector == caseB) {
    return b;
  } else if (selector == caseC) {
    return c;
  } else {
    printf("The only thing you should pass to this function is an instance of Enum3\n");
    exit(1);
  }
}

// also VoidPointer version would be useful
// example: dispatch the top level function to one of the simpler functions
// that return a pointer to a struct/c array
int intMatchEnum3(int selector // enum instance (with default 0,1,2 assignments)
		  , int a
		  , int b
		  , int c) {
  return intMatch3
    ( selector
      , 0, a
      , 1, b
      , 2, c);
}

void* voidPointerMatchEnum3(int selector // enum instance (with default 0,1,2 assignments)
			    , void* a
			    , void* b
			    , void* c) {
  return voidPointerMatch3
    ( selector
      , 0, a
      , 1, b
      , 2, c);
}


typedef enum { Less, Equal, Greater } Order;
Order intCompare(int a, int b) {
  return intWhen2
    ( a < b, Less
      , a == b, Equal
      , Greater);
}

typedef int (*IntToInt)(int);
typedef bool (*IntToBool)(int);
typedef bool (*IntAndIntToBool)(int, int);

//      list*                                   (int, list*)
typedef void* (*IntAndVoidPointerToVoidPointer)(int, void*);
void* intControlFor(int partialControlPredicate
		    , int control, IntAndIntToBool controlPredicate, IntToInt updateControl
		    , void* state, IntAndVoidPointerToVoidPointer mapState) {
  while((*controlPredicate)(control, partialControlPredicate)) {
    state = (*mapState)(control, state);
    control = (*updateControl)(control);
  }
  return state;
}

//

list* listEmpty() {
  return NULL;
}

bool listIsEmpty(const list* xs) {
  return xs == NULL;
}

list* listConsBox(box x, list* xs) {
  list *listPointer = (list*) malloc(sizeof(list));
  listPointer->data = x;
  listPointer->next = xs;

  return listPointer;
}

list* listCons(size_t size, void* unmanagedPointer, list* xs) {
  return listConsBox
    ( Box.box(size, unmanagedPointer)
     , xs);
}

/* list* listIntegerRangeAscending(int first, int last) { */
/*   intControlFor */
/*     ( first */
/*       , lessThan */
/*       , increment */
      

/* } */

/* list* listIntegerRange(int first, int last) { */
/*   return (list*) */
/*     voidPointerMatchEnum3 */
/*     ( intCompare (first, last) */
/*       , listIntegerRangeAscending (first, last) */
/*       , listEmpty() */
/*       , listIntegerRangeDescending (first, last)) */
/* } */

// need closures for this
// actually for the less nice implementation we also need a closure for the same reason
	// need closure for this, othwerwise how do I inject (in predicate)
	// `last` dependency into the function?
	// similar issues with othwer two cases

void* listConsInt(int x, void* xs) {
  return (void*) listCons(sizeof(int), (void*) &x, (list*) xs);
}

list* listIntegerRange(int first, int last) {
  return (list*)
    intControlFor
    ( last
      , first
      , (IntAndIntToBool) voidPointerMatchEnum3
      ( intCompare (first, last)
	, (void*) intLessOrEqualThan
	, (void*) intConstFalse
	, (void*) intGreaterOrEqualThan)
      , (IntToInt) voidPointerMatchEnum3
      ( intCompare (first, last)
	, (void*) increment
	, NULL
	, (void*) decrement)
      , (void*) listEmpty()
      , listConsInt
      );
}

void listMap_(VoidInVoidPointer f, const list* xs) {
  if (listIsEmpty(xs) == false) {
    Box.bind_(f, xs->data);
    listMap_(f, xs->next);
  }
}

list* listMap(BoxInVoidPointer f, const list* xs) {
  if (listIsEmpty(xs)) {
    return listEmpty();
  } else {
    return listConsBox
      ( Box.bind(f, xs->data)
	, listMap(f, xs->next));
  }
}

void listFree(list* xs) {
  if (xs != NULL) {
    listFree(xs->next);
    Box.free(xs->data);
    free(xs);
  }
}

const struct listModule List =
  { .empty = listEmpty,
    .integerRange = listIntegerRange,
    .isEmpty = listIsEmpty,
    .consBox = listConsBox,
    .cons = listCons,
    .map_ = listMap_,
    .map = listMap,
    .free = listFree
  };


