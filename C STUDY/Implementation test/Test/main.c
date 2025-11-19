#include <stdio.h>
#include <stdlib.h>
#include "wordcount.h"

int main(int argc, char **argv) {
    if (argc != 4) {
        fprintf(stderr, "Arguments must be: %s input_file n m\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    int n = atoi(argv[2]);
    int m = atoi(argv[3]);

    if (n <= 0 || m < 0) {
        fprintf(stderr, "Error: n must be > 0 and m >= 0\n");
        return 1;
    }

    Word *words = NULL;
    int size = 0;

    int rc = read_and_count(filename, &words, &size);
    if (rc != 0) {
        fprintf(stderr, "Error: cannot read file '%s'\n", filename);
        return 1;
    }

    sort_by_frequency(words, size);
    print_top(words, size, n, m);

    free(words);
    return 0;
}