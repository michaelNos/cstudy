#include <stdio.h>
#include <inttypes.h>

// a     dec: 4 bin: 0100
// b     dec: 5 bin: 0101
// a & b dec: 4 bin: 0100
// a | b dec: 5 bin: 0101
// a ^ b dec: 1 bin: 0001

// a >> 1 dec: 2 bin: 0010
// a << 1 dec: 8 bin: 1000

void print_bin(int c, uint8_t n) 
{
   if (c) {
      print_bin(--c, n >> 1);
      putc((n & 1) ? '1' : '0', stdout);
   }
}

void print_binary(char *prefix, uint8_t n) 
{
   printf(prefix, n);
   print_bin(4, n);
   printf("\n");
}

int main(int argc, char *argv[]) 
{
   uint8_t a = 4;
   uint8_t b = 5;
   print_binary("a     dec: %d bin: ", a);
   print_binary("b     dec: %d bin: ", b);
   print_binary("a & b dec: %d bin: ", a & b);
   print_binary("a | b dec: %d bin: ", a | b);
   print_binary("a ^ b dec: %d bin: ", a ^ b);
   printf("\n");
   print_binary("a >> 1 dec: %d bin: ", a >> 1);
   print_binary("a << 1 dec: %d bin: ", a << 1);
   return 0;
}
