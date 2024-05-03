from numba import njit
import numpy as np
from numba.openmp import openmp_context as openmp
from numba.openmp import omp_set_num_threads, omp_get_thread_num, omp_get_wtime, omp_get_num_threads
from time import sleep

MAX_THREADS = 16    # Maximum number of threads possible (may depend on the system).

@njit
def pi_func(num_steps):
    step = 1.0 / num_steps
    partial_sums = np.zeros(MAX_THREADS)
    start_time = omp_get_wtime()

    with openmp("parallel shared(partial_sums, num_thrds) private(i, x, local_sum, thread_id)"):
        thread_id = omp_get_thread_num()
        with openmp("single"):
            num_thrds = omp_get_num_threads()
            print("Number of threads =", num_thrds)

        local_sum = 0.0
        for i in range(thread_id, num_steps, num_thrds):
            x = (i + 0.5) * step
            local_sum = local_sum + 4.0 / (1.0 + x * x)
        partial_sums[thread_id] = local_sum

    pi = step * np.sum(partial_sums)
    run_time = omp_get_wtime() - start_time
    print("pi = ", pi, "in", run_time, "seconds", "with", num_steps, "steps")
    return pi


for i in range(15):
    start_jit = omp_get_wtime()
    pi_func(100000000)
    print("Time taken with JIT compilation:", omp_get_wtime() - start_jit)
    sleep(1)
