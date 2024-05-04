#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 500 // Size of the matrices

void initializeMatrix(double matrix[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = (double) rand() / RAND_MAX; // Random initialization
        }
    }
}

void multiplyMatrices(double matrixA[N][N], double matrixB[N][N], double result[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            double sum = 0.0;
            for (int k = 0; k < N; k++) {
                sum += matrixA[i][k] * matrixB[k][j];
            }
            result[i][j] = sum;
        }
    }
}

int main() {
    double matrixA[N][N];
    double matrixB[N][N];
    double result[N][N];
    srand(time(NULL)); // Seed the random number generator

    initializeMatrix(matrixA);
    initializeMatrix(matrixB);

    clock_t start_time = clock(); // Record start time

    multiplyMatrices(matrixA, matrixB, result);

    clock_t end_time = clock(); // Record end time

    printf("Elapsed time (serial): %.4f seconds\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

    return 0;
}
