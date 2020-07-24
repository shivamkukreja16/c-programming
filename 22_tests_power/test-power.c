#include <stdio.h>
#include <stdlib.h>
#include <math.h>

unsigned power(unsigned x, unsigned y);

void check(unsigned x, unsigned y, unsigned expected_ans){
  if( power(x,y) != expected_ans){
    printf("this program is broken\n");
    exit(EXIT_FAILURE);
  }
}
int main(){
  check(0,0,1);
  check(1000,0,1);
  check(4,0,1);
  check(0,100,0);
  check(2,3,8);
  check(15,3,3375);
  check(56,1,56);
  check(1,16894,1);
  check(0,1,0);
  check(1,0,1);
  check(111176,0,1);
  check(03,2,9);
  check(2,02,4);
  check(1,1,1);
  check(9,10,3486784401);
  check(3,10,59049);
  return EXIT_SUCCESS;
}
 
