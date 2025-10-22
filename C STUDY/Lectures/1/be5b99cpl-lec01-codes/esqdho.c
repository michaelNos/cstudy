#include <stdio.h>

int main(void) 
{
   int i = 'a';
   int h = 0x61;
   int o = 0141;

   printf("i: %i h: %i o: %i c: %c\n", i, h, o, i);
   printf("oct: \141 hex: \x61\n");
   return 0;
}
