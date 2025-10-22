#include <stdio.h>

// P1 = (1, 2.235700)
// P1 = (1, 2)
// P1 = (1.000000, 2.235700)
// P1 = (1.000, 2.236)
// P2 = (2.534300, 2.000000)
// (P1 - P2)=(-1.534, 0.236)
// |P1 - P2|^2=2.41

int main(void)
{
   int x1 = 1;
   double y1 = 2.2357;
   float x2 = 2.5343f;
   double y2 = 2;

   printf("P1 = (%i, %f)\n", x1, y1);
   printf("P1 = (%i, %i)\n", x1, (int)y1);
   printf("P1 = (%f, %f)\n", (double)x1, (double)y1);
   printf("P1 = (%.3f, %.3f)\n", (double)x1, (double)y1);

   printf("P2 = (%f, %f)\n", x2, y2);

   double dx = (x1 - x2); // implicit type conferences to double (or float)
   double dy = (y1 - y2);

   printf("(P1 - P2)=(%.3f, %0.3f)\n", dx, dy); 
   printf("|P1 - P2|^2=%.2f\n", dx * dx + dy * dy); 
   return 0;
}
