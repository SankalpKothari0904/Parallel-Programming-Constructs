## 1. [Hello World MPI Program](./Sample%20Programs/mpi_hello_world.c):

Demonstrates basic MPI setup to print "Hello world" from each MPI process. Initializes MPI, retrieves process count and rank, and obtains processor name.

Each process prints its processor name, rank, and total process count. Finalizes MPI environment.

## 2. [Blocking Pass Example 1](./Sample%20Programs/hello_bsend.c):

This MPI program demonstrates a simple communication pattern between pairs of processes. Each process identifies its partner, sends its task ID to the partner, receives the partner's task ID, and then prints out the partner information. 

The program initializes MPI, retrieves the task ID and total number of tasks, checks if the number of tasks is even, and prints out relevant information. After communication, each process prints out information about its partner. Finally, MPI is finalized, and the program exits.

## 3. [Non-Blocking Pass Example 1](./Sample%20Programs/hello_nbsend.c):

This MPI program demonstrates a simple communication pattern between pairs of processes using nonblocking send/receive routines. Each process identifies its partner, sends its task ID to the partner, receives the partner's task ID, and then prints out the partner information. 

The program initializes MPI, retrieves the task ID and total number of tasks, checks if the number of tasks is even, and prints out relevant information. After communication, each process prints out information about its partner. Finally, MPI is finalized, and the program exits.

## 4. [Sum of Elements in an Array](./Sample%20Programs/mpi_array.c):

This MPI program divides an array among multiple processes to perform parallel summation. Each process receives a portion of the array from the master process, performs local computations, and sends the results back to the master. 

The master process initializes the array, distributes portions to other processes, collects results, and computes the final sum. The program helps to demonstrate how to use MPI communication routines for sending and receiving data among processes.

Serialized version of the code - [Sum in Array](./Sample%20Programs/mpi_array_ser.c)

## 5. [Matrix Multiplication](./Sample%20Programs/mpi_mtrx_mult.c):

This MPI program performs matrix multiplication using parallel processing. 

The master task distributes matrix data to worker tasks, and each worker computes a portion of the resulting matrix. 
The master task collects results from worker tasks and prints the final matrix.

Serialized version of the code - [Matrix Mult](./Sample%20Programs/ser_mtrx_mult.c)

## 6. [Calculation of Pi by Dartboard Method](./Sample%20Programs/mpi_pi_calc.c):

This MPI program calculates the value of pi using a "dartboard" algorithm. All processes contribute to the calculation, with the master task averaging the values for pi. 

This code uses low-level sends and receives to collect results. The dartboard algorithm simulates throwing darts randomly at a square dartboard circumscribed by a unit circle. By counting the number of darts that land inside the circle, an approximation of pi can be calculated.

Serialized version of the code - [Pi calculation](./Sample%20Programs/ser_pi_calc.c)

## 7. [Primality Testing of a Large set of Numbers](./Sample%20Programs/mpi_primes.c):

This MPI program calculates prime numbers using embarrassing parallelism. Each task checks a range of numbers for primality, with the total number of tasks being even and defined by `LIMIT`. The stride method evenly distributes the workload, skipping even numbers to enhance efficiency.

The `isprime` function checks if a number is prime, while the main loop increments the prime counter `pc` and stores the latest prime `foundone`. Collective communication operations are used to reduce the number of primes found and determine the largest prime. Finally, the program prints the largest prime and the total number of primes discovered, along with the elapsed wall clock time.

Serialized version of the code - [Prime checker](./Sample%20Programs/ser_primes.c)

## 8. [Program Displaying a Bug - Example 1](./Sample%20Programs/mpi_bug1.c):

This MPI program has a bug that causes it to hang. The issue arises from a deadlock scenario where both tasks are waiting to receive a message from each other, resulting in a standstill. Task 0 sends a message to task 1 and then waits to receive a response. 

Meanwhile, task 1 is also waiting to receive a message from task 0 before sending its response. This mutual waiting leads to a deadlock. To resolve the bug, we need to ensure that one task sends a message before the other waits to receive it.

## 9. [Program Displaying a Bug - Example 2](./Sample%20Programs/mpi_bug2.c):

This MPI program is intended to calculate the sum of elements in an array distributed among multiple MPI processes. However, it contains a bug that leads to incorrect results for the final sum compared to the expected sum.

The bug arises from incomplete updates performed by each MPI task on its assigned chunk of the array. The `update` function is responsible for iterating over the chunk, performing the addition, and keeping track of the local sum. However, it fails to properly update all elements of the chunk, resulting in an inaccurate final sum.

## 10. [Program Displaying a Bug - Example 3](./Sample%20Programs/mpi_bug3.c):

This MPI program exhibits unsafe behavior due to potential deadlock. The behavior of the program varies depending on the platform and MPI library being used.

The bug arises from the potential for deadlock caused by an indefinite loop in the sending task (`rank == 0`) and the lack of synchronization between the sending and receiving tasks (`rank == 1`). The sending task continuously sends messages without any breaks, leading to a potential accumulation of messages in the MPI communication buffer. 

Meanwhile, the receiving task is busy performing computational work without receiving or processing the messages, resulting in buffer overflow and deadlock.
