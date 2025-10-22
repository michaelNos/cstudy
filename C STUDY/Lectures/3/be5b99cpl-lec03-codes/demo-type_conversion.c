#include <stdio.h>

// d = 1000000000000000019884624838656.000000
// i = -2147483648
// l = 5000000000
// i = 705032704

int main(void)
{
   {
      double d = 1e30;
      int i = (int)d;

      printf("d = %lf\n", d);
      printf("i = %i\n", i);
   }

   {
      long l = 5000000000L;
      int i = (int)l;

      printf("l = %li\n", l);
      printf("i = %i\n", i);
   }

   return 0;
}
