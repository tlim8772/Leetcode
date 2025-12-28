'''
if we see the same mod again, the pattern repeats, so if we have not seen a 0, it is impossible.
'''

class Solution:
    def minAllOneMultiple(self, k: int) -> int:
        seen = set()
        
        n = 0
        curr = 0

        while True:
            curr += 1
            n = ((n * 10) % k + 1) % k
            if n == 0:
                return curr
            elif n in seen:
                break
            else:
                seen.add(n)

        return -1
    
print(Solution().minAllOneMultiple(7))