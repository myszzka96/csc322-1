#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_LENGTH 100

typedef char String[STRING_LENGTH];
int main(void) {

   String input;

   while (fgets(input, 100, stdin) != NULL) {
      if ( (strstr(input, "//") != NULL) ) {
         puts(input);
      } else if ( (strstr(input, "/*") != NULL) ) {
         puts(input);
      } else if ( (strstr(input, "*\\") != NULL) ) {
         puts(input);
      }
   }
   return(EXIT_SUCCESS);
}
