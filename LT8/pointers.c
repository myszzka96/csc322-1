#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define ARRAY_SIZE 5

typedef int *IntPtr;
typedef int IntArray[ARRAY_SIZE];
typedef int *PtrArray[ARRAY_SIZE];

void initializeFunction (IntArray MyIntArray, PtrArray PointerArray){

  int index;
  srand(getpid());

  for(index = 0;  index < ARRAY_SIZE; index++) {
    MyIntArray[index] = rand();
  }

  for(index = 0;index < ARRAY_SIZE;index++){
    PointerArray[index] = &MyIntArray[index];
  }
}

void printArray (IntArray MyIntArray) {

  int index;

  for(index = 0; index < ARRAY_SIZE; index++) {
    printf("%d :  %d \n",index, MyIntArray[index]);
  }
}

void printPointerArray (PtrArray PointerArray) {

  int index;

  for(index = 0; index < ARRAY_SIZE; index++) {
    printf("%d :  %d \n",index, *PointerArray[index]);
  }
}

void bubbleSortInteger (IntArray MyIntArray) {

  int temp;
  int index;
  int iter;

  for(iter = 0; iter < ARRAY_SIZE; iter++) {
    for(index = 0; index < ARRAY_SIZE-1; index++) {
      if(*(MyIntArray+index) > *(MyIntArray+(index+1))) {
        temp = *(MyIntArray+index);
        *(MyIntArray+index) = *(MyIntArray+(index+1));
        *(MyIntArray+(index+1)) = temp;
      }
    }
  }
}

void bubbleSortPointer (PtrArray PointerArray) {

  IntPtr temp;
  int index;
  int iter;

  for(iter = 0; iter < ARRAY_SIZE; iter++) {
    for(index = 0; index < ARRAY_SIZE-1; index++) {
      if(*PointerArray[index] > *PointerArray[index+1]) {
        temp = PointerArray[index];
        PointerArray[index] = PointerArray[index+1];
        PointerArray[index+1] = temp;
      }
    }
  }
}

int main(void) {

  IntArray MyIntArray;
  PtrArray PointerArray;

  initializeFunction (MyIntArray,PointerArray);
  printf("---- Initialized array of integers ----\n");
  printArray (MyIntArray);
  bubbleSortPointer (PointerArray);
  printf("---- Sorted array of pointers ----\n");
  printPointerArray (PointerArray);
  bubbleSortInteger (MyIntArray);
  printf("---- Sorted array of integers ----\n");
  printArray (MyIntArray);
  printf("---- Array of pointers ----\n");
  printPointerArray (PointerArray);

  return(EXIT_SUCCESS);
}

