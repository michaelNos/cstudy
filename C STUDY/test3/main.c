#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    if (argc > 1) {
        for (int i =1; i < argc; i++) {
            int len = strlen(argv[i]);
            for(int j = len - 1; j >=0; j--){
                putchar(argv[i][j]);
            }
            putchar('\n');
        }
        return 0;
    }
}
