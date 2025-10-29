#include <stdio.h>

int main(void)
{
   char str1[] = "BE5B99CPL";
   char *str2 = "BE5B99CPL";

   printf("str1 \"%s\"\n", str1);
   printf("str2 \"%s\"\n", str2);

   printf("size of str1 %lu\n", sizeof(str1));
   printf("size of str2 %lu\n", sizeof(str2));

   return 0;

}

// str1 "BE5B99CPL"
// str2 "BE5B99CPL"
// size of str1 10
// size of str2 8