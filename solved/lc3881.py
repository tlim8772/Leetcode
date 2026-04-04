import math

# split into Left and Right groups.
# we can choose a people in the left group and b people in the Right group, 
# s.t a + b = k
# so we sum from 0 to k, i.e
# LC0 * RCk + LC1 * RCk-1 ... LCk * RC0
# but a simpler way is simple (L + R)Ck
# the direction of the person at pos does not matter.

class Solution:
    def countVisiblePeople(self, n: int, pos: int, k: int) -> int:
        return 2 * math.comb(n - 1, k) % int(1e9 + 7)
    
sol = Solution()
print(sol.countVisiblePeople(1, 0, 0))
