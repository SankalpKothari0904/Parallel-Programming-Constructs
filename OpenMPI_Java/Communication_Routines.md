# Communication Routines in OpenMPI for Java

## Point-to-Point Communication:

### Send and Receive:
Java MPI provides `Send` and `Recv` methods for sending and receiving messages between processes. These methods allow processes to exchange data with each other.

### Non-blocking Operations:
Java MPI also supports non-blocking operations like `Isend`, `Irecv`, `Wait`, and `Test` for asynchronous communication. These methods allow processes to continue execution while waiting for communication to complete.

```
Comm comm = MPI.COMM_WORLD;

int me = comm.getRank();

if(me == 0) {
    comm.send(data, 5, MPI.DOUBLE, 1, 1);
} else if(me == 1) {
    Status status = comm.recv(data, 5, MPI.DOUBLE, MPI.ANY_SOURCE, 1);
    int count = status.getCount(MPI.DOUBLE);
    int src = status.getSource();
    System.out.println("Received "+ count +" values from "+ src);
}
```

## Collective Communication:

### Broadcast:
The `Bcast` method broadcasts data from one process to all other processes in a communicator. It is commonly used for distributing configuration or global parameters.

### Scatter and Gather:
Java MPI provides `Scatter` and `Gather` methods for distributing data from one process to all other processes and vice versa. These methods are useful for parallelizing data processing tasks.

### Reduce:
The `Reduce` method performs a reduction operation (e.g., sum, min, max) across all processes in a communicator and stores the result in one process. It is commonly used for aggregating data from multiple processes.

### All-to-All:
Java MPI provides `Allgather`, `Allreduce`, and `Alltoall` methods for communication patterns where all processes exchange data with all other processes. These methods are useful for collective computations.

```
public static void main(String args[]) throws MPIException {
    MPI.Init(args);
    int rank = MPI.COMM_WORLD.getRank(),
    size = MPI.COMM_WORLD.getSize(),

    nint = 100; // Intervals.
    double h = 1.0 / (double)nint,
    sum = 0.0;
    
    for(int i = rank + 1; i <= nint; i += size) {
        double x = h * ((double)i - 0.5);
        sum += (4.0 / (1.0 + x * x));
    }
    
    double sBuf[] = { h * sum },
    rBuf[] = new double[1];
    
    MPI.COMM_WORLD.reduce(sBuf, rBuf, 1, MPI.DOUBLE, MPI.SUM, 0);
    
    if(rank == 0) System.out.println("PI: "+ rBuf[0]);
    
    MPI.Finalize();
}
```

## One-Sided Communication:

### Put and Get:
Java MPI supports one-sided communication operations like `Put` and `Get` for accessing remote memory without explicit synchronization. These methods allow processes to read from and write to remote memory locations directly.

## Intra and Inter Communicators:

### Intra-communicators:
These communicators include processes within the same MPI job. They can be created using `MPI.COMM_WORLD` and are typically used for communication within a single MPI application.

### Inter-communicators:
These communicators involve processes from different MPI jobs. They can be created using `Create` or `Split` methods and are used for communication between separate MPI applications or groups of processes.
