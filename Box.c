#include "Box.h"

box boxBox(size_t size, void* managedPointer) {
  box box;
  box.managedPointer = malloc(size);

  memcpy(box.managedPointer, managedPointer, size);

  return box;
}

box boxBind(BoxInVoidPointer f, box b) {
  return (*f)(b.managedPointer);
}

void boxBind_(VoidInVoidPointer f, box b) {
  (*f)(b.managedPointer);
}

void boxFree(box x) {
  free(x.managedPointer);
}

const struct boxModule Box =
  { .box = boxBox,
    .bind = boxBind,
    .bind_ = boxBind_,
    .free = boxFree
  };
