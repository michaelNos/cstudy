#include <stdio.h>

int main(void) 
{
   char str0[4] = "CPL"; // 1 char for \0
   char str1[5]; // +1 char for \0
   printf("String str0 = '%s'\n", str0);
   printf("Enter 4 chars: ");
   scanf("%4s", str1);
   printf("You entered string '%s'\n", str1);
   printf("String str0 = '%s'\n", str0);
   return 0;
}
