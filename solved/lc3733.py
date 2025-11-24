from typing import *
from math import lcm

'''
binary search on time.
now given a time, need to check whether can complete the required num of deliveries per drone
so we need to find number of delivery windows for drone 1 and drone 2
# delivery windows is t - t // r[i]
# delivery windows in both drone 1 and drone 2 = number of ints not divisble by r[0] and r[1]
# need to use PIE
'''

def helper(d: list[int], r: list[int], t: int) -> bool:
    set1, set2 = t - t // r[0], t - t // r[1]
    
    div1, div2 = t // r[0], t // r[1]
    div12 = t // lcm(*r)
    intersect = t - (div1 + div2 - div12)

    #print(set1 + set2 - intersect)

    if set1 < d[0] or set2 < d[1]:
        return False
    return set1 + set2 - intersect >= sum(d)
    

class Solution:
    def minimumTime(self, d: List[int], r: List[int]) -> int:
        s, e = 1, int(2e9)
        while s < e:
            m = (s + e) >> 1
            res = helper(d, r, m)
            if res:
                e = m
            else:
                s = m + 1
        return s
    
sol = Solution()
d = [3, 1]
r = [2, 3]
print(helper(d, r, 4))
print(sol.minimumTime(d, r))