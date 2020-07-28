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

int main(int argc, char** argv){
  if( argc !=2){ fprintf(stderr, "ERROR! wrong number of argument\n");
    return EXIT_FAILURE;
  }
  FILE * f=fopen(argv[1], "r");
  if(f==NULL){ fprintf(stderr, "the file couldn't open\n");
    return EXIT_FAILURE;
  }
  char matrix[10][10];
  char c_line[12];
  int line_count =0;
  while( (fgets(c_line, 12, f))!=NULL){
    if(strchr(c_line, '\n')==NULL){
      fprintf(stderr, "This line is too long\n");
      return EXIT_FAILURE;
    }
    if(strlen(c_line)!=11){
      fprintf(stderr,"THIS LINE IS TOO SHORT\n");
      return EXIT_FAILURE;
    }
    for(int i=0; i<10; i++){
      matrix[line_count][i] = c_line[i];
    }
    line_count++;
  }
  if(line_count != 10){
    fprintf(stderr, "ERROR! we have %d  line(s)\n", line_count);
    return EXIT_FAILURE;
  }
  rotate(matrix);
  for(int i=0; i<10; i++){
    for(int j=0; j<10; j++){
      fprintf(stdout,"%c", matrix[i][j]);
    }
    fprintf(stdout, "\n");
  }
  if(fclose(f)!=0){
    fprintf(stderr, " The file is not closed\n");
  }
  return EXIT_SUCCESS;
}
