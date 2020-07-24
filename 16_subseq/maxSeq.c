#include <stdio.h>

size_t maxSeq(int * array, size_t n) {

  size_t max_len = 1, count = 1;

  if (n == 0 || n == 1) {
    return n;
  }

  for (size_t i = 0; i < n-1; i++) {
    if (array[i+1] > array[i]) {
      count++;
      if (count >= max_len) {
	max_len = count;
      }
    }
    else{
      count = 1;
    }  
  }
  return max_len;
}
