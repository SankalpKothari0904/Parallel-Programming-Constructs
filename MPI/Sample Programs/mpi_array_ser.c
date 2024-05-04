#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Include time.h for timing functions
#define ARRAYSIZE 2000000

int main(int argc, char *argv[]){
    int i;   /* loop variable */
    float data[ARRAYSIZE]; /* the initial array */

    printf("Starting serial array example...\n");
    printf("Using array of %d floats. Requires %ld bytes\n", ARRAYSIZE, sizeof(data));

    /* Initialize the array */
    printf("Initializing array...\n");
    for (i = 0; i < ARRAYSIZE; i++)
        data[i] = i * 1.0;

    /* Do a simple value assignment to each of the array elements */
    printf("Performing computation on array elements...\n");

    // Record start time
    clock_t start_time = clock();

    for (i = 1; i < ARRAYSIZE; i++)
        data[i] = data[i] + i * 1.0;

    // Record end time and calculate elapsed time
    clock_t end_time = clock();
    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Elapsed wall clock time: %f seconds\n", elapsed_time);

    /* Print a few sample results */
    printf("Sample results\n");
    printf("   data[1]=%e\n", data[1]);
    printf("   data[100]=%e\n", data[100]);
    printf("   data[1000]=%e\n", data[1000]);
    printf("   data[10000]=%e\n", data[10000]);
    printf("   data[20000]=%e\n", data[20000]);
    printf("\nAll Done!\n");
}
