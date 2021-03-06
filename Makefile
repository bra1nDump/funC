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
CC = gcc

.DEFAULT_GOAL := funC

###########################################################################################
# funC lib
###########################################################################################

funCLib = build/libFunC.so

objectDir = src/obj

# include = $(shell echo include/*.h)
sources = $(shell echo src/*.c)
objects = $(patsubst src/%.c,$(objectDir)/%.o,$(sources))

 # fpic - posistion independent code
$(objectDir)/%.o: src/%.c | $(objectDir)
	$(CC) -fpic -Wall -O0 -g -Iinclude -c -o $@ $<

$(objectDir):
	mkdir $@

# -shared to create a shared library
funC: $(objects) | build
	$(CC) $(objects) -o $(funCLib) -shared

build:
	mkdir build

#############################################################################################
# funC lib tests
#############################################################################################

linkerFlags = '-Wl,-rpath,$$ORIGIN/../build' -Lbuild # the -L flag is for compile time linking and rpath is
# for resolving library at runtime

testSources = $(shell echo test/*.c)
testExecutables = $(patsubst test/%.c,bin/%,$(testSources))

bin/%: test/%.c | bin
	$(CC) $(linkerFlags) -Iinclude -lFunC  $< -o $@

bin:
	mkdir bin

test: funC $(testExecutables)
	$(info testing started ...)
	$(foreach testBinary,$(testExecutables),$(testBinary))
	$(info testing completed :D)

.PHONY: clean

clean:
	rm -fr $(objectDir)
	rm -f bin/*
	rm -f build/*.so
