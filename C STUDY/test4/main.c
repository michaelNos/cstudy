#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc > 1) {
        FILE *in = fopen(argv[1], "r");
        if (!in) { perror("open file"); exit(1); }
        // int ch;
        // while ((ch = fgetc(in)) != EOF) {
        //     printf("Ch: %c\n", ch);
        // }
        char buffer[50];
        int total = 0;
        while (fgets(buffer, sizeof(buffer), in)) {
            // printf("%c * %c\n", buffer[0], buffer[2]);
            int linesum = atoi(&buffer[0]) * atoi(&buffer[2]);
            total += linesum;
        }
        printf("%i\n", total);
        return 0;
    }
}
