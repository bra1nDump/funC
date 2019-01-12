#include "Core.h"
#include "List.h"
#include "System.h"

void stringPrint(void* string) {
  printf("%s\n", *((char**) string));
}

void optionPrint(void* optionPointer) {
  processOption* mainOption = (processOption*) optionPointer;
  if (mainOption == NULL) {
    printf("not an option\n");
  } else if (mainOption->maybeArg == NULL) {
    printf("option (no arg): %s\n", mainOption->name);
  } else {
    printf("option (with arg): %s %s\n", mainOption->name, mainOption->maybeArg);
  }
}

int main(int argc, char** argv) {
  list* options = System.parseOptions(argc, argv);
  List.map_(optionPrint, options);
}
