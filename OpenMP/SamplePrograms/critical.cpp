#include <stdio.h>
#include <omp.h>

int main() {
	int x;
	x = 0;

	#pragma omp parallel shared(x) 
	{
		//#pragma omp critical 
		x = x + 1;	
	}
	printf("Value of x: %d\n", x);
	return 0;
}
