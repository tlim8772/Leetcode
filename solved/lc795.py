from typing import *
import math

'''
break problem into find num of subarrays with max elem <= limit
then find ans for left - 1 and right and then substract
use sparse table to find new current max
'''
class SparseTable:
    def __init__(self, lst: List[int]):
        maxPow = int(math.log2(len(lst)))
        self.table = [[0 for i in range(maxPow + 1)] for i in range(len(lst))]

        for i in range(len(lst)):
            self.table[i][0] = lst[i]

        for p in range(1, maxPow + 1):
            for i in range(len(lst)):
                left = self.table[i][p - 1]
                right = 0 if i + (1 << (p - 1)) >= len(lst) else self.table[i + (1 << (p - 1))][p - 1]
                self.table[i][p] = max(left, right)

        '''
        for arr in self.table:
            print(arr)
        '''

    def queryMax(self, l: int, r: int):
        d = int(math.log2(r - l + 1))
        return max(self.table[l][d], self.table[r - (1 << d) + 1][d])
    

class Solution:
    def numSubarrayLessMax(self, nums: List[int], sp: SparseTable, rightLim: int) -> int:
        cnt: int = 0
        
        p: int = -1
        for i in range(len(nums)):
            # use sparse table here to find new currMax, as max has no inverse
            currMax = sp.queryMax(i, p) if p >= i else nums[i]
            p = i if p < i else p

            if currMax > rightLim:
                p = -1
                continue

            while p + 1 < len(nums):
                newMax = max(nums[p + 1], currMax)
                if newMax > rightLim:
                    break
                else:
                    currMax = newMax
                    p += 1

            cnt += p - i + 1

        return cnt


            
    
    
    def numSubarrayBoundedMax(self, nums: List[int], left: int, right: int) -> int:
        sp: SparseTable = SparseTable(nums)
        rightMaxLess = self.numSubarrayLessMax(nums, sp, right)
        leftMaxLess = self.numSubarrayLessMax(nums, sp, left - 1)

        return rightMaxLess - leftMaxLess


lst = [2,1,4,3]
left, right = 2, 3

sol = Solution()

print(sol.numSubarrayBoundedMax(lst, left, right))
