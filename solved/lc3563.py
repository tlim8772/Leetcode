from typing import *
from functools import cache

"""
simple dp
first dp on substring(i, j) to check whether it can be removed
next dp(i): lexicographically smallest string starting from i
dp(i) = min(s[i] + dp(i + 1), dp(j + 1) if substring(i, j) can be removed for all j > i)
"""

def consec(s1, s2: str) -> bool:
    x1 = ord(s1)
    x2 = ord(s2)
    if (x1 > x2):
        x1, x2 = x2, x1
    
    if x1 == ord('a') and x2 == ord('z'):
        return True
    else:
        return x2 - x1 == 1

class Solution:
    def lexicographicallySmallestString(self, s: str) -> str:

        @cache
        def helper(i, j: int) -> bool:
            if (j < i):
                return True
            elif j - i + 1 % 2 == 1:
                return False
            else:
                if consec(s[i], s[j]):
                    if helper(i + 1, j - 1):
                        return True

                for k in range(i + 1, j, 2):
                    if helper(i, k) and helper(k + 1, j):
                        return True
                
                return False
            
        @cache
        def dp(i: int) -> str:
            if i >= len(s):
                return ''
            
            take = s[i] + dp(i + 1)
            
            for j in range(i + 1, len(s), 2):
                if j < len(s) and helper(i, j):
                    res = dp(j + 1)
                    if res < take:
                        take = res  
            
            return take

            
        return dp(0)
    
sol = Solution()
print(sol.lexicographicallySmallestString('ab'))
