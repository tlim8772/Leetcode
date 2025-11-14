import math
import functools

'''
an ideal array is non-decreasing.
suppose we only find strictly increasing ideal arrays, the length is very short, because we always double at minimum.
eg. [1, 2, 4, 8, 16, ... 2^13].
the maximum length is at most 13, as 2^13 = 8192, 2^14 > 1e4

for non decreasing we partition the array into subarrays that are equal
eg [1, 1, 1, 2, 2, 2, 8, 8, 8 ...].
it is equal to distribute n items into k distinct boxes with all boxes having at least 1 item.
ans is math.comb(n - k + (k - 1), k - 1)

let dp(idx, start, max_val, max_len) = # ways for strictly increasing seqeuence, with idx i = start
and elems have to be <= max_val, max_len is the length of the sequence we are aiming for.

dp(idx, start) = dp(idx + 1, start * start) + dp(idx + 1, start * 3) + dp(idx + 1, start * 4)

so total time complexity is 13 * 10^4 * log(10^4)
'''

MOD = int(1e9 + 7)

@functools.cache
def dp(i: int, start: int, max_val: int, max_len: int) -> int:
    if i == max_len - 1:
        return 1
    
    sum = 0
    for j in range(2 * start, max_val + 1, start):
        sum += dp(i + 1, j, max_val, max_len)
        sum = sum % MOD
    return sum

class Solution:
    def idealArrays(self, n: int, maxValue: int) -> int:
        max_len = min(n, 1 + int(math.log2(maxValue)))
        
        ans = 0
        for splits in range(1, max_len + 1):
            num_splits = math.comb(n - 1, splits - 1) % MOD
            ways = 0
            
            for start in range(1, maxValue + 1):
                temp = dp(0, start, maxValue, splits)
                if temp == 0:
                    break
                
                ways = (ways + temp) % MOD
            
            ans = (ans + (ways * num_splits) % MOD) % MOD

        return ans

sol = Solution()
print(sol.idealArrays(5, 3))