import time

def is_prime(num):
    if num <= 1:
        return False
    if num == 2:
        return True
    if num % 2 == 0:
        return False
    for i in range(3, int(num**0.5) + 1, 2):
        if num % i == 0:
            return False
    return True

def find_primes_up_to_N(N):
    primes = []
    for num in range(2, N+1):
        if is_prime(num):
            primes.append(num)
    return primes

def main():
    N = 1000000
    
    start_time = time.time()
    primes = find_primes_up_to_N(N)
    end_time = time.time()
    
    # print("Prime numbers up to", N, "are:")
    # print(primes)
    print("Total number of prime numbers up to", N, "is:", len(primes))
    print("Time taken:", round(end_time - start_time, 4), "seconds")

if __name__ == "__main__":
    main()
