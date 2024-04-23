# OpenMP Like Tools

## Overview

OpenMp is widely used for implementing parallel programming constructs in a local environment/cluster and is considered an industry standard. The OpenMP documentation provides directives and functions only for C/C++ and Fortran. Hence we will look at how OpenMP like tools are being developed in other programming languages and try to come to a generalized approach on building programming languages that support parallelism.

## Exploration of tools

### [JOMP](https://dl.acm.org/doi/pdf/10.1145/337449.337466)

The paper describes a prototype implementation of an OpenMP-like set of directives and library routines implemented completely in java, including the compiler and runtime library used in JOMP.

- It presents a high level abstraction of the POSIX threads, like how it is in the original implementation and aims to help the programmer write code that is closer to the sequential version of the parallel code and avoids the need to use low level thread functions.

- To make use of the directives, the paper adopts the approach used in Fortran where the directives are embedded into comments , i.e using // .


**Key Features of JOMP**

- **Examples 1**: The parallel directive

```
//omp parallel [if(<cond>)] 
//omp [default (sharedlnone)] [shared(<vars>)] 
//omp [private(<vars>)] [firstprivate(<vars>)] 
//omp [reduction(<operation>:<vars>)] 
<Java code block> 
```
- **Example 2** : The sections and section directive 
```
//omp sections [nowait] 
{ 
    //omp section 
    <code block> 
    
    //omp section 
    <code block>

    ... // add more section based on requirements 
} 
```
```
//omp parallel shared(a,b,c) 
{ 
//omp sections 
    { 
        //omp section 
        a.init(); 
        
        //omp section 
        b.init(); 
        
        //omp section 
        c.init(); 
    } 
} 
```
- **Example 3** : Parallel Loop
```
//omp parallel shared(a,b) 
{ 
    //omp for 
    for (i=1; i<n; i++){ 
        b[i] = (a[i] + a[i-1]) * 0.5; 
    } 
} 
```

- JOMP provides other directives like the master, single, critical ,and the barrier directive which have the same functionality as its Fortran counterpart. Also has support for orphan directives.

- It also provides library functions to get essential metadata like number of threads, max threads, thread number, etc.

- **Examples** : getNumThreads, setNumThreads(n), getMaxThreads(), getThreadNum(), inParallel() .


**JOMP Compiler**

Seems to override the javaCC compiler its runtime library methods and output modified code, which includes calls to the runtime library to implement appropriate parallelism. 

- Example of a simple "Hello World" JOMP Program
```
import jomp. runtime. * ; 
public class Hello { 
    public static void main (String argv[]){ 
        int myid; 
        //omp parallel private(myid) 
        { 
            myid = DMP.getThreadNumO ; 
            System.out.println("Hello from " + myid) ; 
        } 
    } 
} 
```
- Resulting "Hello World" Java Program after passing through the JOMP compiler

```
import jomp.runtime.*; 
public class Hello { 
    public static void main (String argyll) { 
        int myid; 
        __omp_class_0 __omp_obj_0 = new __omp_class_0(); 
        try { 
            jomp.runtime.0MP.doParallel(__omp_obj_0); 
        } 
        catch(Throwable __omp_exception) { 
            System.err.println("0MP Warning: exception in parallel region") ; 
        } 
    } 
    
    private static class __omp_class_0 
            extends jomp.runtime.BusyTask { 
        public void ge(int __omp_me) throws Throwable { 
            int myid; 
            myid = 0MP.getThreadNumO; 
            System.out.println("Hello from " + myid); 
        } 
    } 
} 
```


**JOMP Runtime Library**

It provides the necessary functionality to support parallelism in terms of Java's native threads model. The package **jomp.runtime** contains a library of classes and routines used by compiler-generated code. 

- The core of the library is the **OMP class** which contains the routines used by the compiler to implement parallelism in terms of Java's native thread model.

- Each thread has a unique thread id which can be queried using the **static currentThread()** method of the Thread class.

- The initialization step of the runtime environment consists of 2 parts: 
    - **Static initialization** where the OMP class reads the system properties like jomp.threads [number of threads to use during execution], jomp.schedule, etc.
    - A **start() method** is called when the first paralle method is encountered[directives] and initializes:
        - Thread specific data
        - Creating team of threads.
        - These threads are then set to be running and wait to be assigned a task based on the scheduler [static or dynamic].

- **Parallel Execution Model :**
    - The system involves parallel execution of tasks using threads.
    - Tasks are instances of the BusyTask class, each with a go() method.
    - Threads (except the master) are instances of BusyThread, extending Thread.
    - Non-master threads execute a loop, reaching a global barrier, executing their task, and then reaching the barrier again.

- **Master-Worker Interaction :**
    - During serial regions, threads pause at the first barrier, waiting for the master thread.
    - The master thread calls **doParallel()**, setting up tasks for each thread and reaching the global barrier.
    - Other threads execute their tasks, and the master executes its own task before reaching the barrier again.

- **Daemon Threads and Termination :**
    - All non-master threads are daemon threads, meaning they terminate if the master thread does.
    - An implicit barrier at the end of every parallel region ensures the master thread waits for others to finish before proceeding with serial execution.

- **Barriers Class :**

    - The Barrier class implements a simple, static **4-way tournament barrier** for an arbitrary number of threads.
    - The **DoBarrier()** method takes as a parameter a thread number, and causes the calling thread to block until it has been called the same number of times for each possible thread number. 
    - The 0MP class maintains a Barrier reference for each thread pointing to a single barrier for each team. The OMP.doBarrier() method reaches the 
    appropriate barrier for the calling thread. 

- **Reduction Class :**

    - The Reduction class is used to implement the reduction directive. It provides methods for the different reductions on like **+,***. 
    - A call to a reduction method causes the calling thread to wait until all other threads have called the routine with their respective values.
    - The OMP class maintains a reference to the Reducer class for each thread where each thread points to the common **Reducer** of the team.

- **Scheduling :**

    - Scheduling is handled by the LoopData and the Ticketer class based on the required functionality.
        - **LoopData** class : A LoopData object is used to store information about a loop or a chunk of a loop. It contains details of the start, step and stop of a loop.
        - **Ticketer** class : It facilitates the dynamic allocation of work to different threads.

- **Locking Mechanism :** 

    - There are 2 types of locks: 
        - **jomp.runtime.Lock** class : This class implements a simple mutual exclusion lock [It ensures that no two processes or threads can be in a critical section (a part of code that accesses shared resources) simultaneously.]

        - **jomp.runtime.NestLock** class : This class implements a nested lock [allows a thread to acquire a lock it already holds without causing a deadlock]. Unlike a simple lock, a Nested Lock can be reacquired multiple times by the same thread. The lock is only released for other threads to acquire when it has been released as many times as it was acquired2.

    - Both the locks implement the following methods : 
        - **set()** : Attempts to acquire exclusive ownership of the lock. If the lock is held by another thread, then the calling thread blocks until it is released
        - **unset()** : Releases ownership of a lock. 
        - **test()** : Tests if it is possible to acquire a lock immediately without blocking.


### [OMP4J - OpenMP Library For Java](https://dl.acm.org/doi/abs/10.5555/3636517.3636530)









