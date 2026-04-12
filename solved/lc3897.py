from functools import reduce
import itertools

# pairs with no 0s must be placed first.
# among pairs with 0s, we sort by number of leading 1s decreasing, then number of leading 0s increasing

MOD = int(1e9 + 7)

def helper(ones: int, zeros: int) -> str:
    return '1' * ones + '0' * zeros

class Solution:
    def maxValue(self, nums1: list[int], nums0: list[int]) -> int:
        pairs = list(zip(nums1, nums0))
        all_ones = filter(lambda p: p[1] == 0, pairs)
        have_zeros = filter(lambda p: p[1] > 0, pairs)
        lst = sorted(have_zeros, key=lambda p: (p[0], -p[1]), reverse=True)
        
        n = 0
        for ones, zeros in itertools.chain(all_ones, lst):
            n = (n * pow(2, ones, MOD)) % MOD
            n = (n +  pow(2, ones, MOD) - 1 + MOD) % MOD

            n = (n * pow(2, zeros, MOD)) % MOD


        return n
    
sol = Solution()

nums1 = [3, 1]
nums0 = [0, 3]

print(sol.maxValue(nums1, nums0))

