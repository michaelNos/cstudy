#include <stdio.h>

int main(void)
{
   int array[5] = {0, 1, 2, 3, 4};

   printf("Size of array: %lu\n", sizeof(array));
   for (int i = 0; i < 5; ++i) {
      printf("Item[%i] = %i\n", i, array[i]);
   }
   return 0;
}

// Size of array: 20
// Item[0] = 0
// Item[1] = 1
// Item[2] = 2
// Item[3] = 3
// Item[4] = 4