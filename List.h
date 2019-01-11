#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "Core.h"
#include "Box.h"

struct list {
  box data;
  struct list* next;
};
typedef struct list list;

typedef void (*BoxAction)(void* boxContent);
typedef box (*BoxTransformer)(void* boxContent);

struct listModule {
  // constructors
  list* (*empty)(void);
  list* (*integerRange)(int first, int last);

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

  // memory
  void (*free)(list* list);
};

extern const struct boxModule Box;
extern const struct listModule List;
