#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cleanup(void);
void last_word(void);

int main(void)
{
   atexit(cleanup); // register function
   atexit(last_word); // register function
   const char *howToExit = getenv("HOW_TO_EXIT");
   if (howToExit && strcmp(howToExit, "EXIT") == 0) {
      printf("Force exit\n");
      exit(EXIT_FAILURE);
   } else if (howToExit && strcmp(howToExit, "ABORT") == 0) {
      printf("Force abort\n");
      abort();
   }
   printf("Normal exit\n");
   return EXIT_SUCCESS;
}

void cleanup(void)
{
   printf("Perform cleanup at the program exit!\n");
}

void last_word(void)
{
   printf("Bye, bye!\n");
}
