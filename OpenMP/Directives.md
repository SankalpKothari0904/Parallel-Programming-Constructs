# C/C++ OpenMP Directives
## Directive Syntax
```c++
/*
#pragma omp directive-name [clause, ...] newline
*/

// Example
#pragma omp parallel private(x, y) shared(z)
```

- `#pragma omp`: Required for all OpenMP C/C++ directives.
- `directive-name`: A valid OpenMP directive must appear after the pragma and before any clauses.
- `[clause, ...]`: Optional, clauses can be in any order, and repeated as necessary unless otherwise restricted.
- `newline`: Required, should precede the structured block enclosed by the directive.
### General Rules
- Case sensitive.
- Directives follow conventions of the C/C++ standards for compiler directives.
- Only one directive-name may be specified per directive.
- Each directive applies to at most one succeeding statement, which must be a structured block.
- Long directive lines can be “continued” on succeeding lines by escaping the newline character with a backslash ("\") at the end of a directive line.
## OpenMP Directive Scoping
### Static Extent (Lexical)
The static extent of an OpenMP directive extends to the code textually enclosed between the beginning and the end of a structured block following a directive.

The static extent of a directives does not span multiple routines or code files.
### Orphaned Directive
An OpenMP directive that appears independently from another enclosing directive is said to be an orphaned directive. It exists outside of another directive’s static (lexical) extent.

An orphaned directive can span routines and possibly code files.
### Dynamic Extent
The dynamic extent of a directive includes both its static (lexical) extent and the extents of its orphaned directives.
### Examples
```Fortran
PROGRAM TEST  
    ...  
!$OMP PARALLEL  
    ...  
!$OMP DO  
    DO I=...  
        ...  
        CALL SUB1  
        ...  
    ENDDO  
    ...  
    CALL SUB2  
    ...  
!$OMP END PARALLEL
```

```Fortran
SUBROUTINE SUB1  
    ...  
!$OMP CRITICAL  
    ...  
!$OMP END CRITICAL  
    END  
  
    SUBROUTINE SUB2  
    ...  
!$OMP SECTIONS  
    ...  
!$OMP END SECTIONS  
    ...  
    END
```
- **Static Extent:** the `DO` directive occurs within an enclosing `PARALLEL` region.
- **Orphaned Directives:** The `CRITICAL` and `SECTIONS` directives occur outside an enclosing `PARALLEL` region.
- **Dynamic Extent:** The `CRITICAL` and `SECTIONS` directives occur within the dynamic extent of the `DO` and `PARALLEL` directives.

OpenMP specifies a number of scoping rules on how directives may associate (bind) and nest within each other.
Illegal and/or incorrect programs may result if the OpenMP binding and nesting rules are ignored.
## Directive Binding and Nesting Rules
### Directive Binding
- The `DO/for`, `SECTIONS`, `SINGLE`, `MASTER` and `BARRIER` directives bind to the dynamically enclosing `PARALLEL`, if one exists. If no parallel region is currently being executed, the directives have no effect.
- The `ORDERED` directive binds to the dynamically enclosing `DO/for`.
- The `ATOMIC` directive enforces exclusive access with respect to `ATOMIC` directives in all threads, not just the current team.
- The `CRITICAL` directive enforces exclusive access with respect to `CRITICAL` directives in all threads, not just the current team.
- A directive can never bind to any directive outside the closest enclosing `PARALLEL`.
### Directive Nesting
- A work-sharing region may not be closely nested inside a work-sharing, explicit task, critical, ordered, atomic, or master region.
- A barrier region may not be closely nested inside a work-sharing, explicit task, critical, ordered, atomic, or master region.
- A master region may not be closely nested inside a work-sharing, atomic, or explicit task region.
- An ordered region may not be closely nested inside a critical, atomic, or explicit task region.
- An ordered region must be closely nested inside a loop region (or parallel loop region) with an ordered clause.
- A critical region may not be nested (closely or otherwise) inside a critical region with the same name. Note that this restriction is not sufficient to prevent deadlock.
- `PARALLEL`, `FLUSH`, `CRITICAL`, `ATOMIC`, `TASKYIELD`, and explicit `TASK` regions may not be closely nested inside an `ATOMIC` region.

#### Closely Nested Directives
In OpenMP, closely nested directives refer to situations where multiple OpenMP directives are nested within each other, often within the same code block or function. This nesting typically involves directives like `PARALLEL` regions, loop parallelization directives (such as `PARALLEL FOR`), and work-sharing constructs (such as `SECTIONS` or `TASK`).

```C
#pragma omp parallel
{
    #pragma omp for
    for (int i = 0; i < N; i++) {
        #pragma omp task
        {
            // Task code
        }
    }
}
```
In this example, there are closely nested directives: `PARALLEL`, `FOR`, and `TASK` directives are nested within each other. Each nested directive introduces a new level of parallelism, allowing the program to exploit different levels of concurrency.

Closely nested directives can provide fine-grained control over parallel execution and enable developers to express complex parallel patterns and algorithms. However, they also require careful consideration to ensure correctness and avoid performance overhead due to excessive parallelization or synchronization. Improperly nested directives can lead to race conditions, deadlocks, or inefficient parallel execution. Therefore, understanding and managing nested directives effectively is essential for writing efficient and scalable parallel code with OpenMP.
