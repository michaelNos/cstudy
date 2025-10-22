#include <stdio.h>

int main(void) 
{
   unsigned char uc = 127;
   char su = 127;

   printf("The value of uc=%hhu and su=%hhi\n", uc, su);
   uc = uc + 2; 
   su = su + 2;
   printf("The value of uc=%hhu and su=%hhi\n", uc, su);

   return 0;
}
