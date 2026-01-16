from collections import defaultdict

'''
O(n^3) solution. Iterate thorught i, j, k then for the last elem use hash map to find
'''

class Solution:
    def fourSum(self, nums: list[int], target: int) -> list[list[int]]:
        store = set[int]()
        seen = set[tuple[int,int,int,int]]()
        
        for i in range(len(nums)):
            for j in range(i + 1, len(nums)):
                store.clear()
                
                for k in range(len(nums) - 1, j, -1):
                    a, b, c = nums[i], nums[j], nums[k]
                    diff = target - a - b - c
                    
                    if diff in store:
                        seen.add(tuple(sorted([a, b, c, diff])))

                    store.add(nums[k])

        return list(map(lambda x: list(x), list(seen)))
    
sol = Solution()
nums = [1,0,-1,0,-2,2]
target = 0
print(sol.fourSum(nums, target))