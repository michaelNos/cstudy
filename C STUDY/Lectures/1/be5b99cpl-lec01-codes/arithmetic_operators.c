#include <stdio.h>

int main(void)
{
   int a = 10;
   int b = 3;
   int c = 4;
   int d = 5;
   int result;

   result = a - b; // difference
   printf("a - b = %i\n", result);

   result = a * b; // multiplication
   printf("a * b = %i\n", result);

   result = a / b; // integer division 
   printf("a / b = %i\n", result);

   result = a + b * c; // priority of the operators
   printf("a + b * c = %i\n", result);

   printf("a * b + c * d = %i\n", a * b + c * d);
   printf("(a * b) + (c * d) = %i\n", (a * b) + (c * d));
   printf("a * (b + c) * d = %i\n", a * (b + c) * d);

   return 0;
}
