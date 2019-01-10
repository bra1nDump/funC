#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct box {
  void* managedPointer;
};
typedef struct box box;

typedef box (*BoxInVoidPointer)(void* boxContent);
typedef void (*VoidInVoidPointer)(void* boxContent);

struct boxModule {
  // constructors
  box (*box)(size_t size, void* managedPointer);

  // lifters
  box (*bind)(BoxInVoidPointer f, box b);
  void (*bind_)(VoidInVoidPointer f, box b);

  // 
  void (*free)(box b);
};
