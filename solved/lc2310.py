from functools import cache

'''
simple take, no take dp
'''

@cache
def dp(num: int, curr: int, k: int) -> int:
    
    if num == 0:
        return 0
    elif num < curr:
        return 999999
    
    if num >= curr and num % 10 == k:
        return 1
    
    take = 1 + dp(num - curr, curr, k)
    notake = dp(num, curr + 10, k)
    ans = min(take, notake)
    return ans
    

class Solution:
    def minimumNumbers(self, num: int, k: int) -> int:
        dp.cache_clear()
        ans = dp(num, k if k > 0 else 10, k)
        return ans if ans < 999999 else -1
    
sol = Solution()
print(sol.minimumNumbers(58, 9))