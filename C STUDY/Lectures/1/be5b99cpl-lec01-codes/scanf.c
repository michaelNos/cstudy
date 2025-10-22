#include <stdio.h>

int main(void)
{
   int i;
   double d;

   printf("Enter int value: ");
   scanf("%i", &i); /* operator & return address of the variable i */


   printf("Enter a double value: ");
   scanf("%lf", &d);
   printf("You entered %02i and %0.1f\n", i, d);

   return 0;
}
