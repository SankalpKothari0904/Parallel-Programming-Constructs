# Python objects with non-blocking communication:
from mpi4py import MPI
import time

comm = MPI.COMM_WORLD
rank = comm.Get_rank()

if rank == 0:
    data = {'a': 7, 'b': 3.14}
    print("Rank 0 sending data...")
    req = comm.isend(data, dest=1, tag=11)
    # Adding a delay to simulate computation
    time.sleep(1)
    print("Rank 0 continues after sending data")
    req.wait()  # Wait for the communication to complete
    print("Rank 0 communication completed")
elif rank == 1:
    print("Rank 1 receiving data...")
    req = comm.irecv(source=0, tag=11)
    # Adding a delay to simulate computation
    time.sleep(1)
    print("Rank 1 continues after receiving data")
    data = req.wait()  # Wait for the communication to complete
    print("Rank 1 communication completed")

