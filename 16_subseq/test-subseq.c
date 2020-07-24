#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

int main(int argc, char *argv[])
{
  int array1[] = { 1, 2, 1, 3, 5, 7, 2, 4, 6, 9};
  int array2[] = { -5, -4, -3, -2, -1, 0, 1 };
  int array3[] = { 1, 0 };
  int array4[] = { 10 };
  int array5[] = {};
  int array6[] = { 0, 0, 0, 0 , 0 };
  int array7[] = { 0, -1, -2, -3, -4, -5, -6, -7, -8, -9 };


  if (maxSeq(array1, 10) != 4){
    exit(EXIT_FAILURE);
  }
  else if (maxSeq(array2, 7) != 7) {
    exit(EXIT_FAILURE);
  }
  else if (maxSeq(array3, 2) != 1) {
    exit(EXIT_FAILURE);
  }
  else if (maxSeq(array4, 1) != 1) {
    exit(EXIT_FAILURE);
  }
  else if (maxSeq(array5, 0) != 0) {
    exit(EXIT_FAILURE);
  }
  else if (maxSeq(array6, 5) != 1) {
    exit(EXIT_FAILURE);
  }
  else if (maxSeq(array7, 10) != 1) {
    exit(EXIT_FAILURE);
  }
  else{
    printf("All tests passed\n");
    exit(EXIT_SUCCESS);
  }
}
