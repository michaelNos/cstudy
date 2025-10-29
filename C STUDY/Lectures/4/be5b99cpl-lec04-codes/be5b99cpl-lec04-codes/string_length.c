#include <stdio.h>
#include <string.h>

int getLength(char *str)
{
   int ret = 0;
   while (str && (*str++) != '\0') {
      ret++;
   }
   return ret;
}

int main(int argc, char *argv[]) 
{
   for (int i = 0; i < argc; ++i) {
      printf("argv[%i]: getLength = %i -- strlen = %lu\n", i, getLength(argv[i]), strlen(argv[i]));
   }
   return 0;
}

// nosmikah@pc124kp124:~/Desktop/CSTUDY/cstudy/C STUDY/Lectures/4/be5b99cpl-lec04-codes/be5b99cpl-lec04-codes$ clang string_length.c && ./a.out sdda
// argv[0]: getLength = 7 -- strlen = 7
// argv[1]: getLength = 4 -- strlen = 4