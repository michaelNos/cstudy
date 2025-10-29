#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <string>\n", argv[0]);
        return 1;
    }

    char *input = argv[1];
    int size = strlen(input);
    char chars[size][2];  // fixed array: size rows, 2 cols (1 char + '\0')

    for (int i = 0; i < size; i++) {
        chars[i][0] = input[i];
        chars[i][1] = '\0';
    }

    for (int i = 0; i < size; i++) {
        printf("%s\n", chars[i]);
    }

    return 0;
}
