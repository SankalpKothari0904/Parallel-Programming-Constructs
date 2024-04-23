/******************************************************************************
* FILE: mpi_helloBsend.c
* DESCRIPTION:
*   MPI tutorial example code: Simple hello world program that uses blocking
*   send/receive routines.
******************************************************************************/
#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#define  MASTER	 0

int main (int argc, char *argv[])
{
    int  numtasks, taskid, len, partner, message;
    char hostname[MPI_MAX_PROCESSOR_NAME];
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

    /* need an even number of tasks  */
    if (numtasks % 2 != 0) {
    if (taskid == MASTER) 
        printf("Quitting. Need an even number of tasks: numtasks=%d\n", numtasks);
    } 

    else {
        if (taskid == MASTER) 
            printf("MASTER: Number of MPI tasks is: %d\n",numtasks);

        MPI_Get_processor_name(hostname, &len);
        printf ("Hello from task %d on %s!\n", taskid, hostname);

        /* determine partner and then send/receive with partner */
        if (taskid < numtasks/2) {
            partner = numtasks/2 + taskid;
            MPI_Send(&taskid, 1, MPI_INT, partner, 1, MPI_COMM_WORLD);
            MPI_Recv(&message, 1, MPI_INT, partner, 1, MPI_COMM_WORLD, &status);
            }
        else if (taskid >= numtasks/2) {
            partner = taskid - numtasks/2;
            MPI_Recv(&message, 1, MPI_INT, partner, 1, MPI_COMM_WORLD, &status);
            MPI_Send(&taskid, 1, MPI_INT, partner, 1, MPI_COMM_WORLD);
            }

        /* print partner info and exit*/
        printf("Task %d is partner with %d\n",taskid,message);
    }

    MPI_Finalize();

}

/*
 * This MPI program demonstrates a simple communication pattern between pairs of processes.
 * Each process identifies its partner, sends its task ID to the partner, receives the partner's task ID,
 * and then prints out the partner information.
 *
 * The main function initializes MPI, retrieves the task ID and total number of tasks, and checks if the number of tasks is even.
 * If the number of tasks is even, the MASTER process (task 0) prints out the total number of MPI tasks.
 * Each process then prints out its task ID and the name of the processor it's running on.
 *
 * Processes are divided into pairs, and each pair communicates with its partner:
 *   - If the process has a task ID less than half of the total number of tasks,
 *     it calculates its partner as `numtasks/2 + taskid`, sends its task ID to the partner, and receives the partner's task ID.
 *   - If the process has a task ID greater than or equal to half of the total number of tasks,
 *     it calculates its partner as `taskid - numtasks/2`, receives the partner's task ID, and sends its task ID to the partner.
 *
 * After communication, each process prints out information about its partner.
 *
 * Finally, MPI is finalized, and the program exits.
 */


