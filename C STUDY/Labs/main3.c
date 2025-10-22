#include <stdio.h>

float dot_product(float *a, float *b, int size) {
    float sum = 0;
    for (int i = 0; i < size; i++)
        sum += (*(a + i)) * (*(b + i)); // using pointers
    return sum;
}

int main() {
    float v1[3] = {1.0, 2.0, 3.0};
    float v2[3];
    float M[3][3], result[3] = {0};

    // --- Task 1: Dot product ---
    printf("Enter 3 numbers for second vector:\n");
    for (int i = 0; i < 3; i++)
        scanf("%f", &v2[i]);

    printf("\nDot product = %.2f\n\n", dot_product(v1, v2, 3));

    // --- Task 2: Matrix multiplication ---
    printf("Enter 9 numbers for 3x3 matrix:\n");
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            scanf("%f", &M[i][j]);

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            result[i] += M[i][j] * v1[j];

    printf("\nResulting vector (M × v1):\n");
    for (int i = 0; i < 3; i++)
        printf("%.2f ", result[i]);
    printf("\n");

    return 0;
}
