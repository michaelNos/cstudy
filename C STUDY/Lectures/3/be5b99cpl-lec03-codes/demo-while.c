#include <stdio.h>

// x: 10 y: 3 q(while)= 1; q(dowhile)= 1
// x: 2 y: 3 q(while)= 2; q(dowhile)= -1

int make_while(int x, int y);
int make_dowhile(int x, int y);

int main(void)
{
   int x = 10; 
   int y = 3;

   printf("x: %i y: %i q(while)= %i; q(dowhile)= %i\n", x, y, make_while(x, y), make_dowhile(x, y));

   x = 2; y = 3;
   printf("x: %i y: %i q(while)= %i; q(dowhile)= %i\n", x, y, make_while(x, y), make_dowhile(x, y));

   return 0;
}

int make_while(int x, int y)
{ 
   int q = x;
   while (q >= y) {
      q = q - y;
   }
   return q;
}

int make_dowhile(int x, int y)
{
   int q = x;
   do {
      q = q - y;
   } while (q >= y);
   return q;
}
