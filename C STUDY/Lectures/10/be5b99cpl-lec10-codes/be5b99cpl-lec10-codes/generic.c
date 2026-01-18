#include <stdio.h>
#include <stdlib.h>

double f_i(int i) 
{
   return i + 1.0;
}

double f_d(double d)
{
   return d - 1.0;
}

#define fce(X) _Generic((X),\
int: f_i,\
double: f_d\
)(X)

int main(void)
{
   int i = 10;
   double d = 10.0;

   printf("i = %d; d = %f\n", i, d);
   printf("Results of fce(i) %f\n", fce(i));
   printf("Results of fce(d) %f\n", fce(d));
   return EXIT_SUCCESS;
}
