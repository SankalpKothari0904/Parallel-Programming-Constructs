# OpenMPI in Java

Reference Paper: [Design and implementation of Java bindings in Open MPI](https://www.sciencedirect.com/science/article/abs/pii/S0167819116300758?via%3Dihub)

For full PDF - [Paper link](https://riunet.upv.es/bitstream/handle/10251/81655/ompi-java.pdf?sequence=3)

## Introduction

The paper highlights the increasing interest in using Java for high-performance computing (HPC), noting initial concerns about JVM performance which have since been diminished. Recent studies indicate Java's overhead is reasonable for computationally intensive tasks, especially with optimized numerical libraries like MTJ. Java offers built-in support for threads, and efforts are underway to utilize parallel primitives. However, adopting the MPI standard in Java is preferred due to its rich feature set, particularly in collective communication.

The paper introduces Java MPI bindings within Open MPI, integrating with MPI internals for simplicity and leveraging a JNI-based approach to contain complexity. It provides an overview of MPI and Java, demonstrates usage of Java bindings in Open MPI with examples, and discusses internal implementation details. Performance evaluation results are presented, and the paper concludes with remarks on the benefits of MPI adoption in Java for HPC applications.

## Previous and Ongoing related work

This work aims to improve the availability of the MPI in Java, a high-level library commonly used in HPC applications. MPI has multiple major flavors of communication, including point-to-point, one-sided, collective, and I/O. The MPI application programming interface (API) utilizes various types of handles that refer to underlying implementation objects, such as an MPI communicator. Open MPI is one of the most widely used MPI implementations, developed as a coordinated international effort.

Java's main distinguishable feature from C/C++ is that Java source files are compiled into an intermediate bytecode that is executed on a Java Virtual Machine (JVM), making Java programs portable to any system with a JVM without having to recompile. End users run Java applications via a Java Runtime Environment (JRE) installed on their computer, which contains the JVM.

The Java Native Interface (JNI) is extensively used in this work, allowing the application programmer to call native subroutines and libraries from Java and vice versa. JNI is often used to invoke numerical kernels optimized for the particular machine characteristics and would be much slower if implemented in Java. However, JNI breaks Java's spirit of automatic portability, as it requires recompiling the native code whenever the application wants to port the application to a new computer.
```
public class Win
{
    ...
    public Group getGroup() throws MPIException
    {
        MPI.check();
        return new Group(getGroup(handle));
    }
    private native long getGroup(long win) throws MPIException;
    ...
}
```
```
JNIEXPORT jlong JNICALL Java_mpi_Win_getGroup(JNIEnv *env, jobject jthis, jlong win)
{
    MPI_Group group;
    int rc = MPI_Win_get_group((MPI_Win)win, &group);
    ompi_java_exceptionCheck(env, rc);
    return (jlong)group;
}
```

*Example to illustrate the invocation of a JNI method from Java (top) and the corresponding JNI implementation in C (bottom)*

Open MPI's Java bindings address limitations of earlier attempts like mpiJava by providing a completely new implementation that integrates directly into the Open MPI distribution. This eliminates the need for JNI (Java Native Interface) and its associated portability issues, while guaranteeing compatibility with Open MPI. The design prioritizes modern Java practices and adheres to the MPI 3.0 specification, offering a comprehensive and well-integrated solution for developing parallel applications in Java using Open MPI.