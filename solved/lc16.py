from sortedcontainers import *

class Solution:
    def threeSumClosest(self, nums: list[int], target: int) -> int:
        sorted_list = SortedList()
        best = -999999999
        
        for i in range(len(nums)):
            sorted_list.clear()
            
            for j in range(len(nums) - 1, i, -1):
                a, b = nums[i], nums[j]
                diff = target - a - b
                idx = sorted_list.bisect_right(diff)
                
                if idx < len(sorted_list):
                    c1 = sorted_list[idx]
                    if abs(a + b + c1 - target) < abs(best - target):
                        best = a + b + c1

                if idx > 0 and idx - 1 < len(sorted_list):
                    c2 = sorted_list[idx - 1]
                    if abs(a + b + c2 - target) < abs(best - target):
                        best = a + b + c2

                sorted_list.add(b)


        return best
    

sol = Solution()
nums = [0, 1, 1]
target = 2
print(sol.threeSumClosest(nums, target))