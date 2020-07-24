#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char * str) {
   /*
   * Thisfunction reverses the string passed to it.
   * This function doesn't return anything.
   * Modifies the string passed into it in place.
   */

  // Check for NULL argument
  if( str != NULL ){
    //length of string
    size_t len = strlen(str);
    if (len != 0){
      char str_copy[len];
      // Copy string from str to str_copy
      strcpy(str_copy, str);
      for(size_t i = 0; i < len; i++) {
	str[i] = str_copy[len-i-1];
      }
    }
    else{
      // empty string
      str = "";
    }
  }  
}

int main(void) {
  char str0[] = "";
  char str1[] = "123";
  char str2[] = "abcd";
  char str3[] = "Captain's log, Stardate 42523.7";
  char str4[] = "Hello, my name is Inigo Montoya.";
  char str5[] = "You can be my wingman anyday!";
  char str6[] = "Executor Selendis! Unleash the full power of your forces! There may be no tomorrow!";
  char * array[] = {str0, str1, str2, str3, str4, str5, str6};
  for (int i = 0; i < 7; i++) {
    reverse(array[i]);
    printf("%s\n", array[i]);
  }
  return EXIT_SUCCESS;
}
