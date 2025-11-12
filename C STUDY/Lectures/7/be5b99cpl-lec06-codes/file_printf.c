#include <stdio.h>

int main(int argc, char *argv[]) 
{
   char *fname = argc > 1 ? argv[1] : "out.txt";
   FILE *f;
   if ((f = fopen(fname, "w")) == NULL) {
      fprintf(stderr, "Error: Open file '%s'\n", fname);
      return -1;
   }
   printf("File '%s' has been opened for writting\n", fname);

   fprintf(f, "Program arguments argc: %d\n", argc);
   for (int i = 0; i < argc; ++i) {
      fprintf(f, "argv[%d]='%s'\n", i, argv[i]);
   }

   printf("Program arguments written to the file\n");

   if (fclose(f) == EOF) {
      fprintf(stderr, "Error: Close file '%s'\n", fname);
      return -1;
   }
   printf("File has been closed\n");
   return 0;
}
