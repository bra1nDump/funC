#include <stdlib.h>
#include <stdio.h>

#include "Core.h"

void voidGuard(bool predicate, VoidToVoid action) {
  if (predicate) {
    (*action)();
  }
}

int intIfElse(bool selector, int a, int b) {
  if (selector) {
    return a;
  } else {
    return b;
  }
}

void* voidPointerIfElse(bool selector, void* a, void* b) {
  if (selector) {
    return a;
  } else {
    return b;
  }
}

// like cond in LISP, like when in F# in match statements.
// F# is given preference when picking names, thus the name

// rn only used for compare
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

// multiplexer, we can generalize this by making it multi-argument
// , like printf
// this does not have a default, this it will fail if none were matched
// should only be used with enum types
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

void* intControlFor(int control, IntToBool controlPredicate, IntToInt updateControl
		    , void* state, IntForBody mapState) {

  // this apperently doe not work, since
  // both all of the arguments are evaluated, and the first one
  // will keep evaluating (down the recursion), even though
  // it looks like it is ok, the strict evalutation of arguments
  // does not allow this to work out nicely

  // this can be fixed by giving two functions f() = { return expr; } as arguments instead of
  // expressions, but this hardly can be called a nicer syntax :(
  
  /* return voidPointerIfElse */
  /*   ( (*controlPredicate)(control) */
  /*     , intControlFor */
  /*     ( (*updateControl)(control) */
  /* 	, controlPredicate */
  /* 	, updateControl */
	
  /* 	, (*mapState)(control, state) */
  /* 	, mapState) */
  /*     , state); */


  if ((*controlPredicate)(control)) {
    return intControlFor
      ( (*updateControl)(control)
	, controlPredicate
	, updateControl
	
	, (*mapState)(control, state)
	, mapState);
  } else {
    return state;
  }
}

int increment(int x) { return x + 1; }
int decrement(int x) { return x - 1; }

Order intCompare(int a, int b) {
  return intWhen2
    ( a < b, Less
      , a == b, Equal
      , Greater);
}

const IntModule Int =
  { .ifElse = intIfElse,
    .match3 = intMatch3,
    .when2 = intWhen2,
    .controlFor = intControlFor,

    .compare = intCompare,

    .increment = increment,
    .decrement = decrement
  };

const VoidModule Void =
  { .guard = voidGuard
  };

const VoidPointerModule VoidPointer =
  { .ifElse = voidPointerIfElse,
    .match3 = voidPointerMatch3 
  };

