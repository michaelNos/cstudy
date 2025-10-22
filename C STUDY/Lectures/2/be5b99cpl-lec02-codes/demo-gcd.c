#include <stdio.h>

int getGreatestCommonDivisor(int x, int y) 
{
   int d = x < y ? x : y;
   while ( (x % d != 0) || (y % d != 0) ) {
      d = d - 1;
   }
   return d;
} 

int main(void)
{
   int x = 6;
   int y = 15;
   int d = getGreatestCommonDivisor(x, y);
   printf("Greatest common divisor of %i and %i is %i\n", x, y, d);
   return 0;
}
