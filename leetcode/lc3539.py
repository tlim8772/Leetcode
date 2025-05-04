from functools import cache
from typing import *
import math

'''
difficult dp + combinatorics
let state = dp(cnt, start, numBits, bm)
cnt: how many numbers chosen
start: smallest seq number we are starting from, so if start = 5, we are considering taking (multiple copies) of 5
numBits: num of bits that confirm wont change
bm: bm is from 2^start onwards

we can choose [0, m - cnt] copies of start, use a for loop for this
to consider num of permuatations, use stars and bars technique
if we choose i copies of start, we add i to bm, then rightshift bm by 1 for the next call to dp
add 1 to numBits if least significant bit of bm is 1

'''

MOD = 1000000007

def countSetBits(x: int) -> int:
    cnt = 0
    while x > 0:
        cnt += x & 1
        x = x >> 1
    return cnt

class Solution:
    def magicalSum(self, m: int, k: int, nums: List[int]) -> int:
        
        # cnt: how many elems chosen, start: next elem we are considering (in increasing order)
        @cache
        def dp(cnt: int, start: int, numBits: int, bm: int) -> int:
            if start == len(nums):
                if cnt != m:
                    return 0
                else:
                    bits = numBits + countSetBits(bm)
                    return 1 if bits == k else 0
                
            store = 0
            for i in range(0, m - cnt + 1):
                left = m - cnt - i
                
                t1 = pow(nums[start], i, MOD)
                ways = math.comb(i + left + 1 - 1, i) % MOD  # stars and bars here
                newBm = bm + i
                
                res = t1 * ways * dp(cnt + i, start + 1, numBits + (newBm & 1), newBm >> 1)
                res = res % MOD
                store += res
                store = store % MOD

            return store
        
        return dp(0, 0, 0, 0)
    
sol = Solution()
print(sol.magicalSum(2, 2, [5,4,3,2,1]))

        