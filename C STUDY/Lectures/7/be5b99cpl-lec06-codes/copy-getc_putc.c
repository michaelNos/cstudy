#include <stdio.h>
#include <sys/time.h>

int main(void)
{
   int c;
   int bytes = 0;
   struct timeval t1, t2;
   gettimeofday(&t1, NULL);
   while ((c = getc(stdin)) != EOF) {
      if (putc(c, stdout) == EOF) {
         fprintf(stderr, "Error in putc");
         break;
      }
      bytes += 1;
   }
   gettimeofday(&t2, NULL);
   double dt = t2.tv_sec - t1.tv_sec + ((t2.tv_usec - t1.tv_usec) / 1000000.0);
   double mb = bytes / (1024 * 1024);
   fprintf(stderr, "%.2lf MB/sec\n", mb / dt);
   return 0;
}
