#include <stdio.h>

int main(int argc, char *argv[]) 
{
   char *fname = "data.txt";
   FILE *f;
   if ((f = fopen(fname, "r")) == NULL) {
      fprintf(stderr, "Error: open file '%s'\n", fname);
      return -1;
   }

   char str[10];
   int i = -1;
   double d = -1.0;
   int line = 1;
   while (feof(f) == 0) {
      int r = fscanf(f, "%9s %d %lf\n", str, &i, &d);
      if (r == 3) {
         fprintf(stdout, "Info: Line %d number of items scanned %d: s: %s i: %i, d: %lf\n", line, r, str, i, d);
      } else {
         fprintf(stdout, "\n");
         fprintf(stdout, "Warn: Line %d number of items scanned %d: s: %s i: %i, d: %lf\n", line, r, str, i, d);
         break;
      }
      line++;
   }
   if (fclose(f) == EOF) {
      fprintf(stderr, "Error: Close file '%s'\n", fname);
      return -1;
   }
   return 0;
}
