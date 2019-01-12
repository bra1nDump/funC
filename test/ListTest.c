#include <stdio.h>
#include <stdlib.h>
#include "Core.h"
#include "List.h"

// test
void printInt(void* x) {
  int* xInt = (int*) x;
  printf("%d\n", *xInt);
}

void testEmptyConsMap_() {
  list* list1 = List.empty();

  for (int i = 0; i < 10; i += 1) {
    list1 = List.cons(sizeof(i), &i, list1);
  }

  List.map_(printInt, list1);
}

// test
// contents type -> boxed type
box square(void* x) {
  int xInt = *((int*) x);
  int newContents = xInt * xInt;
  box newBox = Box.box(sizeof(int), &newContents);

  return newBox;
}

void testMap() {
  list* list1 = List.empty();

  for (int i = 10; i >= 0; i -= 1) {
    list1 = List.cons(sizeof(i), &i, list1);
  }

  list* newList;
  newList = List.map(square, list1);
  List.map_(printInt, newList);

  List.free(list1);
  List.free(newList);
}

// test
typedef struct {
  int first;
  int second;
} tuple;

tuple initTuple(int first, int second) {
  tuple x;
  x.first = first;
  x.second = second;
  return x;
}

box toTuple(void* x) {
  int contents = *((int*) x);
  tuple newContents = initTuple(contents, contents + 1);
  return Box.box(sizeof(tuple), &newContents);
}

void tuplePrint(void* x) {
  tuple* tuplePointer = (tuple*) x;
  printf("%d %d\n", tuplePointer->first, tuplePointer->second);
}

void testMapIntToTuplePrint() {
  List.map_
    ( tuplePrint
      , List.map
      ( toTuple
	, List.integerRange(1, 10)));
}

void testIntegerRange() {
  List.map_
    ( printInt
      , List.integerRange(55, 60));
}

void testFromCArray() {
  
}

// test suite
int main () {
  testIntegerRange();
  testEmptyConsMap_();
  testMap();
  testMapIntToTuplePrint();

  return 0;
}
