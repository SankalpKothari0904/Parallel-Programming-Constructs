# Synchronization Constructs
## Need For Synchronization
Consider a simple example where two threads on two different processors are both trying to increment a variable x at the same time (assume x is initially 0),

|                 | Thread1                                                              | Thread 2                                                             |
| --------------- | -------------------------------------------------------------------- | -------------------------------------------------------------------- |
| High Level Code | increment(x)  <br>{  <br>x = x + 1;  <br>}                           | increment(x)  <br>{  <br>x = x + 1;  <br>}                           |
| Assembly        | 10 LOAD A, (x address)  <br>20 ADD A, 1  <br>30 STORE A, (x address) | 10 LOAD A, (x address)  <br>20 ADD A, 1  <br>30 STORE A, (x address) |
**One possible execution sequence:**
1. Thread 1 loads the value of x into register A.
2. Thread 2 loads the value of x into register A.
3. Thread 1 adds 1 to register A
4. Thread 2 adds 1 to register A
5. Thread 1 stores register A at location x
6. Thread 2 stores register A at location x

The resultant value of x in this case would be 1, and not 2 (which was expected). To avoid situations like this, we need to synchronize the incrementing of x between the two threads to ensure that the correct result is produced.
## MASTER Directive
The `MASTER` directive specifies a region that is to be executed only by the master thread of the team. All other threads on the team skip this section of code.
There is no implied barrier associated with this directive.
### Format
```c++
#pragma omp master
structured_block
```
### General Rules
It is illegal to branch into or out of `MASTER` block.
## CRITICAL Directive
The `CRITICAL` directive specifies a region of code that must be executed by only one thread at a time.

If a thread is currently executing inside a `CRITICAL` region and another thread reaches that `CRITICAL` region and attempts to execute it, it will block until the first thread exits that `CRITICAL` region.

The optional name enables multiple different `CRITICAL` regions to exist: Names act as global identifiers. Different `CRITICAL` regions with the same name are treated as the same region. All `CRITICAL` sections which are unnamed, are treated as the same section.
### Format
```c++
#pragma omp critical [name]
structured_block
```
### General Rules
It is illegal to branch into or out of a `CRITICAL` block.
### Example
```c++
// In a file called critical.cpp
#include <stdio.h>
#include <omp.h>

int main() {
	int x;
	x = 0;

	#pragma omp parallel shared(x) 
	{
		#pragma omp critical 
		x = x + 1;	
	}
	printf("Value of x: %d\n", x);
	return 0;
}
```
Note that if we do not use the `#pragma omp critical` directive, the value of x printed on the screen would be unpredictable.
## BARRIER Directive
The `BARRIER` directive synchronizes all threads in the team.
When a `BARRIER` directive is reached, a thread will wait at that point until all other threads have reached that barrier. All threads then resume executing in parallel the code that follows the barrier.
### Format
```c++
#pragma omp barrier
```
### General Rules
All threads in a team (or none) must execute the `BARRIER` region.

The sequence of work-sharing regions and barrier regions encountered must be the same for every thread in a team.
## TASKWAIT Directive
The `TASKWAIT` construct specifies a *wait on the completion of child tasks generated since the beginning of the current task*.
### Format
```c++
#pragma omp taskwait
```
### General Rules
Because the `TASKWAIT` construct does not have a C language statement as part of its syntax, there are some restrictions on its placement within a program. 

The `TASKWAIT` directive may be placed only at a point where a base language statement is allowed. The `TASKWAIT` directive may not be used in place of the statement following an if, while, do, switch, or label.

An example on how the `TASKWAIT` directive may be used is provided in _task_fibonacci.cpp_
## ATOMIC Directive
The `ATOMIC` directive specifies that a specific memory location must be updated atomically, rather than letting multiple threads attempt to write to it. In essence, this directive *provides a mini-CRITICAL section*.

An important distinction of atomic from single is that it protects the memory locations for which actions are performed rather than ensuring the code must be run by a single thread; multiple atomic statements can be run together as long as they do not work on the same memory.
### ATOMIC vs CRITICAL
An OpenMP critical section offers complete versatility, capable of enveloping any arbitrary code block. However, this flexibility comes at a cost, as significant overhead is incurred each time a thread enters and exits the critical section, in addition to the inherent serialization cost.

Moreover, in OpenMP, all unnamed critical sections are treated as identical. Consequently, if one thread occupies an unnamed critical section, no other thread can enter any unnamed critical section concurrently. This limitation can be circumvented by utilizing named critical sections.

On the other hand, atomic operations present a more efficient alternative with significantly lower overhead. Leveraging hardware-specific features, such as atomic increment operations, eliminates the need for lock/unlock procedures upon entering and exiting the code line. This approach ensures that concurrent atomic operations are not blocked by a thread currently engaged in another atomic operation.

While the benefits include reduced overhead and non-blocking behavior for other atomic operations, the downside lies in the limited range of operations supported by atomic operations.
### Format
```c++
#pragma omp atomic
statement_expression
```

There are a few more nuances to the syntax here, and it is suggested that one refers to the official documentation [here](https://www.openmp.org/spec-html/5.0/openmpsu95.html)
