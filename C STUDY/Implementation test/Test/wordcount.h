#ifndef WORDCOUNT_H
#define WORDCOUNT_H

#define MAX_WORD_LEN 50

typedef struct {
    char word[MAX_WORD_LEN + 1];
    int count;
} Word;

// Reads words from file, counts, returns array via out_words.
int read_and_count(const char *filename, Word **out_words, int *out_size);

// Sorts words by frequency
void sort_by_frequency(Word *words, int size);

// Prints n most frequent words with length >= min_len.
void print_top(const Word *words, int size, int n, int min_len);

#endif