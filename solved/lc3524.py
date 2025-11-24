from typing import *

class Solution:
    def resultArray(self, nums: List[int], k: int) -> List[int]:
        out = [0 for i in range(k)]
        store = [0 for i in range(k)] # result for suffix i
        
        for i in range(len(nums) - 1, -1, -1):
            new_store = [0 for i in range(k)]
            mod = nums[i] % k
            
            new_store[mod] += 1
            for i in range(k):
                new_store[(mod * i) % k] += store[i]
            
            store = new_store
            for i in range(k):
                out[i] += store[i]

        return out
    

sol = Solution()
nums = [1,2,3,4,5]
k = 3
print(sol.resultArray(nums, k))
        