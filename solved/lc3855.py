'''
suppose we have x digits
for digit d at position p, it contributes  d * (10 ** p) for x ** (k - 1) times.
but k <= 10^9, so we have to use geometric series to sum d * (10 ** p)
'''
class Solution:
    def sumOfNumbers(self, l: int, r: int, k: int) -> int:
        size = r - l + 1
        MOD = int(1e9 + 7)
        sum = 0
        for d in range(l, r + 1):
            sum += pow(size, k - 1, MOD) * d * (pow(10, k, MOD) - 1) * pow(9, -1, MOD)
        return sum % MOD
    
print(Solution().sumOfNumbers(1, 2, 2))