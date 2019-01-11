#include <stdlib.h>

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

// do not need this yet
/* int intWhen2(bool selectA, int a */
/* 	     , bool selectB, int b */
/* 	     , int defaultValue) { */
/*   if (selectA) { */
/*     return a; */
/*   } else if (selectB) { */
/*     return b; */
/*   } else { */
/*     return defaultValue; */
/*   } */
/* } */

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
  return voidPointerIfElse
    ( (*controlPredicate)(control)
      , intControlFor
      ( (*updateControl)(control)
	, controlPredicate
	, updateControl
	, (*mapState)(control, state)
	, mapState)
      , state);
}


