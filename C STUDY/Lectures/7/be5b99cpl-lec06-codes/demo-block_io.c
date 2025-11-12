#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#include <sys/time.h>

#ifndef BUFSIZE
#define BUFSIZE 32768
#endif

#ifndef BSIZE 
#define BSIZE 4098
#endif

int main(int argc, char *argv[])
{
   int c = 0;
   _Bool read = true;
   const char *fname = NULL;
   FILE *file;
   const char *mode = "r";
   while (argc-- > 1) {
      fprintf(stderr, "DEBUG: argc: %d '%s'\n", argc, argv[argc]);
      if (strcmp(argv[argc], "-w") == 0) {
         fprintf(stderr, "DEBUG: enable writting\n");
         read = false; // enable writting
         mode = "w";
      } else { 
         fname = argv[argc];
      }
   } // end while
   file = fopen(fname, mode);
   if (!file) {
      fprintf(stderr, "ERROR: Cannot open file '%s', error %d - %s\n", fname, errno, strerror(errno));
      return -1;
   }
   int *data = (int*)malloc(BSIZE * sizeof(int));
   assert(data);
   struct timeval t1, t2;
   gettimeofday(&t1, NULL);
   if (read) {
      fprintf(stderr, "INFO: Read from the file '%s'\n", fname);
      c = fread(data, sizeof(int), BSIZE, file);
      if (c != BSIZE) {
         fprintf(stderr, "WARN: Read only %i objects (int)\n", c);
      } else {
         fprintf(stderr, "DEBUG: Read %i objects (int)\n", c);
      }
   } else {
      char buffer[BUFSIZE];
      if (setvbuf(file, buffer, _IOFBF, BUFSIZE)) {
         fprintf(stderr, "WARN: Cannot set buffer");
      }
      fprintf(stderr, "INFO: Write to the file '%s'\n", fname);
      c = fwrite(data, sizeof(int), BSIZE, file);
      if (c != BSIZE) {
         fprintf(stderr, "WARN: Write only %i objects (int)\n", c);
      } else {
         fprintf(stderr, "DEBUG: Write %i objects (int)\n", c);
      }
      fflush(file);
   }
   gettimeofday(&t2, NULL);
   double dt = t2.tv_sec - t1.tv_sec + ((t2.tv_usec - t1.tv_usec) / 1000000.0);
   double mb = (sizeof(int) * c)/ (1024 * 1024);
   fprintf(stderr, "DEBUG: feof: %i ferror: %i\n", feof(file), ferror(file));
   fprintf(stderr, "INFO: %s %lu MB\n", (read ? "read" : "write"), sizeof(int)*BSIZE/(1024 * 1024));
   fprintf(stderr, "INFO: %.2lf MB/sec\n", mb / dt);
   free(data);
   return EXIT_SUCCESS;
}
