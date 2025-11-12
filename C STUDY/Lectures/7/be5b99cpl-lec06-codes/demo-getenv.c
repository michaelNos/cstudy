#include <stdio.h>
#include <stdlib.h>

int main(void)
{
   printf("USER: %s\n", getenv("USER"));
   printf("HOME: %s\n", getenv("HOME"));
   return EXIT_SUCCESS;
}
