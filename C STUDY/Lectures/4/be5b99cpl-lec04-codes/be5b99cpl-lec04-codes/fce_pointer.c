#include <stdio.h>

void fce(int n, int *array)
{
   int local_array[] = {2, 4, 6};
   printf("sizeof(array) = %lu, n = %i -- sizeof(local_array) = %lu\n",
         sizeof(array), n, sizeof(local_array));
   for (int i = 0; i < 3 && i < n; ++i) {
      printf("array[%i]=%i local_array[%i]=%i\n", i, array[i], i, local_array[i]);
   }
}

int main(void)
{
   int array[] = {1, 2, 3};
   fce(sizeof(array)/sizeof(int), array);

   return 0;
}
