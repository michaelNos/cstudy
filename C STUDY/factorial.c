#include <stdio.h>

// Shortest recursive factorial function
int f(int n) { return n<2 ? 1 : n*f(n-1); }

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("Factorial of %d is %d\n", n, f(n));
    return 0;
}