#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main(int argc, char **argv) {
    int den, num, fin_den, fin_num;
    // fprintf(stdout, "My first program in C!\n");
    // fprintf(stdout, "Its name is \"%s\"\n", argv[0]);
    // fprintf(stdout, "Run with %d arguments\n", argc);
    if (argc > 1) {
        fprintf(stdout, "The arguments are:\n");
        for (int i = 1; i < argc; ++i) {
            fprintf(stdout, "Arg: %d is \"%s\"\n", i, argv[i]);
        }
        den = atoi(argv[1]);
        num = atoi(argv[3]);
        fin_den = den/gcd(den, num);
        fin_num = num/gcd(den, num);
        fprintf(stdout, "Answer: %i / %i\n", fin_den, fin_num);
        return 0;
    }
}