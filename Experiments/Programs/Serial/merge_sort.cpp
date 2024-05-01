#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#define TASK_SIZE 100

// Function to generate a random number within a given range
unsigned int rand_interval(unsigned int min, unsigned int max)
{
    int r;
    const unsigned int range = 1 + max - min;
    const unsigned int buckets = RAND_MAX / range;
    const unsigned int limit = buckets * range;

    do
    {
        r = rand();
    } 
    while (r >= limit);

    return min + (r / buckets);
}

// Function to fill an array with random numbers
void fillupRandomly (int *m, int size, unsigned int min, unsigned int max){
    for (int i = 0; i < size; i++)
        m[i] = rand_interval(min, max);
} 

// Function to merge two sorted subarrays into a single sorted array
void mergeSortAux(int *X, int n, int *tmp) {
    int i = 0;
    int j = n/2;
    int ti = 0;

    while (i<n/2 && j<n) {
        if (X[i] < X[j]) {
            tmp[ti] = X[i];
            ti++; i++;
        } else {
            tmp[ti] = X[j];
            ti++; j++;
        }
    }
    while (i<n/2) { /* finish up lower half */
        tmp[ti] = X[i];
        ti++; i++;
    }
    while (j<n) { /* finish up upper half */
        tmp[ti] = X[j];
        ti++; j++;
    }
    memcpy(X, tmp, n*sizeof(int));
} 

// Recursive function to perform merge sort on an array
void mergeSort(int *X, int n, int *tmp)
{
    if (n < 2) return;

    mergeSort(X, n/2, tmp);
    mergeSort(X+(n/2), n-(n/2), tmp + n/2);

    mergeSortAux(X, n, tmp);
}

// Function to initialize an array with zeros
void init(int *a, int size){
    for(int i = 0; i < size; i++)
        a[i] = 0;
}

// Function to print the elements of an array
void printArray(int *a, int size){
    for(int i = 0; i < size; i++)
        printf("%d ", a[i]);
    printf("\n");
}

// Function to check if an array is sorted in ascending order
int isSorted(int *a, int size){
    for(int i = 0; i < size - 1; i++)
        if(a[i] > a[i + 1])
            return 0;
    return 1;
}

int main(int argc, char *argv[]) {
    srand(123456);
    int N  = (argc > 1) ? atoi(argv[1]) : 100000000;
    int print = (argc > 2) ? atoi(argv[2]) : 0;
    int numThreads = (argc > 3) ? atoi(argv[3]) : 1;
    int *X = (int *)malloc(N * sizeof(int));
    int *tmp = (int *)malloc(N * sizeof(int));

    omp_set_dynamic(0);              /** Explicitly disable dynamic teams **/
    omp_set_num_threads(numThreads); /** Use N threads for all parallel regions **/

    // Dealing with failed memory allocation
    if(!X || !tmp)
    { 
        if(X) free(X);
        if(tmp) free(tmp);
        return (-1);
    }

    fillupRandomly (X, N, 0, 5);

    double start = omp_get_wtime();
    
    mergeSort(X, N, tmp);

    printf("Time: %f (s) \n", omp_get_wtime() - start);

    assert(1 == isSorted(X, N));

    if(print){
        printArray(X, N);
    }

    free(X);
    free(tmp);
    return (0);
}
