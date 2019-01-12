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

###########################################################################################
# output
buildDir = build
funCLib = $(buildDir)/libFunC.so

includeDir = include
srcDir = src
objectDir = $(srcDir)/obj

# include = $(shell echo $(includeDir)/*.h)
sources = $(shell echo $(srcDir)/*.c)
objects = $(patsubst $(srcDir)/%.c,$(objectDir)/%.o,$(sources))

 # fpic - posistion independent code
$(objectDir)/%.o: $(srcDir)/%.c
	$(CC) -fPIC -Wall -O2 -g -I$(includeDir) -c -o $@ $<

# -shared to create a shared library
$(funCLib): $(objects)
	$(CC) $(objects) -o $@ -shared

copyHeaders:
	cp $(includeDir)/*.h $(buildDir)/include/

build: $(funCLib) copyHeaders

#############################################################################################
# tests
testSrcDir = test
testObjectDir = $(testSrcDir)/obj

testSources = $(shell echo $(testSrcDir)/*.c)
testObjects = $(patsubst $(testSrcDir)/%.c,$(testObjectDir)/%.o,$(testSources))

$(info -------------------------)
$(info test sources and objects:)
$(info $(testSources))
$(info $(testObjects))
$(info -------------------------)

$(testObjectDir)/%.o: $(testSrcDir)/%.c
	$(CC) -c -I$(buildDir)/include $< -o $@

testExecutable: $(testObjects)
	$(CC) -I$(buildDir)/include -L./$(buildDir) -lFunC $(testObjects) -o testExecutable

test: build testExecutable
	echo "testing started ..."
	./testExecutable
	echo "testing done!"

.PHONY: clean

clean:
	rm -f $(objectDir)/*
	rm -f $(testObjectDir)/*
	rm -f $(buildDir)/*.so
	rm -f $(buildDir)/include/*.h
