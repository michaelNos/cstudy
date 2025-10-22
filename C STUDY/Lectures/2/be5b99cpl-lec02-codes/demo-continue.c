#include <stdio.h>

int main(void)
{
   for (int i = 0; i < 10; ++i) {
      printf("i: %i ", i);
      if (i % 3 != 0) {
         continue;
      }
      printf("\n");
   }
   return 0;
}
