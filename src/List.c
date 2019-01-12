#include "Core.h"
#include "List.h"

// forward-used declarations
// list* listCons(size_t size, void* unmanagedPointer, list* xs);

bool listIsEmpty(const list* xs) {
  return xs == NULL;
}

list* listEmpty() {
  return NULL;
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

list* listFromCArray(int count, size_t elementSize, void* array) {
  if (count == 0) {
    return listEmpty();
  } else {
    return listCons
      ( elementSize, array
	, listFromCArray(count - 1, elementSize, array + 1));
  }
}

void* listConsInt(int x, void* xs) {
  return (void*) listCons(sizeof(int), (void*) &x, (list*) xs);
}

list* listIntegerRange(int first, int last) {
  bool less(int x) { return x <= last; }
  bool constantFalse(int _x) { return false; }
  bool greater(int x) { return x >= last; }
  
  return (list*)
    Int.controlFor
    // loop control
    ( first
      , (IntToBool)
      VoidPointer.match3
      ( Int.compare (first, last)
	, Less, (void*) less
	, Equal, (void*) constantFalse
	, Greater, (void*) greater)
      , (IntToInt) VoidPointer.match3
      ( Int.compare (first, last)
	, Less, (void*) Int.increment
	, Equal, NULL
	, Greater, (void*) Int.decrement)

      // loop body
      , (void*) listEmpty()
      , listConsInt
      );
}

void listMap_(VoidPointerToVoid f, const list* xs) {
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
    .fromCArray = listFromCArray,
    .integerRange = listIntegerRange,
    .isEmpty = listIsEmpty,
    .consBox = listConsBox,
    .cons = listCons,
    .map_ = listMap_,
    .map = listMap,
    .free = listFree
  };


