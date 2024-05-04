#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>   // Include the time.h library for clock()

#define LIMIT     2500000     /* Increase this to find more primes */
#define PRINT     100000      /* Print a line after this many numbers */

int isprime(int n) {
    int i, squareroot;
    if (n > 10) {
        squareroot = (int) sqrt(n);
        for (i = 3; i <= squareroot; i = i + 2)
            if ((n % i) == 0)
                return 0;
        return 1;
    }
    /* Assume first four primes are counted elsewhere. Forget everything else */
    else
        return 0;
}

int main(int argc, char *argv[]) {
    int n,                           /* loop variables */
        pc,                          /* prime counter */
        foundone;                    /* most recent prime found */
    clock_t start_time, end_time;   // Variables to store start and end times

    printf("Starting. Numbers to be scanned= %d\n", LIMIT);

    pc = 4;     /* Assume the primes less than 10 (2,3,5,7) are counted here */

    start_time = clock();  // Record the start time

    for (n = 11; n <= LIMIT; n = n + 2) {
        if (isprime(n)) {
            pc++;
            foundone = n;
            /***** Optional: print each prime as it is found
            printf("%d\n", foundone);
            *****/
        }
        if ((n - 1) % PRINT == 0)
            printf("Numbers scanned= %d   Primes found= %d\n", n - 1, pc);
    }

    end_time = clock();  // Record the end time

    printf("Done. Largest prime is %d Total primes %d\n", foundone, pc);
    
    // Calculate and print the elapsed time
    printf("Wall clock time elapsed: %.6lf seconds\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

    return 0;
}
