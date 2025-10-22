#include <stdio.h>

int main(void) 
{
   unsigned char uc = 127;
   char su = 127;

   printf("The value of uc=%i and su=%i\n", uc, su);
   uc = uc + 2; 
   su = su + 2;
   printf("The value of uc=%i and su=%i\n", uc, su);

   return 0;
}

// The value of uc=127 and su=127
// The value of uc=129 and su=-127