#include <stdio.h>

int main(void)
{
   int i, n;
   printf("Enter number of integers to be read: ");
   scanf("%d", &n);

   int a[n]; /* variable length array */
   for (i = 0; i < n; ++i) {
      scanf("%d", &a[i]);
   }
   printf("Entered numbers in reverse order: ");
   for (i = n - 1; i >= 0; --i) {
      printf(" %d", a[i]);
   }
   printf("\n");
   return 0;
}
