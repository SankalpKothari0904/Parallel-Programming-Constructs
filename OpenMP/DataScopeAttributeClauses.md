# Data Scope Attribute Clauses
Also called Data-Sharing Attribute Clauses.
Since OpenMP is based on the shared memory programming model, most variables are shared by default.

**For C/C++:**
- Global variables include file scope variables, static.
- Private variables include loop index variables, stack variables in subroutines called from parallel regions.

The OpenMP Data Scope Attribute Clauses are used to explicitly define how variables should be scoped. They include: `PRIVATE`, `FIRSTPRIVATE`, `LASTPRIVATE`, `SHARED`, `DEFAULT`, `REDUCTION`, `COPYIN`.They are used in conjunction with several directives (`PARALLEL`, `DO/for`, and `SECTIONS`) to control the scoping of enclosed variables.

These constructs provide the ability to control the data environment during execution of parallel constructs.
- They define how and which data variables in the serial section of the program are transferred to the parallel sections of the program (and back).
- They define which variables will be visible to all threads in the parallel sections and which variables will be privately allocated to all threads.

**Note:** Data Scope Attribute Clauses are effective only within their lexical/static extent.
## PRIVATE Clause
The `PRIVATE` clause declares variables in its list to be private to each thread.

`PRIVATE` variables behave as follows:
- A new object of the same type is declared once for each thread in the team.
- All references to the original object are replaced with references to the new object.
- Variables declared PRIVATE should be assumed to be uninitialized for each thread.
### Format
```c++
#pragma omp <compatible_directive> private (list_of_vars)
```
## SHARED Clause
The `SHARED` clause declares variables in its list to be shared among all threads in the team.

A shared variable exists in only one memory location and all threads can read or write to that address.

It is the programmer’s responsibility to ensure that multiple threads properly access `SHARED` variables and avoid data corruption (such as via `CRITICAL` sections).
### Format
```c++
#pragma omp <compatible_directive> shared (list_of_vars)
```
## DEFAULT Clause
The `DEFAULT` clause allows the user to specify a default scope for all variables in the lexical extent of any parallel region.

Specific variables can be exempted from the default using the `PRIVATE`, `SHARED`, `FIRSTPRIVATE`, `LASTPRIVATE`, and `REDUCTION` clauses.
**Note:** Using `NONE` as a default requires that the programmer explicitly scope all variables, and only one `DEFAULT` clause can be specified on a `PARALLEL` directive.
### Format
```c++
#pragma omp <compatible_directive> default (shared | none)
```
## FIRSTPRIVATE Clause
The `FIRSTPRIVATE` clause combines the behavior of the `PRIVATE` clause with automatic initialization of the variables in its list.
Listed variables are initialized according to the value of their original objects prior to entry into the parallel or work-sharing construct.
### Format
```c++
#pragma omp <compatible_directive> firstprivate (list_of_vars)
```
## LASTPRIVATE Clause
The `LASTPRIVATE` clause combines the behavior of the `PRIVATE` clause with a copy from the last loop iteration or section to the original variable object.

The value copied back into the original variable object is obtained from the last (sequentially) iteration or section of the enclosing construct.

For example, the team member which executes the final iteration for a `DO` section, or the team member which does the last `SECTION` of a `SECTIONS` context performs the copy with its own values.
### Format
```c++
#pragma omp <compatible_directive> lastprivate (list_of_vars)
```
