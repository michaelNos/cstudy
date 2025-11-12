#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define POEM_IN  "c_poem.txt"
#define POEM_OUT "c_poem_censored.txt"
#define COPY_OUT "copy.txt"
#define CONTACTS "contacts.txt"

// ---- helper: create file if missing ----
void create_file_if_missing(const char *filename, const char *content) {
    FILE *f = fopen(filename, "r");
    if (f) { fclose(f); return; }   // already exists
    f = fopen(filename, "w");
    if (!f) { perror("create file"); exit(1); }
    fputs(content, f);
    fclose(f);
    printf("Created %s with default content.\n", filename);
}

// ---- Task 1: Text censorship ----
void task1(void) {
    create_file_if_missing(POEM_IN,
"In the realm of code, C stands tall, a robust language, embraced by all.\n"
"With syntax concise, and power untold, it crafts systems, timeless and bold.\n"
"Pointers dance in memory's maze, arrays align in structured arrays.\n"
"Functions echo, a symphony of logic, in C's embrace, a coder's magic.\n"
"From main to end, the journey unfolds, loops and branches, stories untold.\n"
"Efficiency reigns in every line, in the heart of C, brilliance aligns.\n"
"Header files whisper of libraries vast, A tapestry woven, from present to past.\n"
"C, the maestro in the coding symphony, Crafting elegance in binary harmony.\n"
"- ChatGPT\n");

    FILE *in = fopen(POEM_IN, "r");
    FILE *out = fopen(POEM_OUT, "w");
    if (!in || !out) { perror("open file"); exit(1); }

    int ch;
    while ((ch = fgetc(in)) != EOF) {
        if (ch == 'C') ch = '*';
        fputc(ch, out);
    }

    fclose(in);
    fclose(out);
    printf("Task 1 done: %s censored into %s\n", POEM_IN, POEM_OUT);
}

// ---- Task 2: Copying ----
void task2(void) {
    FILE *in = fopen(POEM_OUT, "r");
    if (!in) {
        printf("%s missing, running Task 1 first.\n", POEM_OUT);
        task1();
        in = fopen(POEM_OUT, "r");
    }
    FILE *out = fopen(COPY_OUT, "w");
    if (!in || !out) { perror("open"); exit(1); }

    char buffer[50];  // try changing to 100, 10, etc.
    printf("\n--- Copying lines from %s ---\n", POEM_OUT);

    while (fgets(buffer, sizeof(buffer), in)) {
        printf("%s", buffer);
        fputs(buffer, out);
    }

    fclose(in);
    fclose(out);
    printf("\nTask 2 done: copied to %s\n", COPY_OUT);
    printf("If a line is longer than buffer, fgets() splits it into multiple reads.\n");
}

// ---- Task 3: Read and Display Contacts ----
void task3(void) {
    create_file_if_missing(CONTACTS,
"Miles 23\nLeonardo 31\nGeorge 22\nFrederique 40\nRobin 4\nRiccardo 35\n");

    FILE *f = fopen(CONTACTS, "r");
    if (!f) { perror("open contacts"); exit(1); }

    char name[100];
    int age, count = 0, sum = 0;

    printf("\n--- Contacts list ---\n");
    while (fscanf(f, "%99s %d", name, &age) == 2) {
        printf("%s %d\n", name, age);
        sum += age;
        count++;
    }
    fclose(f);

    if (count)
        printf("Total: %d, Average age: %.2f\n", count, (double)sum / count);
    else
        printf("No contacts found.\n");

    // optional: append new
    char addName[100];
    int addAge;
    printf("\nAdd new contact? (Name Age, or press Enter to skip): ");
    if (scanf("%99s %d", addName, &addAge) == 2) {
        FILE *a = fopen(CONTACTS, "a");
        fprintf(a, "%s %d\n", addName, addAge);
        fclose(a);
        printf("Added: %s %d\n", addName, addAge);
    } else {
        printf("No new contact added.\n");
    }
}

// ---- main ----
int main(void) {
    printf("=== Lab 07 – File Handling ===\n");
    task1();
    task2();
    task3();
    return 0;
}
