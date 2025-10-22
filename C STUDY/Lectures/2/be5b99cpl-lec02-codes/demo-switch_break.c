#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
   const int part = argc > 1 ? atoi(argv[1]) : -1;
   switch(part) {
      case 1:
         printf("Branch 1\n");
         break;
      case 2:
         printf("Branch 2\n");
      case 3:
         printf("Branch 3\n");
         break;
      case 4:
         printf("Branch 4\n");
         break;
      default:
         printf("Default branch\n");
         break;
   }
   return 0;
}
