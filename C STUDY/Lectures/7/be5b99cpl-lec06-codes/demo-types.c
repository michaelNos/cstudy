#include <stdio.h>

int main(void)
{
   double values[] = { 1000, 1e5, 1e20, 1e30 };

   for (int v = 0; v < sizeof(values)/sizeof(double); ++v) {
      printf("\nShow representations of the double value %lf and its conversion to short and int\n");
      double d = values[v];
      short sd = (short)d;
      int id = (int)d;

      printf(" d: %lf\n", d);
      printf("sd: %u\n", sd);
      printf("id: %u\n", id);

      char *p = (char*)&d;
      printf(" d (hex): ");
      for (int i = 0; i < sizeof(double); ++i) {
         printf(" %02x", *(p++) & 0xff); // for varargs, arguments smaller than int are promoted to int
      }
      printf("\n");

      p = (char*)&sd;
      printf("sd (hex): ");
      for (int i = 0; i < sizeof(short); ++i) {
         printf(" %02x", *(p++) & 0xff); // for varargs, arguments smaller than int are promoted to int
      }
      printf("\n");

      p = (char*)&id;
      printf("id (hex): ");
      for (int i = 0; i < sizeof(int); ++i) {
         printf(" %02x", *(p++) & 0xff); // for varargs, arguments smaller than int are promoted to int
      }
      printf("\n");
   }
   return 0;
}
