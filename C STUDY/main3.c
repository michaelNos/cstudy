#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **split_chars(const char *input, int *count) {
    int size = strlen(input);
    char **chars = malloc(size * sizeof(char*));

    for (int i = 0; i < size; i++) {
        chars[i] = malloc(2);      // 1 char + '\0'
        chars[i][0] = input[i];
        chars[i][1] = '\0';
    }

    *count = size;  // pass back number of elements
    return chars;   // ✅ valid after function returns
}

int main() {
    char *text = "HELLO";
    int n;
    char **letters = split_chars(text, &n);

    for (int i = 0; i < n; i++) {
        printf("%s\n", letters[i]);
        free(letters[i]);  // free each small string
    }
    free(letters);          // then free array of pointers
    return 0;
}
