
# since array is strictly increasing and jumping from idx i to idx i + 1
# is abs(nums[i + 1] - nums[i]) or 1
# we take the cost of 1 jumps as much as possible.
# also cost of jumping from i to k then to j <= cost of jumping straight from i to j.
# quite easy to prove :)
# result is just the sum of costs of consecutive jumps to the direct left/right elem.

# make seperate prefix sums for jumping right (when l < r) and left (when l > r) respectively.

class Solution:
    def minCost(self, nums: list[int], queries: list[list[int]]) -> list[int]:
        # idx i is cost to jump from i to i + 1
        right_jumps = []
        # idx i is cost to jump from i + 1 to i
        left_jumps = []

        for i in range(0, len(nums)):
            lcost = abs(nums[i - 1] - nums[i]) if i > 0 else int(1e10)
            rcost = abs(nums[i] - nums[i + 1]) if i < len(nums) - 1 else int(1e10)
            
            if i < len(nums) - 1:
                right_jumps.append(1 if rcost < lcost else rcost)

            if i > 0:
                left_jumps.append(1 if lcost <= rcost else lcost)

        
        for i in range(1, len(right_jumps)):
            right_jumps[i] += right_jumps[i - 1]
            left_jumps[i] += left_jumps[i - 1]

        out = []
        for q in queries:
            l, r = q
            if l == r:
                out.append(0)
                continue
            elif l < r:
                out.append(right_jumps[r - 1] - (0 if l == 0 else right_jumps[l - 1]))
            else:
                out.append(left_jumps[l - 1] - (0 if r == 0 else left_jumps[r - 1]))

        return out
    
sol = Solution()
nums = [0,2,3,9]
queries = [[3,0],[1,2],[2,0]]
print(sol.minCost(nums, queries))
        


        

