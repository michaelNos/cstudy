#include <stdio.h>

int main(int argc, char *argv[]) 
{
   int c;
   int i;
   int j;

   i = j = 10;
   if ((c = 5) == 5) {
      fprintf(stdout, "c is 5 \n");
   } else {
      fprintf(stdout, "c is not 5\n");
   }
   return 0;
}
