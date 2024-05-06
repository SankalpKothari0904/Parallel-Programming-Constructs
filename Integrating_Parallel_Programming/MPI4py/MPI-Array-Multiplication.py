from mpi4py import MPI
import random
import time

N = 500  # Size of the matrices

def initialize_matrix():
    return [[random.random() for _ in range(N)] for _ in range(N)]

def multiply_matrices(matrixA, matrixB, result, start_row, end_row):
    for i in range(start_row, end_row):
        for j in range(N):
            result[i][j] = sum(matrixA[i][k] * matrixB[k][j] for k in range(N))

if __name__ == "__main__":
    comm = MPI.COMM_WORLD
    rank = comm.Get_rank()
    num_tasks = comm.Get_size()

    matrixA = None
    matrixB = None
    result = [[0 for _ in range(N)] for _ in range(N)]

    random.seed(rank)  # Seed the random number generator

    rows_per_task = N // num_tasks
    start_row = rank * rows_per_task
    end_row = N if rank == num_tasks - 1 else (rank + 1) * rows_per_task

    if rank == 0:
        matrixA = initialize_matrix()
        matrixB = initialize_matrix()
        start_time = time.time()  # Record start time

    matrixA = comm.bcast(matrixA, root=0)
    matrixB = comm.bcast(matrixB, root=0)

    multiply_matrices(matrixA, matrixB, result, start_row, end_row)

    result = comm.gather(result, root=0)

    if rank == 0:
        merged_result = [[0 for _ in range(N)] for _ in range(N)]
        for res in result:
            for i in range(N):
                for j in range(N):
                    merged_result[i][j] += res[i][j]
        end_time = time.time()  # Record end time
        print("Elapsed time (parallel): {:.4f} seconds".format(end_time - start_time))
