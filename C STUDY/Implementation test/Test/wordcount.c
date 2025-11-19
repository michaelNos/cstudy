#include "wordcount.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// sorting function for qsort method
static int cmp_words(const void *a, const void *b) {
    const Word *wa = (const Word *)a;
    const Word *wb = (const Word *)b;
    return wb->count - wa->count; // desc count
}

int read_and_count(const char *filename, Word **out_words, int *out_size) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        return 1;
    }

    Word *arr = NULL;
    int size = 0;
    int cap = 0;
    char buf[MAX_WORD_LEN + 1];

    while (fscanf(f, "%50s", buf) == 1) {
        int found = -1;
        for (int i = 0; i < size; i++) {
            if (strcmp(arr[i].word, buf) == 0) {
                found = i;
                break;
            }
        }

        if (found >= 0) {
            arr[found].count++;
        } else {
            if (size == cap) {
                int new_cap = cap ? cap * 2 : 16;
                Word *tmp = realloc(arr, new_cap * sizeof(Word));
                if (!tmp) {
                    free(arr);
                    fclose(f);
                    return 2;
                }
                arr = tmp;
                cap = new_cap;
            }
            strcpy(arr[size].word, buf);
            arr[size].count = 1;
            size++;
        }
    }

    fclose(f);

    *out_words = arr;
    *out_size = size;
    return 0;
}

void sort_by_frequency(Word *words, int size) {
    qsort(words, (size_t)size, sizeof(Word), cmp_words);
}

void print_top(const Word *words, int size, int n, int min_len) {
    int printed = 0;
    for (int i = 0; i < size && printed < n; i++) {
        if ((int)strlen(words[i].word) >= min_len) {
            printf("%s %d\n", words[i].word, words[i].count);
            printed++;
        }
    }
}