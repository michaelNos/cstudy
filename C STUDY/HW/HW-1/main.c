#include <stdio.h>
#include <stdlib.h>

double for_one(double p) {
    return (0.8 * p) / ((0.8 * p) + (0.2 * (1 - p)));
}

double for_nul(double p) {
    return (0.2 * p) / ((0.2 * p) + (0.8 * (1 - p)));
}

int main(int argc, char **argv) {
    if (argc < 2) return 0;

    double P = 0.5;

    for (int i = 1; i < argc; ++i) {
        int m = atoi(argv[i]);
        if (m == 0)
            P = for_nul(P);
        else if (m == 1)
            P = for_one(P);
        else {
            printf("Error: Invalid input.\n");
            return 1;
        }

        printf("%.5f", P);
        if (i < argc - 1) printf(" ");
    }

    printf("\n");
    return 0;
}
