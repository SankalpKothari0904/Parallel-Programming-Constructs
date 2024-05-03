import time

def compute_pi_serial(n):
    delta_x = 1.0 / n
    sum = 0.0
    for i in range(n):
        x = (i + 0.5) * delta_x
        sum += 4.0 / (1.0 + x * x)
    pi = delta_x * sum
    return pi

n = 100000000
for i in range(15):
    start_time = time.time()
    pi = compute_pi_serial(n)
    end_time = time.time()
    print("Time taken:", end_time - start_time, "seconds")
    print("Approximation of pi:", pi)
