from numba import njit
from numba.openmp import openmp_context as openmp
from numba.openmp import omp_set_num_threads


@njit
def test_pi_loop():
    num_steps = 1000000
    step = 1.0 / num_steps

    the_sum = 0.0
    omp_set_num_threads(4)

    with openmp("parallel"):
        with openmp("for reduction(+:the_sum) schedule(static)"):
            for j in range(num_steps):
                c = step
                x = ((j-1) - 0.5) * step
                the_sum += 4.0 / (1.0 + x * x)

    pi = step * the_sum
    return pi

x = test_pi_loop()
print(x)
