#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]) 
{
   FILE *f = fopen("soubor.txt", "r");
   if (f == NULL) {
      int r = errno;
      printf("Open file failed errno value %d\n", errno); 
      printf("String error '%s'\n", strerror(r));
   }
   return 0;
}
