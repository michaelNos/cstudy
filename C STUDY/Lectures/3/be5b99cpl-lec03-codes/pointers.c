#include <stdio.h>

// i: 10 -- pi: 0x7ffd5e3d47a8
// &i: 0x7ffd5e3d47a8 -- *pi: 10
// *(&)i: 10 -- &(*pi): 0x7ffd5e3d47a8

// i: 10 -- *pj: 10
// i: 20 -- *pj: 20

// sizeof(i): 4
// sizeof(pi): 8
// l: 0x7ffd5e3d47a8 0x7ffd5e3d47a8
// l: 0xa 0xa

int main(void)
{
   int i = 10;
   int *pi;
   int *pj = &i; /* pj points to the address of i */

   pi = &i;
   int b;

   b = *pi;

   printf("i: %d -- pi: %p\n", i, pi);
   printf("&i: %p -- *pi: %d\n", &i, *pi);
   printf("*(&)i: %d -- &(*pi): %p\n", *(&i), &(*pi));

   puts("");
   printf("i: %d -- *pj: %d\n", i, *pj);
   i = 20;
   printf("i: %d -- *pj: %d\n", i, *pj);

   puts("");

   printf("sizeof(i): %lu\n", sizeof(i));
   printf("sizeof(pi): %lu\n", sizeof(pi));

   long l = (long)pi;
   printf("l: 0x%lx %p\n", l, pi); /* print l as hex */

   l = 10;
   pi = (int*)l; /* possible it is but nonsense */
   printf("l: 0x%lx %p\n", l, pi); /* print l as hex */
   return 0;
}
