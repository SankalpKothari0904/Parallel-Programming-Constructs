import time
import random

N = 500  # Size of the matrices

def initialize_matrix(matrix):
    for i in range(N):
        for j in range(N):
            matrix[i][j] = random.random()

def multiply_matrices(matrixA, matrixB, result):
    for i in range(N):
        for j in range(N):
            sum_ = 0.0
            for k in range(N):
                sum_ += matrixA[i][k] * matrixB[k][j]
            result[i][j] = sum_

if __name__ == "__main__":
    matrixA = [[0] * N for _ in range(N)]
    matrixB = [[0] * N for _ in range(N)]
    result = [[0] * N for _ in range(N)]

    random.seed(time.time())  # Seed the random number generator

    initialize_matrix(matrixA)
    initialize_matrix(matrixB)

    start_time = time.time()  # Record start time

    multiply_matrices(matrixA, matrixB, result)

    end_time = time.time()  # Record end time

    print("Elapsed time (serial): {:.4f} seconds".format(end_time - start_time))
