from functools import cache
from typing import *
import math

'''
merging interval dp
consider the road divided into intervals (pos[0], pos[1]), (pos[1], pos[2]) ... (pos[n - 2], pos[n - 1])
we can merge some intervals into a larger interval. The cost the is the cost of the 1st interval used
then add the cost of the remaining interval to the 1st interval after the merge
eg.
merge the 1st 2 intervals: (0, 1) (1, 2) (2, 3) -> (0, 2) (2, 3)
add cost of (1, 2) to cost of (2, 3)
'''

class Solution:
    def minTravelTime(self, l: int, n: int, k: int, position: List[int], time: List[int]) -> int:
        '''
        start means (start, start + 1) is the 1st interval
        offset is the additional cost due to previous mergers
        kLeft is how many merges left

        if we merge i intervals, new start interval is (s + i + 1, s + i + 2)
        add cost of (s + 1, s + 2) (s + 2, s + 3) ... (s + i, s + i + 1)
        
        '''
        @cache
        def dp(offset: int, start: int, kLeft: int) -> int:
            if start == n - 1:
                return 999999999 if kLeft != 0 else 0
            
            sum = 0
            best = 999999999
            for i in range(0, kLeft + 1):
                if start + i + 1 > n - 1:
                    break

                res = (offset + time[start]) * (position[start + i + 1] - position[start]) + dp(sum, start + i + 1, kLeft - i)
                best = min(best, res)

                sum += time[start + i + 1]

            return best
        
        return dp(0, 0, k)


        
        

sol = Solution()
l = 3
n = 3
k = 1
position = [0,1,3]
time = [1,3,1]

print(sol.minTravelTime(l, n, k, position, time))




            
        