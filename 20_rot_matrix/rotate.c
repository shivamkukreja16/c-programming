#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void rotate( char matrix[10][10]){
  if(matrix != NULL){
    char matrix_copy[10][10];
    for(int i=0; i<10; i++){
      for(int j=0; j<10; j++){
	matrix_copy[i][j] = matrix[i][j];
      }
    }
    for(int i=0; i<10; i++){
      for(int j=0; j<10; j++){
	matrix[j][10-i-1] = matrix_copy[i][j];
      }
    }
  }
}
