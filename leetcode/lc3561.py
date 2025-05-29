'''
consider a stack, push characters in it, if encounter consecutive characters pop them out
'''

from typing import *

class Solution:

    def consec(self, s1, s2: str) -> bool:
        x1 = ord(s1)
        x2 = ord(s2)
        if (x1 > x2):
            x1, x2 = x2, x1
        
        if x1 == ord('a') and x2 == ord('z'):
            return True
        else:
            return x2 - x1 == 1
    
    def resultingString(self, s: str) -> str:
        stack = []
        for i in range(len(s)):
            if len(stack) > 0 and self.consec(stack[-1], s[i]):
                stack.pop()
            else:
                stack.append(s[i])

        return ''.join(stack)
    
sol = Solution()
s = 'adce'
print(sol.resultingString(s))