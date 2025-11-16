from typing import List
import math

'''
split the array into non-decreasing subarrays.
a valid subarray is a subarray whose start and end indices fall within a maximal non-decreasing subarray
num of 'stable' subarrays in len C 2 + len

suppose the ranges are [[0, 3], [4,5], [6, 9]] and query is [1, 7]
so the valid choices to choose from is [1,3], [4,5], [6, 7]
'''

def split_into_subarrays(nums: list[int]) -> list[list[int]]:
    out = []
    s = 0
    for i in range(len(nums)):
        if i > 0 and nums[i] < nums[i - 1]:
            out.append([s, i - 1])
            s = i
    out.append([s, len(nums) - 1])
    return out

def b_search(l: int, r: int, se: list[list[int]]) -> tuple[int,int]:
    x, y = 0, 0
    s, e = 0, len(se) - 1

    while s < e:
        m = (s + e) // 2
        arr = se[m]
        if arr[0] <= l and l <= arr[1]:
            s, e = m, m
            break
        elif l < arr[0]:
            e = m - 1
        elif l > arr[1]:
            s = m + 1
    x = s

    s, e = 0, len(se) - 1
    while s < e:
        m = (s + e) // 2
        arr = se[m]
        if arr[0] <= r and r <= arr[1]:
            s, e = m, m
            break
        elif r < arr[0]:
            e = m - 1
        elif r > arr[1]:
            s = m + 1
    y = s

    return (x, y)

class Solution:
    def __init__(self):
        self.prefix_sum = None
        self.subarrays_se = None
        self.which_se = None

    
    def countStableSubarrays(self, nums: List[int], queries: List[List[int]]) -> List[int]:
        self.subarrays_se = split_into_subarrays(nums)

        self.which_se = [-1 for _ in range(len(nums))]
        p = 0
        for i in range(len(nums)):
            if i > self.subarrays_se[p][1]:
                p += 1
            self.which_se[i] = p
        #print(self.which_se)     
        
        self.prefix_sum = []
        for se in self.subarrays_se:
            l = se[1] - se[0] + 1
            res = l * (l - 1) / 2 + l
            ans = res if len(self.prefix_sum) == 0 else res + self.prefix_sum[-1]
            self.prefix_sum.append(ans)
        #print(self.prefix_sum)

        ans = []
        for q in queries:
            x, y = self.which_se[q[0]], self.which_se[q[1]]
            #print(x, y)
            
            if x == y:
                res = math.comb(q[1] - q[0] + 1, 2) + q[1] - q[0] + 1
                ans.append(int(res))
                continue

            res = 0
            
            l = math.comb(self.subarrays_se[x][1] - q[0] + 1, 2) + self.subarrays_se[x][1] - q[0] + 1
            r = math.comb(q[1] - self.subarrays_se[y][0] + 1, 2) + q[1] - self.subarrays_se[y][0] + 1
            #print(l, r)
            
            m = 0
            if x + 1 <= y - 1:
                m = self.prefix_sum[y - 1] - self.prefix_sum[x]
            
            ans.append(int(l + r + m))

        return ans


sol = Solution()
print(sol.countStableSubarrays([3,1,2],[[0,1]]))