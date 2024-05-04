#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h> 

#define N 500 // Size of the matrices

void initializeMatrix(double matrix[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = (double) rand() / RAND_MAX; // Random initialization
        }
    }
}

void multiplyMatrices(double matrixA[N][N], double matrixB[N][N], double result[N][N], int startRow, int endRow) {
    for (int i = startRow; i < endRow; i++) {
        for (int j = 0; j < N; j++) {
            double sum = 0.0;
            for (int k = 0; k < N; k++) {
                sum += matrixA[i][k] * matrixB[k][j];
            }
            result[i][j] = sum;
        }
    }
}

int main(int argc, char *argv[]) {
    int rank, numtasks;
    double matrixA[N][N];
    double matrixB[N][N];
    double result[N][N];
    srand(time(NULL)); // Seed the random number generator

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

    int rowsPerTask = N / numtasks;
    int startRow = rank * rowsPerTask;
    int endRow = (rank == numtasks - 1) ? N : (rank + 1) * rowsPerTask;

    initializeMatrix(matrixA);
    initializeMatrix(matrixB);

    double start_time = MPI_Wtime(); // Record start time

    multiplyMatrices(matrixA, matrixB, result, startRow, endRow);

    double end_time = MPI_Wtime(); // Record end time

    if (rank == 0) {
        printf("Elapsed time (parallel): %.4f seconds\n", end_time - start_time);
    }

    MPI_Finalize();

    return 0;
}
