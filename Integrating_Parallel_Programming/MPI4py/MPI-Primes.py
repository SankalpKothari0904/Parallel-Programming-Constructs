from mpi4py import MPI
import math

LIMIT = 2500000
FIRST = 0

def isprime(n):
    if n > 10:
        squareroot = int(math.sqrt(n))
        for i in range(3, squareroot + 1, 2):
            if n % i == 0:
                return 0
        return 1
    else:
        return 0

comm = MPI.COMM_WORLD
rank = comm.Get_rank()
ntasks = comm.Get_size()

if ntasks % 2 != 0 or LIMIT % ntasks != 0:
    print("Sorry - this exercise requires an even number of tasks.")
    print("evenly divisible into {}. Try 4 or 8.".format(LIMIT))
    comm.Abort()

start_time = MPI.Wtime()
mystart = rank * 2 + 1
stride = ntasks * 2
pc = 0
foundone = 0

if rank == FIRST:
    print("Using {} tasks to scan {} numbers".format(ntasks, LIMIT))
    pc = 4
    for n in range(mystart, LIMIT + 1, stride):
        if isprime(n):
            pc += 1
            foundone = n

    pcsum = comm.reduce(pc, op=MPI.SUM, root=FIRST)
    maxprime = comm.reduce(foundone, op=MPI.MAX, root=FIRST)
    end_time = MPI.Wtime()
    if rank == FIRST:
        print("Done. Largest prime is {}. Total primes {}".format(maxprime, pcsum))
        print("Wallclock time elapsed: {:.6f} seconds".format(end_time - start_time))

else:
    for n in range(mystart, LIMIT + 1, stride):
        if isprime(n):
            pc += 1
            foundone = n

    comm.reduce(pc, op=MPI.SUM, root=FIRST)
    comm.reduce(foundone, op=MPI.MAX, root=FIRST)
    
MPI.Finalize()
