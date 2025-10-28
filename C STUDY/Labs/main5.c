#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// ---------- TASK 1 ----------
size_t string_length(const char *str) {
    size_t len = 0;
    while (str[len] != '\0') len++;
    return len;
}

void task1(char *arg) {
    size_t len = string_length(arg);
    printf("Length: %zu\n", len);
    printf("Reverse: ");
    for (int i = len - 1; i >= 0; i--)
        putchar(arg[i]);
    printf("\n");
}

// ---------- TASK 2 ----------
void task2() {
    char line[201];
    printf("Enter sentence:\n");
    fgets(line, sizeof(line), stdin);
    line[strcspn(line, "\n")] = 0; // remove newline

    char *words[200];
    int count = 0;
    char *tok = strtok(line, " ");
    while (tok) {
        int duplicate = 0;
        for (int i = 0; i < count; i++) {
            if (strcasecmp(words[i], tok) == 0) {
                duplicate = 1;
                break;
            }
        }
        if (!duplicate)
            words[count++] = tok;
        tok = strtok(NULL, " ");
    }

    for (int i = 0; i < count; i++) {
        printf("%s", words[i]);
        if (i < count - 1) printf(" ");
    }
    printf("\n");
}

// ---------- TASK 3 ----------
void task3() {
    char line[101], clean[101];
    printf("Enter text:\n");
    fgets(line, sizeof(line), stdin);

    int j = 0;
    for (int i = 0; line[i]; i++)
        if (isalpha((unsigned char)line[i]))
            clean[j++] = tolower((unsigned char)line[i]);
    clean[j] = '\0';

    int len = strlen(clean), is_pal = 1;
    for (int i = 0; i < len / 2; i++)
        if (clean[i] != clean[len - i - 1]) is_pal = 0;

    printf("%s\n", is_pal ? "Palindrome" : "Not a palindrome");
}

// ---------- TASK 4 ----------
void task4() {
    char *text = NULL;
    size_t len = 0, cap = 0;
    int c;

    printf("Enter text (Ctrl+D to end):\n");
    while ((c = getchar()) != EOF) {
        if (len + 1 >= cap) {
            cap = cap ? cap * 2 : 256;
            text = realloc(text, cap);
        }
        text[len++] = c;
    }
    text[len] = '\0';

    int words = 0, letters = 0, hist[26] = {0};
    char *token = strtok(text, " \n\t.,!?;:");

    char longest[256] = "";
    while (token) {
        words++;
        int count = 0;
        for (int i = 0; token[i]; i++) {
            if (isalpha((unsigned char)token[i])) {
                letters++;
                hist[tolower((unsigned char)token[i]) - 'a']++;
                count++;
            }
        }
        if (count > (int)strlen(longest))
            strcpy(longest, token);
        token = strtok(NULL, " \n\t.,!?;:");
    }

    printf("Words: %d\nLetters: %d\n", words, letters);
    printf("Histogram:\n");
    for (int i = 0; i < 26; i++)
        if (hist[i]) printf("%c: %d\n", 'a' + i, hist[i]);
    printf("Longest: %s (%zu)\n", longest, strlen(longest));
    free(text);
}

// ---------- MAIN ----------
int main(int argc, char *argv[]) {
    if (argc > 1) {
        task1(argv[1]);
    } else {
        int choice;
        printf("Select task (2–4): ");
        scanf("%d%*c", &choice);
        if (choice == 2) task2();
        else if (choice == 3) task3();
        else if (choice == 4) task4();
        else printf("Invalid.\n");
    }
    return 0;
}
