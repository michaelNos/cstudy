#include <stdlib.h>
#include <stdio.h>

void* allocate_memory(int size, void **ptr) 
{
   *ptr = malloc(size);
   if (*ptr == NULL) {
      fprintf(stderr, "Error: required block of memory has not been allocated!\n");
      exit(-1); /* if allocation fail exit the program */
   }
   return *ptr;
}

void fill_array(int* array, int size) 
{
   /* array is a local variable initialized 
    * with the calling value */
   /* notice size may be larger than int */
   for (int i = 0; i < size; ++i) {
      *(array++) = random();
   }
}

void deallocate_memory(void **ptr)
{
   if (ptr != NULL && *ptr != NULL) {
      free(*ptr);
      *ptr = NULL;
   }
}

int main(int argc, char *argv[]) 
{
   int *int_array;
   const int size = 4;

   allocate_memory(sizeof(int) * size, (void**)&int_array);

   fill_array(int_array, size);

   int *cur = int_array;
   for (int i = 0; i < size; ++i, cur++) {
      printf("Array[%d] = %d\n", i, *cur);
   }

   deallocate_memory((void**)&int_array);
   return 0;
}
