from numba import njit
from numba.openmp import openmp_context as openmp
from numba.openmp import omp_get_wtime
from numba.openmp import omp_get_num_threads, omp_set_num_threads

NSTEPS = 1000000
MIN_BLK = 1024*1024*256

@njit
def pi_comp(n_start, n_stop, step):
    iblk = n_stop - n_start
    
    # Check if current task is small enough
    if(iblk < MIN_BLK):
        sum = 0.0
        for i in range(n_start, n_stop):
            x = (i + 0.5)*step
            sum += 4.0/(1.0 + x*x)

    else:
        sum1 = 0.0
        sum2 = 0.0
        with openmp("task shared (sum1)"):
            sum1 = pi_comp(n_start, n_stop - iblk//2, step)

        with openmp("task shared (sum2)"):
            sum1 = pi_comp(n_stop - iblk//2, n_stop, step)

        with openmp ("taskwait"):
            sum = sum1 + sum2

    return sum

@njit
def pi_func(num_steps):
    step = 1.0/num_steps
    sum = 0.0
    start_time = omp_get_wtime()
    
    with openmp("parallel"):
        with openmp("single"):
            sum = pi_comp(0, num_steps, step)

    pi = step*sum
    run_time = omp_get_wtime() - start_time
    print("pi =", pi, "in", run_time, "seconds for", num_steps, "steps")
    return pi

start = omp_get_wtime()
pi = pi_func(NSTEPS)
print("Time including JIT time:", omp_get_wtime() - start)
