#include <stdio.h>
#include <stdint.h>

int main(int argc, char *argv[]) 
{
   int8_t i8;
   int16_t i16;
   int32_t i32;

   printf("\nSize of the types\n");
   printf("int8_t size: %lu\n", sizeof(int8_t));
   printf("int16_t size: %lu\n", sizeof(int16_t));
   printf("int32_t size: %lu\n", sizeof(int32_t));

   printf("\nSize of the variables\n");
   printf("int8_t size: %lu\n", sizeof(i8));
   printf("int16_t size: %lu\n", sizeof(i16));
   printf("int32_t size: %lu\n", sizeof(i32));
   return 0;
}


// Size of the types
// int8_t size: 1
// int16_t size: 2
// int32_t size: 4

// Size of the variables
// int8_t size: 1
// int16_t size: 2
// int32_t size: 4