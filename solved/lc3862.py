from functools import reduce

'''
to prevent multiplication overflow, just put -1, once mults is over 1e15, because
max sum is 1e14
'''

class Solution:
    def smallestBalancedIndex(self, nums: list[int]) -> int:
        left_sum = 0
        right_mults = []

        store = 1
        for i in range(len(nums) - 1, -1, -1):
            if store > 1e15:
                right_mults.append(-1)
            else:
                store *= nums[i]
                right_mults.append(store)
        right_mults.reverse()
        
        for i in range(len(nums)):
            if left_sum == (1 if i == len(nums) - 1 else right_mults[i + 1]):
                return i
            left_sum += nums[i]
        return -1
    

sol = Solution()
nums = [999,818,984,995,841,822,984,978,960,997,896,926,759,961,1000,562,1,1,1,87,4,1,40]
print(sol.smallestBalancedIndex(nums))
