# cheat sheet

# $@ - left side of the rule
# $< - first item in the dependency list
# % - match any number of characters (also is bound to 
#     what ever it matched in the following commands)
# $(var:.suffix=.newSuffix) - replace suffix
# $(patsubst pattern,replacement,inText)

# gcc options
# -I<headers directory>
# -L<shared libraries directory>

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

funC: $(funCLib) copyHeaders

#############################################################################################
# tests (this includes building the lab0 executable)
testSrcDir = test
testExecutableDir = bin

testSources = $(shell echo $(testSrcDir)/*.c)
testExecutables = $(patsubst $(testSrcDir)/%.c,$(testExecutableDir)/%,$(testSources))

$(testExecutableDir)/%: $(testSrcDir)/%.c
	$(CC) -I$(buildDir)/include -L$(buildDir) -lFunC $< -o $@

test: funC $(testExecutables)
	$(info testing started ...)
	$(foreach testBinary,$(testExecutables),$(testBinary))
	$(info testing completed :D)

#############################################################################################
# lab 0

# dont forget to add -Wextra
.DEFAULT_GOAL := lab

lab0SrcDir = lab0

lab: funC $(lab0SrcDir)/lab0.c
	$(CC) -I$(buildDir)/include -L$(buildDir) -lFunC $(lab0SrcDir)/lab0.c -o $(lab0SrcDir)/lab0

.PHONY: clean

clean:
	rm -f $(objectDir)/*
	rm -f $(testExecutableDir)/*
	rm -f $(buildDir)/*.so
	rm -f $(buildDir)/include/*.h

	rm -f $(lab0SrcDir)/lab0
