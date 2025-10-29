#include <stdio.h>

int main(int argc, char *argv[]) 
{
   int a[] = {1,2,3};
   int *p = a;

   int size = sizeof(a) / sizeof(int);
   for (int i = 0; i < size; ++i) {
      printf("a[%d]=%d\n", i, a[i]);
   }

   for (int i = 0; i < size; ++i, p += 1) {
      printf("address %p array adress %p\n", p, &a[i]);
   }

   printf("\nString example\n");
   char str[] = "hallo";
   size = sizeof(str); // consider the null terminating string
   char* strp = str; 
   for (int i = 0; i < size; ++i, strp++) {
      printf("str[%i]=%c address %p\n", i, *strp, strp);
   }
   return 0;
}

// a[0]=1
// a[1]=2
// a[2]=3
// address 0x7ffc0ddd05d4 array adress 0x7ffc0ddd05d4
// address 0x7ffc0ddd05d8 array adress 0x7ffc0ddd05d8
// address 0x7ffc0ddd05dc array adress 0x7ffc0ddd05dc

// String example
// str[0]=h address 0x7ffc0ddd05b6
// str[1]=a address 0x7ffc0ddd05b7
// str[2]=l address 0x7ffc0ddd05b8
// str[3]=l address 0x7ffc0ddd05b9
// str[4]=o address 0x7ffc0ddd05ba
// str[5]= address 0x7ffc0ddd05bb