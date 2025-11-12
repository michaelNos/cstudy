#include <stdio.h>

typedef struct {
   unsigned short seconds: 5; // use 5 bits to store seconds
   unsigned short minutes: 6; // use 6 bits to store minutes
   unsigned short hours: 5; //use 5 bits to store hours
} file_time_s;

typedef struct {
   unsigned int seconds: 5;
   unsigned int minutes: 6;
   unsigned int hours: 5; 
} file_time_int_s;

typedef struct {
   unsigned int seconds: 5;
   unsigned int : 0;
   unsigned int minutes: 6;
   unsigned int hours: 5; 
} file_time_int_skip_s;

void print_time(const file_time_s *t)
{
   printf("%02u:%02u:%02u\n", t->hours, t->minutes, t->seconds);
}

int main(void)
{
   file_time_s time = { .hours = 23, .minutes = 7, .seconds = 10 };
   print_time(&time);
   time.minutes += 30;
   print_time(&time);

   printf("Size of file_time_s %lu\n", sizeof(time));
   printf("Size of file_time_int_s %lu\n", sizeof(file_time_int_s));
   printf("Size of file_time_int_skip_s %lu\n", sizeof(file_time_int_skip_s));
   return 0;
}
