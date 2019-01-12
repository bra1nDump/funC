#ifndef ListHeader
#define ListHeader

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "Core.h"

struct list {
  box data;
  struct list* next;
};
typedef struct list list;

typedef void (*BoxAction)(void* boxContent);
typedef box (*BoxTransformer)(void* boxContent);
typedef box (*BoxFolder)(box state, void* boxContent);

typedef struct {
  // constructors
  list* (*empty)(void);
  list* (*integerRange)(int first, int last);
  list* (*fromCArray)(int count, size_t elementSize, void* array);

  // state
  bool (*isEmpty)(const list* list);

  // operators
  list* (*consBox)(box box, list* list);
  list* (*cons)(size_t size, void* umanagedPointer, list* list);

  // function lifters
  
  // no need to constuct a new list, just map over it
  // for stateful computations only
  void (*map_)(BoxAction f, const list* list);

  // we need to construct a new list, potentially of
  // different type
  list* (*map)(BoxTransformer f, const list* list);
  box (*fold)(BoxFolder f, box state, const list* list);

  // memory
  void (*free)(list* list);
} ListModule;

extern const ListModule List;

#endif
