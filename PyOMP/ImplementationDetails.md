# Numba And Implementation Details of PyOMP
Numba is a Just In Time (JIT) compiler that translates Python functions into native code optimized for a particular target. 

The Numba JIT compiles PyOMP to native code in 4 basic phases:
1. **Untyped phase:** Numba converts Python bytecode into its own intermediate representation (IR), including "with" contexts that are OpenMP-represented in the IR as "with" node types, and performs various optimizations on the IR. Later, Numba removes these "with" nodes by translating them to other node types in the IR. For our PyOmp implementation, we added a new OpenMP node type into the IR, and we convert OpenMP "with" contexts into these new OpenMP IR nodes.
2. **Type inference phase:** Numba performs type inference on the IR starting from the known argument types to the function and then performs additional optimizations. No changes were made to the Numba typed compilation phase to support OpenMP.
3. **IR conversion phase:** Numba converts its own IR into LLVM IR.
4. **Compilation phase:** Numba uses LLVM to compile the LLVM IR into machine code and dynamically loads the result into the running application.

## Converting PyOMP with clauses to Numba IR
- **When removing OpenMP "with" contexts and replacing them with OpenMP IR nodes:**
  1. Numba provides basic block information to demarcate the region that the with context covers.
  2. PyOMP places one OpenMP IR node at the beginning of this region and one at the end with a reference from the end node back to the start node to associate the two.
- **To determine what to store in the OpenMP IR node, PyOMP follows these steps:**
  1. PyOMP first parses the string passed to the OpenMP with context to create a parse tree.
  2. A postorder traversal of the parse tree is performed, accumulating the information as we go up the tree until we reach a node that has a direct OpenMP LLVM tag equivalent.
  3. At this point, convert the information from the sub-tree into tag form and then subsequently pass that tag up the parse tree.
  4. Accumulate these tags as lists of tags up the parse tree until the traversal reaches a top-level OpenMP construct or directive, which have their own tags.
- Some directives are simple and require no additional processing, while others, particularly those that support data clauses, require additional clauses to be added to the Numba OpenMP node that are not necessarily explicitly present in the programmer’s OpenMP string.

For example, all variables used within the parallel, for and parallel for directives must be present as an LLVM tag even if they are not explicitly mentioned in the programmer’s OpenMP statement. Therefore, for these directives our PyOMP prototype performs a [use-def analysis](https://en.wikipedia.org/wiki/Use-define_chain) of the variables used within the OpenMP region to determine if they are also used before or after the OpenMP region. If they are used exclusively within the OpenMP region then their default data clause is private. In all other cases, the default data clause is shared but of course these defaults can be overridden by explicit data clauses in the programmer OpenMP string.

## Converting PyOMP Numba IR To LLVM
- **When a Numba OpenMP IR node is encountered in the process of converting Numba IR to LLVM IR:**
	1. The node is converted to an LLVM OpenMP_start (or OpenMP_end) call.
	2. Inside the Numba OpenMP node is a list of the clauses that apply to this OpenMP region.
	3. A 1-to-1 conversion of that list of clauses into a list of LLVM tags is performed on the LLVM OpenMP_start call.
- Code captures the result of the LLVM OpenMP_start call, and that result is passed as a parameter to the OpenMP_end, allowing LLVM to match the beginning and end of OpenMP regions.
- In the current PyOMP prototype, inside OpenMP regions, exception handling is currently omitted to ensure the requirement of single entry and single exit to and from OpenMP regions. In the usual case, Numba unifies the handling of exceptions with return values by adding an additional hidden parameter to the functions it compiles.
- **The Numba process of converting Numba IR to LLVM IR introduces many temporary variables into the LLVM IR not present in the Numba IR:**
  - Such temporaries used solely within an OpenMP region are classified as private in the tags associated with the surrounding OpenMP region’s OpenMP_start demarcation function call.
  - PyOMP implements a callback in the Numba function to create these LLVM temporary variables and adds them as private to the previously emitted tags of the surrounding OpenMP region.
- **Certain OpenMP directives such as single and critical require the use of memory fences with acquire, release, or acquire/release memory orders:**
  - The current prototype stores this information in the Numba OpenMP IR node as created during the untyped phase.
  - During conversion of those OpenMP IR nodes to LLVM, if the node requires memory fences, then the equivalent LLVM fence instructions are inserted into the LLVM IR.
