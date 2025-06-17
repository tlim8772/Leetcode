from typing import *
from functools import *

'''
classic digit dp
'''

# pos is 1 index, anyway it means how many digits left we are considering
@cache
def dp(pos: int, isPrev1: bool, is1st: bool):
    if pos == 0:
        return 1
    
    # since is 1st digit, only option is 1, no trailing 0
    if is1st:
        return dp(pos - 1, True, False)
    
    # only option is 0
    if isPrev1:
        return dp(pos - 1, False, False)
    else:
        put1 = dp(pos - 1, True, False)
        put0 = dp(pos - 1, False, False)
        return put1 + put0

    

#print(dp(4, False, True))
#print(bin(999))

class Solution:

    # pos start from 1 don't need to consider 0
    # if 1st digit is 0, it is already counted when we count nums with 
    # strictly lesser num of digits
    def helper(self, s: str, pos: int) -> int:
        if pos == len(s):
            return 1
        
        if s[pos] == '1':
            if s[pos - 1] == '1':
                # then we must put 0, and we cannot continue
                return dp(len(s) - pos - 1, False, False)
            else:
                put0 = dp(len(s) - pos - 1, False, False)
                put1 = self.helper(s, pos + 1)
                return put0 + put1
        
        else:
            return self.helper(s, pos + 1)

    
    
    def findIntegers(self, n: int) -> int:
        s = bin(n)[2:]
        
        sum = 1 # need to consider 0
        
        for i in range(1, len(s), 1):
            sum += dp(i, False, True)

        # print(sum)
        sum += self.helper(s, 1)

        return sum
    

sol = Solution()
print(sol.findIntegers(2))