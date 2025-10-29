#include <stdio.h>

int main(void)
{
   int array[10];

   for (int i = 0; i < 10; i++) {
      array[i] = i;
   }

   int n = 5;
   int array2[n * 2];

   for (int i = 0; i < 10; i++) {
      array2[i] = 3 * i - 2 * i * i;
   }

   printf("Size of array: %lu\n", sizeof(array));
   for (int i = 0; i < 10; ++i) {
      printf("array[%i]=%+2i \t array2[%i]=%6i\n", i, array[i], i, array2[i]);
   }
   return 0;
}

// Size of array: 40
// array[0]=+0      array2[0]=     0
// array[1]=+1      array2[1]=     1
// array[2]=+2      array2[2]=    -2
// array[3]=+3      array2[3]=    -9
// array[4]=+4      array2[4]=   -20
// array[5]=+5      array2[5]=   -35
// array[6]=+6      array2[6]=   -54
// array[7]=+7      array2[7]=   -77
// array[8]=+8      array2[8]=  -104
// array[9]=+9      array2[9]=  -135