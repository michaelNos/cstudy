#include <stdio.h>

int main(void)
{
   int m[3][3] = { { 1, 2, 3 }, { 4, 5, 6}, { 7, 8, 9 } };

   printf("Size of m: %lu == %lu\n", sizeof(m), 3*3*sizeof(int));

   for (int r = 0; r < 3; ++r) {
      for (int c = 0; c < 3; ++c) {
         printf("%3i", m[r][c]);
      }
      printf("\n");
   }

   int *pm = (int *)m;
   printf("m[0][0]=%i m[1][0]=%i\n", m[0][0], m[1][0]);
   printf("pm[0]=%i pm[3]=%i\n", m[0][0], m[1][0]);

   int (*p)[3] = m; // pointer to array of int

   printf("Size of p: %lu\n", sizeof(p));
   printf("Size of *p: %lu\n", sizeof(*p)); // 3 * sizeof(int) = 12

   return 0;
}

// Size of m: 36 == 36
//   1  2  3
//   4  5  6
//   7  8  9
// m[0][0]=1 m[1][0]=4
// pm[0]=1 pm[3]=4
// Size of p: 8
// Size of *p: 12
