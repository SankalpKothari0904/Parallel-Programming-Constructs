#include <stdio.h>
#include <omp.h>

int main(){
	long long int total_sum, N;
    N = 100000000;
    total_sum = 0;
    auto start = omp_get_wtime();
    for(int i = 1; i <= N; i++) {
        total_sum += i;
    }

	printf("Total sum from 1 to %lld: %lld, computed in: %f seconds\n", N, total_sum, omp_get_wtime() - start);
	return 0;
}
