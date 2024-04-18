# Parallel Region Construct
This is the fundamental OpenMP parallel construct. A parallel region is a block of code that will be executed by multiple threads.

```c++
#pragma omp parallel [clause, ...]
{
... // Structured block
}
```

The `clause` can be one or more of `if(...)`, `shared(...)`, `private(...)`, `default(...)`, `reduction(...)`, `copyin(...)`, `num_threads(...)`, `firstprivate(...)`. These will be described in more detail later.

When a thread reaches a PARALLEL directive, it creates a team of threads and becomes the master of the team. The master is a member of that team and has thread number 0 within that team. Threads (say N) are numbered from `0` (master thread) to `N - 1`.

Starting from the beginning of this parallel region, the code is duplicated and all threads will execute that code.

There is an implied `barrier` at the end of a parallel section. Only the master thread continues execution past this point. If any thread terminates within a parallel region, all threads in the team will terminate, and the work done up until that point is undefined.

The number of threads in a parallel region is determined by the following factors, in order of precedence:
1. Evaluation of the `IF` clause
2. Setting of the `NUM_THREADS` clause
3. Use of the `omp_set_num_threads()` library function
4. Setting of the `OMP_NUM_THREADS` environment variable
5. Implementation default - usually the number of CPUs on a node, though it could be dynamic.
## Dynamic Threads
Use the `omp_get_dynamic()` library function to determine if dynamic threads are enabled.
If supported, the two methods available for enabling dynamic threads are:
1. The `omp_set_dynamic()` library routine
2. Setting of the `OMP_DYNAMIC` environment variable to TRUE

If not supported, a parallel region nested within another parallel region results in the creation of a new team, consisting of one thread, by default.
## Restrictions
- A parallel region must be a structured block that does not span multiple routines or code files.
- It is illegal to branch (`goto`) into or out of a parallel region.
- Only a single `IF` clause is permitted.
- Only a single `NUM_THREADS` clause is permitted.
- A program must not depend upon the ordering of the clauses.