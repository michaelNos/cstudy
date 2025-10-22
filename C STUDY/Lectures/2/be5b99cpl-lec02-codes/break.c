#include <stdio.h>

// End of the while loop i: 9
// End of the while loop i: 8
// End of the while loop i: 7
// End of the while loop i: 6
// End of the while loop i: 5
// i reaches 5, leave the loop

int main(void)
{
   int i = 10;
   while (i > 0) {
      if (i == 5) {
         printf("i reaches 5, leave the loop\n");
         break;
      }
      i--;
      printf("End of the while loop i: %d\n", i);
   }
   return 0;
}
