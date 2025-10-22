#include <stdio.h>

void printValue(int v)
{
   printf("value: %i\n", v);
   printValue(v + 1);
}

int main(void)
{
   printValue(1);
}
