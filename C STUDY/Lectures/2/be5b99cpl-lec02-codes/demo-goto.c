#include <stdio.h>

// i-j: 0-0
// i-j: 0-1
// i-j: 1-0
// i-j: 1-1
// i-j: 2-0
// i-j: 2-1

// Break outer loop
// i-j: 0-0
// i-j: 0-1
// i-j: 0-2

int main(void)
{
   for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
         printf("i-j: %i-%i\n", i, j);
         if (j == 1) {
            break;
         }
      }
   }
   printf("\nBreak outer loop\n");

   for (int i = 0; i < 5; ++i) {
      for (int j = 0; j < 3; ++j) {
         printf("i-j: %i-%i\n", i, j);
         if (j == 2) {
            goto outer;
         }
      }
   }
outer:

   return 0;
}
