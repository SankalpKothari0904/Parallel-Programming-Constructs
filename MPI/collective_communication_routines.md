# Collective Communication Routines

#### Types of Collective Operations:

- **Synchronization**: Processes wait until all members of the group reach the synchronization point.
- **Data Movement**: Includes broadcast, scatter/gather, and all-to-all communication.
- **Collective Computation (Reductions)**: Involves one member collecting data from others and performing operations like minimum, maximum, addition, multiplication, etc.

Some sample collective communication operations -

![collective_comm](collective_comm.gif)

#### Scope:

Collective communication routines involve all processes within a communicator's scope. By default, all processes are part of the communicator MPI_COMM_WORLD. Programmers can define additional communicators.

Failure to ensure participation of all communicator members can lead to unexpected behavior or program failure.

#### Programming Considerations and Restrictions:

- Collective communication routines do not accept message tag arguments.
- Subset operations are achieved by partitioning subsets into new groups and attaching them to new communicators.
- These routines are compatible only with MPI predefined datatypes and not with MPI Derived Data Types.
- MPI-2 extended most collective operations to support data movement between intercommunicators, which is not covered here.
- In MPI-3, collective operations can be blocking or non-blocking; however, this tutorial covers only blocking operations.

### Collective Communication Routines

**MPI_Barrier**

A synchronization operation that creates a barrier, ensuring all tasks in a group reach the same point before proceeding.

```
MPI_Barrier (comm)
```

**MPI_Bcast**

A data movement operation that broadcasts a message from the process with rank "root" to all other processes in the group.

```
MPI_Bcast (&buffer,count,datatype,root,comm)
```


**MPI_Scatter**

Distributes distinct messages from a single source task to each task in the group.

```
MPI_Scatter (&sendbuf,sendcnt,sendtype,&recvbuf,recvcnt,recvtype,root, comm)
```

**MPI_Gather**

Gathers distinct messages from each task in the group to a single destination task. This is the reverse operation of MPI_Scatter.

```
MPI_Gather (&sendbuf,sendcnt,sendtype,&recvbuf,recvcount,recvtype,root, comm)
```

**MPI_Reduce**

A collective computation operation that applies a reduction operation on all tasks in the group and places the result in one task.

```
MPI_Reduce (&sendbuf,&recvbuf,count,datatype,op,root,comm)
```
-------------------------------------------------------------
| MPI Reduction Operation | C Data Types           |
|-------------------------|------------------------|
| **MPI_MAX**             | maximum (integer, float)        |
| **MPI_MIN**             | minimum (integer, float)        |
| **MPI_SUM**             | sum (integer, float)            |
| **MPI_PROD**            | product (integer, float)        |
| **MPI_LAND**            | logical AND (integer)           |
| **MPI_BAND**            | bit-wise AND (integer, MPI_BYTE)|
| **MPI_LOR**             | logical OR (integer)            |
| **MPI_BOR**             | bit-wise OR (integer, MPI_BYTE) |
| **MPI_LXOR**            | logical XOR (integer)           |
| **MPI_BXOR**            | bit-wise XOR (integer, MPI_BYTE)|
| **MPI_MAXLOC**          | max value and location (float, double, long double) |
| **MPI_MINLOC**          | min value and location (float, double, long double) |
---------------------------------------------------------------------------------


**MPI_Reduce_scatter**

Collective computation operation + data movement. First does an element-wise reduction on a vector across all tasks in the group. Next, the result vector is split into disjoint segments and distributed across the tasks. This is equivalent to an MPI_Reduce followed by an MPI_Scatter operation. 

![image](MPI_Reduce_scatter.gif)

```
MPI_Reduce_scatter (&sendbuf,&recvbuf,recvcount,datatype,op,comm)
```

**MPI_Alltoall**

Data movement operation. Each task in a group performs a scatter operation, sending a distinct message to all the tasks in the group in order by index.

```
MPI_Alltoall (&sendbuf,sendcount,sendtype,&recvbuf,recvcnt,recvtype,comm)
```

**MPI_Scan**

Performs a scan operation with respect to a reduction operation across a task group. 

![image](MPI_Scan.gif)

```
MPI_Scan (&sendbuf,&recvbuf,count,datatype,op,comm)
```

### Examples

```
#include "mpi.h"
#include <stdio.h>
#define SIZE 4

main(int argc, char *argv[])  {
int numtasks, rank, sendcount, recvcount, source;
    float sendbuf[SIZE][SIZE] = {
        {1.0, 2.0, 3.0, 4.0},
        {5.0, 6.0, 7.0, 8.0},
        {9.0, 10.0, 11.0, 12.0},
        {13.0, 14.0, 15.0, 16.0}  };
    float recvbuf[SIZE];

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

    if (numtasks == SIZE) {
        // define source task and elements to send/receive, then perform collective scatter
        source = 1;
        sendcount = SIZE;
        recvcount = SIZE;
        MPI_Scatter(sendbuf,sendcount,MPI_FLOAT,recvbuf,recvcount,
                    MPI_FLOAT,source,MPI_COMM_WORLD);

        printf("rank= %d  Results: %f %f %f %f\n",rank,recvbuf[0],
            recvbuf[1],recvbuf[2],recvbuf[3]);
    }
    else
        printf("Must specify %d processors. Terminating.\n",SIZE);

    MPI_Finalize();
}
```

Sample program output:

```
rank= 0  Results: 1.000000 2.000000 3.000000 4.000000
rank= 1  Results: 5.000000 6.000000 7.000000 8.000000
rank= 2  Results: 9.000000 10.000000 11.000000 12.000000
rank= 3  Results: 13.000000 14.000000 15.000000 16.000000
```
