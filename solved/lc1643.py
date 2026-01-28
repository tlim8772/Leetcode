import math

# just use nCr, and 1st put H, check how many combinations, if less than k then put V
# if not keep H.

class Solution:
    def kthSmallestPath(self, destination: list[int], k: int) -> str:
        v, h = destination
        path = []
        for i in range(h + v):
            if h == 0 or v == 0:
                break
            
            num = math.comb(h - 1 + v, v)
            if num < k:
                path.append('V')
                v -= 1
                k -= num
            else:
                path.append('H')
                h -= 1
        
        for _ in range(h):
            path.append('H')
        
        for _ in range(v):
            path.append('V')

        return ''.join(path)
    
sol = Solution()
destination = [2, 3]
k = 2
print(sol.kthSmallestPath(destination, k))
