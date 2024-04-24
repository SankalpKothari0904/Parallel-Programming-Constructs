# THREADPRIVATE Directive
The `THREADPRIVATE` directive is used to make global file scope variables (C/C++) local and persistent to a thread through the execution of multiple parallel regions.

The directive must appear after the declaration of listed variables/common blocks. Each thread then gets its own copy of the variable/common block, so data written by one thread is not visible to other threads.

**Global File Scope Variables (C/C++):** These are variables declared outside of any function or block, making them accessible throughout the file. When such variables are declared as `threadprivate`, each thread gets its own private copy of the variable.
### Format
```c++
#pragma omp threadprivate (list)
```
### Example
```c++
// In a file called thread_private.cpp
#include <stdio.h>
#include <omp.h>

// Declare Global Variables
int  a, b, i, tid;
float x;

#pragma omp threadprivate(a, x)

int main() {
        // Explicitly turn off dynamic threads
        omp_set_dynamic(0);

        printf("1st Parallel Region:\n");
        #pragma omp parallel private(b,tid)
        {
                tid = omp_get_thread_num();
                a = tid;
                b = tid;
                x = 1.1 * tid +1.0;
                printf("Thread %d:   a,b,x= %d %d %f\n",tid,a,b,x);
        }  // end of parallel section

        printf("************************************\n");
        printf("Master thread doing serial work here\n");
        printf("************************************\n");

        printf("2nd Parallel Region:\n");
        #pragma omp parallel private(tid)
        {
                tid = omp_get_thread_num();
                printf("Thread %d:   a,b,x= %d %d %f\n",tid,a,b,x);
        }  // end of parallel section
        return 0;
}
```

Output:
```
1st Parallel Region:
Thread 2:   a,b,x= 2 2 3.200000
Thread 3:   a,b,x= 3 3 4.300000
Thread 1:   a,b,x= 1 1 2.100000
Thread 0:   a,b,x= 0 0 1.000000
************************************
Master thread doing serial work here
************************************
2nd Parallel Region:
Thread 2:   a,b,x= 2 0 3.200000
Thread 0:   a,b,x= 0 0 1.000000
Thread 3:   a,b,x= 3 0 4.300000
Thread 1:   a,b,x= 1 0 2.100000
```

We notice that the global variables `a` and `x` are `THREADPRIVATE`, while `b` is not. When the team executes the first parallel region, each thread gets its own copy of `a` and `x` , which is then maintained when the second parallel region is executed. The same is not true for `b`, which is re-initialized to 0;
### General Rules
Data in `THREADPRIVATE` objects is guaranteed to persist only if the dynamic threads mechanism is “turned off” and the number of threads in different parallel regions remains constant. The default setting of dynamic threads is undefined.

The `THREADPRIVATE` directive must appear after every declaration of a thread private variable/common block.
### Use cases
The `threadprivate` directive in OpenMP serves various use cases where you need each thread to have its own private copy of a variable that persists across multiple parallel regions. Here are some common use cases:

1. **Thread-Specific Data**: When you have data that needs to be unique and persistent to each thread throughout the execution of multiple parallel regions, `threadprivate` is useful. This could include thread-specific counters, thread-local caches, or any other per-thread state.
2. **Parallel Reductions**: In some cases, you might want to perform reductions across multiple parallel regions but need to maintain separate accumulation variables for each thread. `threadprivate` can be used to ensure that each thread has its own private accumulation variable that persists across parallel regions.
3. **Thread-Specific Configuration**: If you have configuration settings or parameters that are specific to each thread and need to remain constant throughout the execution of multiple parallel regions, `threadprivate` can be used to maintain thread-specific configurations.

Overall, `threadprivate` provides a convenient mechanism for managing thread-specific data that needs to persist across multiple parallel regions without the overhead of recreating or reallocating the data in each region.

### PRIVATE vs THREADPRIVATE

|                          | PRIVATE                                                     | THREADPRIVATE                                                    |
| ------------------------ | ----------------------------------------------------------- | ---------------------------------------------------------------- |
| Data Item                | Variable                                                    | Variable                                                         |
| Where is the Declaration | At the start of the region or work-sharing group            | In declarations of each routine using block or global file scope |
| Persistent?              | No                                                          | Yes                                                              |
| Extent                   | Lexical only - unless passed as an argument to a subroutine | Dynamic                                                          |
| Initialized              | Use FIRSTPRIVATE                                            | Use COPYIN                                                       |


