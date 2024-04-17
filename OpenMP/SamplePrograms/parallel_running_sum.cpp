#include <stdio.h>
#include <omp.h>

int main(){
	int partial_sum, total_sum;
	#pragma omp parallel private(partial_sum) shared(total_sum)
	{
		partial_sum = 0;
		total_sum = 0;

		// Work sharing directive
		#pragma omp for
		for(int i = 1; i <= 1000; i++) {
			partial_sum += i;
		}

		// The threads must be joined in a one-writer fashion when adding each partial sum to the total_sum.
		// This creates a thread-safe section of the code.
		#pragma omp critical
		{
			total_sum += partial_sum;
		}
	}
	printf("Total sum from 1 to 1000: %d\n", total_sum);
	return 0;
}
