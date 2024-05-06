# Broadcasting a Python dictionary:
import time

start_time = time.time()
from mpi4py import MPI

comm = MPI.COMM_WORLD
rank = comm.Get_rank()

size = comm.Get_size()

if rank == 0:
    data = {'key1': [7, 2.72, 2 + 3j],
            'key2': ('abc', 'xyz'),
            'key3': list(range(10)),  # Large list
            'key4': {i: i ** 2 for i in range(10)}  # Large dictionary
            }
    print("Original data size:", len(data))
else:
    data = None

# Broadcast data from rank 0 to other processes
data = comm.bcast(data, root=0)

# Print received data size
if rank != 0:
    print("Received data size:", len(data))
    print(f"The data received is {data}")

if rank==0 :
    print(f"Number of processes in communicator {size}")
    end_time = time.time()
    print("Time taken:", end_time - start_time, "seconds")
