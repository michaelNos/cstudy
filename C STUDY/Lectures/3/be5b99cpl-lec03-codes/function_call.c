#include <stdio.h>

void fce(int a, char *b)
{
   a += 1;
   (*b)++;
}

int main(void)
{
   int a = 10;
   char b = 'A';

   printf("Before call a: %d b: %c\n", a, b);
   fce(a, &b);
   printf("After call a: %d b: %c\n", a, b);
   fce(a, &b);
   printf("After call a: %d b: %c\n", a, b);

   return 0;
}

// Before call a: 10 b: A
// After call a: 10 b: B
// After call a: 10 b: C