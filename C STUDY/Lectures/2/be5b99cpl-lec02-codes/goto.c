#include <stdio.h>

int main(void)
{
   int test = 3;
   for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 5; ++j) {
         if (j == test) {
            goto loop_out;
         }
         fprintf(stdout, "Loop i: %d j: %d\n", i, j);
      }
   }
   return 0;
loop_out:
   fprintf(stdout, "After loop\n");
   return -1;
}
