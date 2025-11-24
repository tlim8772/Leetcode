'''
if arr[i:j] has xor 0, (inclusive at both ends) then xor(arr[:j]) == xor(arr[:i-1])
if arr[i:j] has #even == #odd, then even_odd_diff(arr[:j]) == even_odd_diff(arr[:i-1])
is just hashmap with key (xor, even - odd).
take the difference of the smallest and largest value
i.e if bins[key] = (1, 10) means arr[2:10] is a valid subarray
'''


class Solution:
    def maxBalancedSubarray(self, nums: list[int]) -> int:
        bins: dict[tuple[int,int,int],tuple[int,int]] = {}
        
        even, odd = 0, 0
        xor = 0
        for i, x in enumerate(nums):
            if x % 2 == 0:
                even += 1
            else:
                odd += 1
            xor ^= x
            k = (xor, even - odd)
            if k not in bins:
                bins[k] = (i, i)
            else:
                bins[k] = (bins[k][0], i)

        best = 0
        for k, v in bins.items():
            if k[0] == 0 and k[1] == 0:
                best = max(best, v[1] + 1)
            else:
                best = max(best, v[1] - v[0])
        return best

sol = Solution()
nums = [3,1,3,2,0]
print(sol.maxBalancedSubarray(nums))