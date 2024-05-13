# Parallel-Programming-Constructs
This is a repository for the course project for CS 754 - Programming Languages at IIIT - Bangalore.

## Author's Remarks
We realized during the course of this project that in order to understand how parallel programming constructs can be designed and implemented, it is essential to become familiar with the fundamentals of parallel programming. In an attempt to do so, we have thoroughly explored OpenMP and MPI, two of the most widely used APIs and specifications for parallel computing. This was done by conducting an elaborate survey on the web, and identifying useful resources. Considering the depth of the subject, a detailed documentation has been written and added to this repository.

Realizing that it could possibly be a challenge to go through the entire repository in a short span of time, we have summarized the key ideas and concepts from the project in our report, which is also available in the repository. Finally, one may view the presentation slides (also available in the repository) for a very quick, albeit a shallow glance at our work.

In case of any queries, feel free to contact us through our college email addresses.

## How To Navigate This Repository
- For details related to OpenMP, go [here](https://github.com/Vidhish-Trivedi/Parallel-Programming-Constructs/tree/main/OpenMP) and use the README as an index.
- For details related to MPI, go [here](https://github.com/Vidhish-Trivedi/Parallel-Programming-Constructs/tree/main/MPI) and use the README as an index.
- The `/Experiments` directory [(here)](https://github.com/Vidhish-Trivedi/Parallel-Programming-Constructs/tree/main/Experiments) contains several programs and algorithms implemented in both serial and parallel manner, along with a running time comparison between those. A naive analysis using Python is also done, which can be viewed in the included Jupyter notebook.
- The `/Integrating_Parallel_Programming` directory [(here)](https://github.com/Vidhish-Trivedi/Parallel-Programming-Constructs/tree/main/Integrating_Parallel_Programming) contains documentation and information on several tools and frameworks through which one can incorporate parallel programming constructs from OpenMP and MPI into languages like Java, OCaml, and Python. The directory also contains sample code files.
- The directory `/OpenMPI_Java` [(here)](https://github.com/Vidhish-Trivedi/Parallel-Programming-Constructs/tree/main/OpenMPI_Java) contains information on how we can use Java bindings for MPI through JNI.
- The directory `/PyOMP` [(here)](https://github.com/Vidhish-Trivedi/Parallel-Programming-Constructs/tree/main/PyOMP) contains information on a prototype system for bypassing Python's GlobalInterpreterLock (GIL) and access the full potential of multithreading in Python using OpenMP directives.


## Authors

- [@Vidhish-Trivedi](https://github.com/Vidhish-Trivedi)
- [@KalyanRam1234](https://github.com/KalyanRam1234)
- [@SankalpKothari0904](https://github.com/SankalpKothari0904)

## License
[MIT](https://choosealicense.com/licenses/mit/)
