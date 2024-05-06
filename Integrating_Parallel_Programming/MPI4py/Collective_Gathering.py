# Gathering Python objects:

from mpi4py import MPI

comm = MPI.COMM_WORLD
size = comm.Get_size()
rank = comm.Get_rank()

data = (rank+1)**2

# Gather the data
data = comm.gather(data, root=0)

# Print data for each process
print("Process", rank, "has data:", data)

if rank == 0:
    for i in range(size):
        assert data[i] == (i+1)**2
