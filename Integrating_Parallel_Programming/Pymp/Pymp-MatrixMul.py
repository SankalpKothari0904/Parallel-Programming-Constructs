import pymp
import time

# Function to perform matrix multiplication
def matrix_multiplication(A, B, result, i, j, N):
    temp = 0
    for k in range(N):
        temp += A[i][k] * B[k][j]
    result[i][j] = temp

# Define matrix sizes
N = 500
M = 500
K = 500

# Generate random matrices
A = [[0]*M for _ in range(N)]
B = [[0]*K for _ in range(M)]
result = [[0]*K for _ in range(N)]

for i in range(N):
    for j in range(M):
        A[i][j] = 1  # You can use any values or input your matrices here

for i in range(M):
    for j in range(K):
        B[i][j] = 2  # You can use any values or input your matrices here

start_time = time.time()

# Create a parallel region
with pymp.Parallel(4) as p:
    # Parallelize the outer loop
    for i in p.range(N):
        # Iterate through columns of B
        for j in range(K):
            # Compute the dot product for the corresponding cell in the result matrix
            matrix_multiplication(A, B, result, i, j, M)

end_time = time.time()
elapsed_time = end_time - start_time

print("Time taken:", elapsed_time, "seconds")
# print(result)
