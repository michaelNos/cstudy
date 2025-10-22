#include <stdio.h>

int main(void) 
{
   int a = 10;
   printf("%lu %lu\n", sizeof(a), sizeof(a + 1.0));
   return 0;
}
