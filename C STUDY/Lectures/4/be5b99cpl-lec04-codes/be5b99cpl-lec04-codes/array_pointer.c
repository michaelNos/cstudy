#include <stdio.h>

int main(void)
{
   int a[] = {1, 2, 3, 4};
   int b[] = {[3] = 10, [1] = 1, [2] = 5, [0] = 0};

   // b = a; It is not possible to assign arrays
   for (int i = 0; i < 4; ++i) {
      printf("a[%i] =%3i   b[%i] =%3i\n", i, a[i], i, b[i]);
   }

   int *p = a; 
   a[2] = 99;

   printf("\nPrint content of the array 'a' using pointer arithmetic\n");
   for (int i = 0; i < 4; ++i) {
      printf("a[%i] =%3i   p+%i =%3i\n", i, a[i], i, *(p+i));
   }

   return 0;
}

// a[0] =  1   b[0] =  0
// a[1] =  2   b[1] =  1
// a[2] =  3   b[2] =  5
// a[3] =  4   b[3] = 10

// Print content of the array 'a' using pointer arithmetic
// a[0] =  1   p+0 =  1
// a[1] =  2   p+1 =  2
// a[2] = 99   p+2 = 99
// a[3] =  4   p+3 =  4
