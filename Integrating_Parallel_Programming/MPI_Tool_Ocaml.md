# MPI Tool for OCAML Programming Language

## Overview 

MPI is a popular library for distributed-memory parallel programming in SPMD (single program, multiple data) style.

MPI offers both point-to-point message passing and group communication operations (broadcast, scatter/gather, etc).

Several implementations of MPI are available, both for networks of Unix workstations and for supercomputers with specialized communication networks.

More info on MPI is available here.

Two popular, free implementations of MPI are MPICH and OpenMPI .

The module below also depends on the mpich compiler, hence a mpi program written in ocaml will be executed as :

```
$ ocamlc -I +ocamlmpi -o sendrecv mpi.cma sendrecv.ml
$ mpiexec -n 2 ./sendrecv 
```

Link to ocamlc : https://ocaml.org/manual/5.1/comp.html

### [OCamlMPI](https://github.com/coti/ocamlmpi?tab=readme-ov-file)

- OCamlMPI provides OCaml bindings for a large subset of MPI functions. The file mpi.mli in this directory lists the MPI functions provided, along with short documentation.

- Most communication functions come in five flavors:
    - one generic function operating on any data type  (e.g. Mpi.send)
    - four specialized functions for the following types:
              int         (Mpi.send_int)
              
              float       (Mpi.send_float
              
              int array   (Mpi.send_int_array)
              
              float array (Mpi.send_float_array)

- The data types that can be transmitted using the "generic"
communication functions are those that can be marshaled by the
Marshal.to_channel function (q.v.) with the Marshal.Closures option.

- That is:
  - all concrete data structures (base types, arrays, records, variant types)
  - function closures
  - but not objects
  - nor certain abstract types (in_channel, out_channel, Graphics.image)

- For Running OCamlMPI : follow the instructions in the link

**Examples of common MPI features** : 

- MPI Tags:  Messages are sent with an accompanying user-defined integer tag, to assist the receiving process in identifying the message.

- Mpi.send : This function sends data to a given remote process on a given communicator with a given tag. It takes the following arguments
    - Data to be sent
    - Rank of the destination process
    - Tag
    - Communicator that must be used for this communication

```
let token = 42 in
let my_tag = 1664 in
let dst = 1 in
Mpi.send token dst my_tag Mpi.comm_world
```

- Mpi.receive : This function receives data from a given remote process on a given communicator with a given tag. It takes the following arguments : 
    - Rank of the source process
    - Tag
    - Communicator that must be used for communication

```
let my_tag = 1664 in
let src = 0 in
token = receive src my_tag Mpi.comm_world ;
```

- Mpi.comm_rank : This function determines the rank of the current process on a given communicator. It takes the communicator as input and returns the rank of the current process. 

```
let rank = Mpi.comm_rank Mpi.comm_world in
```

- Mpi.comm_size :This function determines the size (ie, the number of processes) of a given communicator. It takes the communicator as argument

```
let size = Mpi.comm_size Mpi.comm_world in
```
- Some more examples can be found in the link provided, need to setup the ocamlmpi module.

### Flow of OCampMpi execution

- OCamlMPI provides bindings to the native MPI library through the use of OCaml's foreign function interface (FFI). Here's a general overview of how it works:

1. **FFI**: OCaml allows interfacing with code written in other languages, such as C, through its FFI mechanism. This mechanism enables OCaml code to call functions defined in external libraries and vice versa.

2. **Binding Generation**: OCamlMPI provides OCaml bindings for the MPI functions by generating OCaml code that interfaces with the C MPI library. This code defines OCaml functions that wrap the corresponding MPI functions, handling conversions between OCaml data types and C data types as needed.

3. **Compilation**: When you compile OCamlMPI-based code, the OCaml compiler (ocamlc or ocamlopt) compiles both the OCaml code and the generated C code into bytecode or native code, respectively.

4. **Linking**: During the linking stage, the OCaml compiler links the compiled OCaml code with the MPI library (e.g., MPICH or Open MPI) and any other necessary libraries. This allows the resulting executable to make calls to the MPI functions provided by the native MPI library.
5. **Execution**: When you run the compiled OCamlMPI program, it interacts with the native MPI library to perform message passing and other parallel computing tasks. The native MPI library handles the actual communication between processes running on different nodes in the cluster or computing environment.


```
ocamlc -I +ocamlmpi -o bcast mpi.cma unix.cma bcast.ml            

mpiexec -n 4 ./bcast                                          
```

- The above is a example of running the ocamlmpi file, where we provie the 