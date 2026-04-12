from sortedcontainers import SortedList
import math

# use sieve to generate all primes from 1 to 2e5
# for even indices, if not prime, get the nearest prime from left to right.
# for odd indices, get the nearest non prime from left to right.

class Sieve:
    def __init__(self, len):
        self.len = len
        self.is_prime: list[bool] = [True for _ in range(len + 1)]
        self.primes_only: SortedList[int] = None
        self.process()

    def process(self):
        lim = int(math.floor(math.sqrt(self.len)))
        for i in range(2, lim + 1):
            if not self.is_prime[i]:
                continue
            for j in range(i * i, self.len + 1, i):
                self.is_prime[j] = False

        primes = enumerate(self.is_prime)
        primes = filter(lambda p: p[0] >= 2 and p[1], primes)
        primes = map(lambda p: p[0], primes)
        self.primes_only = SortedList(primes)

    def closest_prime(self, n: int) -> int:
        if n >= 2 and self.is_prime[n]:
            return n
        
        idx = self.primes_only.bisect_left(n)
        return self.primes_only[idx]
    
    def closest_nonprime(self, n: int) -> int:
        if n < 2 or not self.is_prime[n]:
            return n
        
        cnt = 1
        while True:
            if not self.is_prime[n + cnt]:
                return n + cnt
            cnt += 1
    
sieve = Sieve(200000)

class Solution:
    def minOperations(self, nums: list[int]) -> int:
        sum = 0
        for i, x in enumerate(nums):
            if i % 2 == 0:
                sum += sieve.closest_prime(x) - x
            else:
                sum += sieve.closest_nonprime(x) - x
        return sum

        

sol = Solution()
nums = [7,8,6,1]
print(sol.minOperations(nums))



