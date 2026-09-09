from functools import cache
# basically it is just longest common subsequence

class Solution:
    def maxUncrossedLines(self, nums1: list[int], nums2: list[int]) -> int:
        @cache
        def dp(i: int, j: int):
            if i >= len(nums1) or j >= len(nums2):
                return 0

            if nums1[i] == nums2[j]:
                return 1 + dp(i + 1, j + 1)

            return max(dp(i, j + 1), dp(i + 1, j))

        return dp(0, 0)

sol = Solution()
nums1 = [1,2,3]
nums2 = [0,0,1,2,3]
ans = sol.maxUncrossedLines(nums1, nums2)
print(ans)