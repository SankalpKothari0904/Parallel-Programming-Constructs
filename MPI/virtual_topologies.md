# Virtual Topologies

## Introduction

In MPI programming, virtual topologies help organize processes for easier communication. Let's explore what they are, why they're useful, and how they're used.

## What Are Virtual Topologies?

In MPI, a virtual topology represents how MPI processes are organized into various geometric shapes. These shapes could be simple, like a one-dimensional array, or more complex, like a two-dimensional grid or a graph.

We can think of them as a way to organize MPI processes into shapes like grids or graphs. They make it easier to talk to each other, simplifying parallel programming.

MPI topologies are virtual, meaning they may not directly reflect the physical layout of the parallel machine. Instead, they're constructed based on the logical organization of processes within MPI communicators and groups.

The programmer is responsible for programming these virtual topologies according to the requirements of their application

## Why Use Them?

### Convenience
Virtual topologies match common communication patterns, making it easier to write code. For example, grids are great for neighbors talking to each other.

### Communication Efficiency

Some hardware architectures may impose penalties for communications between successively distant "nodes".

Virtual Topologies help speed up communication between processes by organizing them effectively, especially on different hardware.

### Example:

A simplified mapping of processes into a Cartesian virtual topology appears below:

![topology](Images/Cartesian_topology.gif)

## Types of Virtual Topologies

### Cartesian (Grid) Topology
Processes are organized in a grid, handy for structured communication like neighbor chats.

### Graph Topology
Processes are like dots connected by lines, allowing for flexible communication patterns.

## Key MPI Topology Functions

1. **MPI_Cart_create**: Sets up a grid for processes to talk.
2. **MPI_Cart_coords**: Figures out where a process is in the grid.
3. **MPI_Cart_rank**: Finds the number of a process in the grid.
4. **MPI_Cart_shift**: Helps find neighboring processes.
5. **MPI_Graph_create**: Sets up a general graph for processes to connect.
6. **MPI_Dims_create**: Figures out grid dimensions based on the number of processes.

These functions make it easy to set up communication patterns. For example, a 2D grid is perfect for some problems, while a graph might work better for others.

Using virtual topologies in MPI makes parallel programming simpler and more efficient.

### Code examples

Create a 4 x 4 Cartesian topology from 16 processors and have each process exchange its rank with four neighbors.

#### Cartesian Virtual Topology Example

```
#include "mpi.h"
#include <stdio.h>
#define SIZE 16
#define UP    0
#define DOWN  1
#define LEFT  2
#define RIGHT 3

int main(int argc, char *argv[])  {
    int numtasks, rank, source, dest, outbuf, i, tag=1,
        inbuf[4]={MPI_PROC_NULL,MPI_PROC_NULL,MPI_PROC_NULL,MPI_PROC_NULL,},
        nbrs[4], dims[2]={4,4},
        periods[2]={0,0}, reorder=0, coords[2];

    MPI_Request reqs[8];
    MPI_Status stats[8];
    MPI_Comm cartcomm;   // required variable

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

    if (numtasks == SIZE) {
        // create cartesian virtual topology, get rank, coordinates, neighbor ranks
        MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, reorder, &cartcomm);
        MPI_Comm_rank(cartcomm, &rank);
        MPI_Cart_coords(cartcomm, rank, 2, coords);
        MPI_Cart_shift(cartcomm, 0, 1, &nbrs[UP], &nbrs[DOWN]);
        MPI_Cart_shift(cartcomm, 1, 1, &nbrs[LEFT], &nbrs[RIGHT]);

        printf("rank= %d coords= %d %d  neighbors(u,d,l,r)= %d %d %d %d\n",
                rank,coords[0],coords[1],nbrs[UP],nbrs[DOWN],nbrs[LEFT],
                nbrs[RIGHT]);

        outbuf = rank;

        // exchange data (rank) with 4 neighbors
        for (i=0; i<4; i++) {
            dest = nbrs[i];
            source = nbrs[i];
            MPI_Isend(&outbuf, 1, MPI_INT, dest, tag,
                    MPI_COMM_WORLD, &reqs[i]);
            MPI_Irecv(&inbuf[i], 1, MPI_INT, source, tag,
                    MPI_COMM_WORLD, &reqs[i+4]);
        }

        MPI_Waitall(8, reqs, stats);

        printf("rank= %d \t\t\t\t inbuf(u,d,l,r)= %d %d %d %d\n",rank,inbuf[UP],inbuf[DOWN],inbuf[LEFT],inbuf[RIGHT]);  
    }
    else
        printf("Must specify %d processors. Terminating.\n",SIZE);

    MPI_Finalize();
}
```

Sample program output: (partial)

```
rank=   0 coords=  0 0 neighbors(u,d,l,r)=  -1  4 -1  1
rank=   0                  inbuf(u,d,l,r)=  -1  4 -1  1
rank=   8 coords=  2 0 neighbors(u,d,l,r)=   4 12 -1  9
rank=   8                  inbuf(u,d,l,r)=   4 12 -1  9
rank=   1 coords=  0 1 neighbors(u,d,l,r)=  -1  5  0  2
rank=   1                  inbuf(u,d,l,r)=  -1  5  0  2
rank=  13 coords=  3 1 neighbors(u,d,l,r)=   9 -1 12 14
rank=  13                  inbuf(u,d,l,r)=   9 -1 12 14
...
...
rank=   3 coords=  0 3 neighbors(u,d,l,r)=  -1  7  2 -1
rank=   3                  inbuf(u,d,l,r)=  -1  7  2 -1
rank=  11 coords=  2 3 neighbors(u,d,l,r)=   7 15 10 -1
rank=  11                  inbuf(u,d,l,r)=   7 15 10 -1
rank=  10 coords=  2 2 neighbors(u,d,l,r)=   6 14  9 11
rank=  10                  inbuf(u,d,l,r)=   6 14  9 11
rank=   9 coords=  2 1 neighbors(u,d,l,r)=   5 13  8 10
rank=   9                  inbuf(u,d,l,r)=   5 13  8 10
```
