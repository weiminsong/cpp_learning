#include <stdio.h>
#include <stdlib.h>
#include <cstring>
using namespace std;

int main () {
   char *str;

   /* Initial memory allocation */
   str = (char *) malloc(15);
   int a = strlen(str);
   strcpy(str, "tutorialspoint");
   printf("String = %s,  Address = %u\n", str, str);

   ///* Reallocating memory */
   //str = (char *) realloc(str, 25);
   //strcat(str, ".com");
   //printf("String = %s,  Address = %u\n", str, str);

   free(str);
   
   return(0);
}
