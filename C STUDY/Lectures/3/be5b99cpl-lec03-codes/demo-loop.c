#include <stdio.h>

int main(void)
{
   double n = 10.0/ 3.0;
   double i = 0;
   while (i != n) {
      printf("i: %f n: %f\n", i, n);
      i++;
   }
   return 0;
}
