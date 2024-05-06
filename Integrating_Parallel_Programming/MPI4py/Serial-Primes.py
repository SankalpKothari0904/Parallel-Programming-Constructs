import math
import time

LIMIT = 2500000
PRINT = 100000

def is_prime(n):
    if n > 10:
        squareroot = int(math.sqrt(n))
        for i in range(3, squareroot + 1, 2):
            if n % i == 0:
                return False
        return True
    else:
        return False

def main():
    pc = 4  # Assuming primes less than 10 are counted here
    print(f"Starting. Numbers to be scanned = {LIMIT}")
    
    start_time = time.time()
    
    for n in range(11, LIMIT + 1, 2):
        if is_prime(n):
            pc += 1
            foundone = n
            # Optional: print each prime as it is found
            # print(foundone)
        
        if (n - 1) % PRINT == 0:
            print(f"Numbers scanned = {n - 1}   Primes found = {pc}")
    
    end_time = time.time()
    
    print(f"Done. Largest prime is {foundone}. Total primes: {pc}")
    # Calculate and print the elapsed time
    print(f"Wall clock time elapsed: {end_time - start_time:.6f} seconds")

if __name__ == "__main__":
    main()
