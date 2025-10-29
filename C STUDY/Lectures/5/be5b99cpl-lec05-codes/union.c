#include <stdio.h>

int main(int argc, char *argv[])
{
   union Numbers {
      char c;
      int i;
      double d;
   };

   printf("size of char %lu\n", sizeof(char));
   printf("size of int %lu\n", sizeof(int ));
   printf("size of double %lu\n", sizeof(double));
   printf("size of Numbers %lu\n", sizeof(union Numbers));

   union Numbers numbers;

   printf("Numbers c: %d i: %d d: %lf\n", numbers.c, numbers.i, numbers.d);

   numbers.c = 'a';
   numbers.i = 5;
   numbers.d = 3.14;
   printf("Set the numbers to 'a', 5, and 3.14\n");
   printf("Numbers c: %d i: %d d: %lf\n", numbers.c, numbers.i, numbers.d);

   numbers.c = 'a';
   printf("\nSet the numbers.c to 'a'\n");
   printf("Numbers c: %d i: %d d: %lf\n", numbers.c, numbers.i, numbers.d);

   numbers.i = 5;
   printf("\nSet the numbers.i to 5\n");
   printf("Numbers c: %d i: %d d: %lf\n", numbers.c, numbers.i, numbers.d);

   numbers.d = 3.14;
   printf("\nSet the numbers.d to 3.14\n");
   printf("Numbers c: %d i: %d d: %lf\n", numbers.c, numbers.i, numbers.d);
   return 0;
}

// size of char 1
// size of int 4
// size of double 8
// size of Numbers 8
// Numbers c: 100 i: 100 d: 0.000000
// Set the numbers to 'a', 5, and 3.14
// Numbers c: 31 i: 1374389535 d: 3.140000

// Set the numbers.c to 'a'
// Numbers c: 97 i: 1374389601 d: 3.140000

// Set the numbers.i to 5
// Numbers c: 5 i: 5 d: 3.139999

// Set the numbers.d to 3.14
// Numbers c: 31 i: 1374389535 d: 3.140000