#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    if (argc > 1) {
        for (int i = argc-1; i > 0; i--) {
            int len = strlen(argv[i]);
            for(int j = len - 1; j >=0; j--){
                putchar(argv[i][j]);
            }
            putchar('\n');
        }
        return 0;
    }
}
