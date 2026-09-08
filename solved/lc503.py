
# just append the same arr to it.
# do next greater element on it.
# then just return the 1st half.

class Solution:
    def nextGreaterElements(self, nums: list[int]) -> list[int]:
        nums = nums + nums
        out = [-1] * len(nums)
        stack: list[tuple[int,int]] = []

        for i, v in enumerate(nums):
            while len(stack) > 0 and stack[-1][1] < v:
                io, _ = stack.pop()
                out[io] = v
            stack.append((i, v))

        return out[:len(nums) // 2]
        
sol = Solution()
nums = [1,2,1]
print(sol.nextGreaterElements(nums))
