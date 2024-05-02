from numba import njit
from numba.openmp import openmp_context as openmp
from numba.openmp import omp_get_wtime

@njit
def pi_func(num_steps):
    step = 1.0/num_steps
    sum = 0.0
    start_time = omp_get_wtime()

    with openmp("parallel for private(x) reduction (+: sum)"):
        for i in range(num_steps):
            x = (i + 0.5)*step
            sum += 4.0/(1.0 + x*x)

    pi = step*sum
    run_time = omp_get_wtime() - start_time
    print("pi =", pi, "in", run_time, "seconds for", num_steps, "steps")
    return pi

start = omp_get_wtime()
pi = pi_func(100000000)
print("Time including JIT time:", omp_get_wtime() - start)
