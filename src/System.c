#include "Core.h"
#include "System.h"

#include <string.h>

list* systemParseOptions(int argCount, char** args) {
  
  cString acceptLongOption(void* cStringPointer) {
    cString arg = *((cString*) cStringPointer);
    return (cString)
      VoidPointer.ifElse
      ( strncmp("--", arg, 2) == 0
	, ((void*) arg) + 2 * sizeof(char)
	, NULL);
  }

  // for sintance in here I would not be able to
  // to evaluate al the arguments upfront, because some of the inputs can be NULL
  // and will cause segfault
  box parseOptionArg(cString maybeOption) {
    if (maybeOption == NULL) {
      return Box.box(0, NULL);
    } else if (NULL == strpbrk(maybeOption, "=")) {
      processOption noArgOption;
      size_t nameSize = strlen(maybeOption);
      
      noArgOption.name = malloc(sizeof(char) * (nameSize + 1));
      memcpy(noArgOption.name, maybeOption, nameSize);
      noArgOption.name[nameSize] = '\0';
      
      noArgOption.maybeArg = NULL;
      
      return Box.box(sizeof(processOption), &noArgOption);
    } else {
      processOption argOption;
      void* splitAt = (void*) strpbrk(maybeOption, "=");
      size_t nameSize = (size_t) (splitAt - (void*)maybeOption);
      size_t maybeOptionSize = strlen(maybeOption);
      size_t argSize = maybeOptionSize - nameSize - 1;
      
      argOption.name = (cString) malloc(sizeof(char) * (nameSize + 1));
      memcpy(argOption.name, maybeOption, nameSize);
      ((cString) argOption.name)[nameSize] = '\0';
      
      argOption.maybeArg = (cString) malloc(sizeof(char) * (argSize + 1));
      memcpy(argOption.maybeArg, splitAt + sizeof(char), argSize);
      argOption.maybeArg[argSize] = '\0';
      
      return Box.box(sizeof(processOption), &argOption);
    }
  }

  box parseArg(void* argPointer) {
    return parseOptionArg(acceptLongOption(argPointer));
  }
  
  return
    List.map
    (parseArg
     , List.fromCArray(argCount - 1, sizeof(char*), ((void*) args) + sizeof(char*)));
}

const SystemModule System =
  { .parseOptions = systemParseOptions
  };
