# cheat sheet

# $@ - left side of the rule
# $< - first item in the dependency list
# % - match any number of characters (also is bound to 
#     what ever it matched in the following commands)
# $(var:.suffix=.newSuffix) - replace suffix
# $(patsubst pattern,replacement,inText)


# special variables
SHELL = /bin/sh
CC = gcc-8

cFlags = -Iinclude

# this is to create a shared library (.so file)
libraryFlags = -shared

# output
libDir = lib
target = $(libDir)/funC.so

# input locations
srcDir = src
headerDir = include
objectDir = $(srcDir)/obj

$(shell mkdir $(objDir))

# other
sources = $(shell echo $(srcDir)/*.c)
objects = $(patsubst $(srcDir)/%.c,$(objectDir)/%.o,$(sources))

$(info $(objectDir))
$(info $(sources))
$(info $(objects))

$(objectDir)/%.o: $(srcDir)/%.c
	$(CC) $(cFlags) -c -o $@ $<

$(target): $(objects)
	$(CC) $(cFlags) $(objects) -o $@ $(libraryFlags)
