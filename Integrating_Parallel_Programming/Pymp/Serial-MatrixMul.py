import time

# Function to perform matrix multiplication
def matrix_multiplication(A, B):
    result = [[0] * len(B[0]) for _ in range(len(A))]
    for i in range(len(A)):
        for j in range(len(B[0])):
            for k in range(len(B)):
                result[i][j] += A[i][k] * B[k][j]
    return result

# Define matrix sizes
N = 500
M = 500
K = 500

# Generate random matrices
A = [[0]*M for _ in range(N)]
B = [[0]*K for _ in range(M)]

for i in range(N):
    for j in range(M):
        A[i][j] = 1  # You can use any values or input your matrices here

for i in range(M):
    for j in range(K):
        B[i][j] = 2  # You can use any values or input your matrices here

# Measure the time taken for matrix multiplication
start_time = time.time()
result = matrix_multiplication(A, B)
end_time = time.time()

# Calculate the elapsed time
elapsed_time = end_time - start_time

print("Time taken for matrix multiplication: {:.5f} seconds".format(elapsed_time))
