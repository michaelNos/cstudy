#include <stdio.h>
#include <stdarg.h>

int even_numbers(int n, ...);
int main(void)
{
   printf("Number of even numbers: %i\n", even_numbers(2, 1, 2));
   printf("Number of even numbers: %i\n", even_numbers(4, 1, 3, 4, 5));
   printf("Number of even numbers: %i\n", even_numbers(3, 2, 4, 6));
   return 0;
}

int even_numbers(int n, ...)
{
   int c = 0;
   va_list ap;
   va_start(ap, n);
   for (int i = 0; i < n; ++i) {
      int v = va_arg(ap, int);
      (v % 2 == 0) ? c += 1 : 0;
   }
   va_end(ap);
   return c;
}
