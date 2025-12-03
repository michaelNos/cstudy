#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc < 2) return 1;

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    char mode[10];
    if(scanf("%9s", mode) != 1)
        return 1;
    int a;
    int min = 0;
    int max = 0;

    while (fscanf(f, "%i", &a) == 1) {
        if (a < min) min = a;
        if (a > max) max = a;
    }

    fclose(f);

    if(strcmp(mode, "min") == 0){
        printf("%d\n", min);
    } else if(strcmp(mode, "max") == 0){
        printf("%d\n", max);
    } else if(strcmp(mode, "minmax") == 0){
        printf("%d %d\n", min, max);
    }
    return 0;
}

