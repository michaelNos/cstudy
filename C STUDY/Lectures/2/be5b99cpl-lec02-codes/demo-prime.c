#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

_Bool isPrimeNumber(int n) 
{
   _Bool ret = true;
   const int maxBound = (int)sqrt((double)n);
   for (int i = 2; i <= maxBound; ++i) {
      if (n % i == 0) {
         ret = false;
         break;
      }
   }
   return ret;
}

int main(int argc, char *argv[]) 
{
   int number = argc > 1 ? atoi(argv[1]) : 14;
   printf("Number %i is%s primer number\n", number, isPrimeNumber(number) ? "" : " not");
   return 0;
}
