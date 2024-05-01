#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <omp.h>

using namespace std;

int MAX_THREADS = 16;    // Maximum number of threads possible (may depend on the system).

double pi_func(int num_steps) {
    double step = 1.0 / num_steps;
    double partial_sums[MAX_THREADS];

    int num_thrds, i, thread_id; 
    double local_sum, x;

    for(int i = 0; i < MAX_THREADS; i++) {
        partial_sums[i] = 0.0;
    }

    auto start_time = omp_get_wtime();
    
    thread_id = omp_get_thread_num();

    num_thrds = omp_get_num_threads();
    printf("Number of threads = %d\n", num_thrds);

    local_sum = 0.0;
    for(i = thread_id; i < num_steps; i += num_thrds) {
        x = (i + 0.5) * step;
        local_sum = local_sum + 4.0 / (1.0 + x * x);
    }
    partial_sums[thread_id] = local_sum;
    

    double total_sum = 0.0;
    for(i = 0; i < num_thrds; i++) {
        total_sum += partial_sums[i];
    }

    long double pi = step * total_sum;
    printf("pi = %.10Lf in %f seconds with %d steps\n", pi, omp_get_wtime() - start_time, num_steps);
    return pi;
}

int main() {
    double pi = pi_func(100000000);
    return 0;
}
