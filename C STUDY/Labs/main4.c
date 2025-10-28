#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// ---------- TASK 1 ----------
int compare_desc(const void *a, const void *b) {
    return (*(int*)b - *(int*)a); // descending
}

void task1(int N) {
    int arr[N];
    for (int i = 0; i < N; i++)
        scanf("%d", &arr[i]);

    printf("Original: ");
    for (int i = 0; i < N; i++)
        printf("%d ", arr[i]);
    printf("\n");

    qsort(arr, N, sizeof(int), compare_desc);

    printf("Sorted:   ");
    for (int i = 0; i < N; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// ---------- TASK 2 ----------
void task2() {
    char *buf = NULL;
    int size = 0;
    int c;

    printf("Enter characters (P=print, X=uppercase+exit):\n");
    while ((c = getchar()) != EOF) {
        if (c == 'P') {
            buf[size] = '\0';
            printf("Current: %s\n", buf);
        } else if (c == 'X') {
            for (int i = 0; i < size; i++)
                buf[i] = toupper((unsigned char)buf[i]);
            buf[size] = '\0';
            printf("Upper: %s\n", buf);
            free(buf);
            return;
        } else if (c != '\n') {
            buf = realloc(buf, size + 2); // +1 for new char, +1 for '\0'
            buf[size++] = c;
        }
    }
    free(buf);
}

// ---------- MAIN ----------
int main(int argc, char *argv[]) {
    if (argc == 2) {
        int N = atoi(argv[1]);
        task1(N);
    } else {
        task2();
    }
    return 0;
}
