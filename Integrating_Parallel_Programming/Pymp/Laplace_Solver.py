import pymp  
from time import perf_counter
 
nx = 1201
ny = 1201
 
# Solution and previous solution array
sol = pymp.shared.array((nx,ny))  
soln = pymp.shared.array((nx,ny))  
 
for j in range(0,ny-1):
    sol[0,j] = 10.0
    sol[nx-1,j] = 1.0
# end for
 
for i in range(0,nx-1):
    sol[i,0] = 0.0
    sol[i,ny-1] = 0.0
# end for
 
# Iterate
start_time = perf_counter()
with pymp.Parallel(6) as p:  
    for kloop in range(1,100):
        soln = sol.copy()
 
        for i in p.range(1,nx-1):
            for j in p.range (1,ny-1):
                sol[i,j] = 0.25 * (soln[i,j-1] + soln[i,j+1] + soln[i-1,j] + soln[i+1,j])
            # end j for loop
        # end i for loop
    # end kloop for loop
# end with
end_time = perf_counter()
 
print(' ')
print('Elapsed wall clock time = %g seconds.' % (end_time-start_time) )
print(' ')