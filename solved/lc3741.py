from collections import defaultdict

class Solution:
    def minimumDistance(self, nums: list[int]) -> int:
        store = defaultdict[int, list[int]](list)
        for i, x in enumerate(nums):
            store[x].append(i)
        
        best = 999999999
        for arr in store.values():
            for i in range(len(arr) - 2):
                a, b, c = arr[i:i+3]
                score = abs(a - b) + abs(b - c) + abs(c - a)
                best = min(best, score)
        
        return best if best < 999999999 else -1
    
sol = Solution()
nums = [1,1,2,3,2,1,2]
print(sol.minimumDistance(nums))