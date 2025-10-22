#include <stdio.h>

void switch_example(char v)
{
   switch(v) {
      case 'A': 
         fprintf(stdout, "Upper 'A'\n");
         break;
      case 'a':
         fprintf(stdout, "Lower 'a'\n");
         break;
      default:
         fprintf(stdout, "It is not 'A' nor 'a'\n");
         break;
   }
}

void if_example(char v)
{
   if (v == 'A') {
      fprintf(stdout, "Upper 'A'\n");
   } else if (v == 'a') {
      fprintf(stdout, "Lower 'a'\n");
   } else {
      fprintf(stdout, "It is not 'A' nor 'a'\n");
   }
}

int main(void)
{
   switch_example('A');
   if_example('a');
   if_example('l');
   return 0;
}
