#include <stdio.h>

int main(int argc, char *argv[]) 
{
   int ret = 0;

   fprintf(stdout, "Program has been called as %s\n", argv[0]);

   if (argc > 1) {
      fprintf(stdout, "1st argument is %s\n", argv[1]);
   } else {
      fprintf(stdout, "1st argument is not given\n");
      fprintf(stderr, "At least one argument must be given!\n");
      ret = -1;
   }
   return ret;
}
