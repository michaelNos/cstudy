#include <stdio.h>
#include <ctype.h>

#include <string.h> // for strcmp()

#include <stdlib.h> // for system()

#include <termios.h> 
#include <unistd.h>  // for STDIN_FILENO


void call_stty(int reset);
void call_termios(int reset);

int main(int argc, char *argv[])
{
   void (*set)(int reset) = 0;

   if (argc > 1) {
      if (strcmp(argv[1], "stty") == 0) {
         printf("Call stty to put stdin to raw mode\n");
         set = call_stty;
      } else if (strcmp(argv[1], "termios") == 0) {
         printf("Call termios to put stdin to raw mode\n");
         set = call_termios;
      }
   }
   int c;
   if (set) {
      (*set)(0);
   }
   while ((c = getchar()) != 'q') {
      if (isalpha(c)) {
         printf("Key '%c' is alphabetic letter;", c);
      } else if (isspace(c)) {
         printf("Key '%c' is space character;", c);
      } else if (isdigit(c)) {
         printf("Key '%c' is decimal digit;", c);
      } else if (isblank(c)) {
         printf("Key is blank;");
      } else {
         printf("Key is something else;");
      }
      printf(" ascii: %s\n", isascii(c) ? "true" : "false");
   }
   if (set) {
      (*set)(1); //revert to the original mode
   }
   return 0;
}

void call_stty(int reset) 
{
   if (reset) {
      system("stty -raw echo");
   } else {
      system("stty raw -echo");
   }
}

void call_termios(int reset)
{
   static struct termios tio, tioOld;
   tcgetattr(STDIN_FILENO, &tio);
   if (reset) {
      tcsetattr(STDIN_FILENO, TCSANOW, &tioOld);
   } else {
      tioOld = tio; //backup 
      cfmakeraw(&tio);
      tio.c_lflag &= ~ECHO; // assure echo is disabled
      tio.c_oflag |= OPOST; // enable output postprocessing
      tcsetattr(STDIN_FILENO, TCSANOW, &tio);
   }
}
