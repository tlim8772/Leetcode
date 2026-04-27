# everytime arr[i] < arr[i - 1], we increase arr[i:] by arr[i - 1] - arr[i].
# this is the most optimal way to minimise the sum of 'x' used in each operation.
# instead of increasing one by one.

class Solution:
    def minOperations(self, nums: list[int]) -> int:
        offset = 0
        total = 0
        for i in range(1, len(nums)):
            # remember nums[i - 1] has also offset added to it, and so does nums[i]
            diff = nums[i - 1] - nums[i]
            if diff <= 0:
                continue
            offset += diff
            total += diff
        return total
    
sol = Solution()
nums = [5,1,2,3]
print(sol.minOperations(nums))