# Design Patterns In OpenMP
## Single Program Multiple Data (SPMD)
- By creating a team of N threads, you can explicitly manage the distribution of work among threads using the thread's rank (ranging from 0 to N - 1) and the total number of threads, N.
- Like most multithreaded programming environments, OpenMP operates as a shared memory API. All threads are part of a single process and share the process's heap. Variables outside a parallel construct are shared by default within the construct, while variables created within the construct are private by default (meaning each thread in the team has its own copy).
- It's considered good practice in OpenMP programming to clearly specify the status of variables within an OpenMP construct.
## Loop Level Parallelism
- The Loop Level Parallelism pattern is where most people start with OpenMP.
- Parallelism is introduced through a single with statement to express the parallel for construct. This construct creates a team of threads and then distributes the iterations of the loop among the threads. To accumulate the summation across loop iterations, we include the reduction clause.
## Tasks And Divide And Conquer
- This important pattern is heavily used by more advanced parallel programmers.
- The general idea is to define three basic phases of the algorithm: split, compute, and merge.
	- The split phase recursively divides a problem into smaller subproblems.
	- After enough splits, the subproblems are small enough to directly compute in the compute phase.
	- The final phase merges subproblems together to produce the final answer.