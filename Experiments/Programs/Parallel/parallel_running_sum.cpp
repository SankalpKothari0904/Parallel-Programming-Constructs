#include <stdio.h>
#include <omp.h>

int main(){
	long long int partial_sum, total_sum;
	auto start = omp_get_wtime();
	#pragma omp parallel private(partial_sum) shared(total_sum)
	{
		partial_sum = 0;
		total_sum = 0;

		// Work sharing directive
		#pragma omp for
		for(int i = 1; i <= 100000000; i++) {
			partial_sum += i;
		}
		
		// The threads must be joined in a one-writer fashion when adding each partial sum to the total_sum.
		// This creates a thread-safe section of the code.
		#pragma omp critical
		{
			total_sum += partial_sum;
		}
	}
	printf("Total sum from 1 to 100000000: %lld, computed in %f seconds\n", total_sum, omp_get_wtime() - start);
	return 0;
}
