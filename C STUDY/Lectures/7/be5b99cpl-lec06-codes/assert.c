#include <stdio.h>
#include <assert.h>

int main(int argc, char *argv[]) 
{
   assert(argc > 1);
   printf("program argc: %d\n", argc);
   return 0;
}
