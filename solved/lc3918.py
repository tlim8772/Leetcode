import math
class Solution:
    def sumOfPrimesInRange(self, n: int) -> int:
        r = int(str(n)[::-1])
        start, end = min(n, r), max(n, r)

        def is_prime(n: int) -> bool:
            for i in range(2, int(n**0.5) + 1):
                if n % i == 0:
                    return False
            return True
        
        it = range(max(2, start), end + 1)
        it = filter(lambda x: is_prime(x), it)
        ans = sum(it)
        return ans
    
sol = Solution()
print(sol.sumOfPrimesInRange(10))
