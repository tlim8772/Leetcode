
# the sum is just a sliding window.
# sum goes from [0, len /2), [1, len / 2 + 1), [2, len / 2 + 2) ... [n - 1, len / 2 + n - 1)

class Solution:
    def countGoodRotations(self, nums: list[int]) -> int:
        total = sum(nums)
        window = 0
        cnt = 0
        for i in range(len(nums)):
            if i == 0:
                window = sum(nums[0:len(nums) // 2])
            else:
                window -= nums[i - 1]
                window += nums[(i + len(nums) // 2 - 1) % len(nums)]
            cnt += window > total - window
            #print(window)
        return cnt

sol = Solution()
nums = [1,2,3,4,5,6]

ans = sol.countGoodRotations(nums)
#print(ans)