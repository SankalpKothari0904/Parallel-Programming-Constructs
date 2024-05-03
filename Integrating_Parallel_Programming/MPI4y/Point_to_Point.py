# Python objects (pickle under the hood):

# this code demonstrates simple point-to-point communication between two processes (rank 0 and rank 1) using MPI. 
# Process 0 sends a dictionary to process 1, which then receives it.

from mpi4py import MPI

comm = MPI.COMM_WORLD
rank = comm.Get_rank()

if rank == 0:
    data = {'a': 7, 'b': 3.14}
    comm.send(data, dest=1, tag=11)
elif rank == 1:
    data = comm.recv(source=0, tag=11)