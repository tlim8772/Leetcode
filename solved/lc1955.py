'''
let dp(curr, i) be how many subsequence with at least 1 elem == curr starting from index i are 'good'
subsequences. eg if curr = 1, then a god subseqeunce is [1,1,2], [1,2,2] ...

if nums[i] == curr
dp(curr, i) = 
1. dp(curr, i + 1): we skip this elem
2. dp(curr, i + 1): we tak this elem, but want to continue taking more elems == curr
3. dp(curr + 1, i + 1): we want to take the next curr eg. from 1 to 2

if nums[i] != curr
then ans is dp(curr, i + 1): we skip
'''

MOD = int(1e9 + 7)

class Solution:
    def __init__(self):
        self.nums: list[int] = None
        self.store: list[list[int]] = None

    def dp(self, curr: int, i: int) -> int:
        if self.store[curr][i] != None:
            return self.store[curr][i]
        
        if curr == 2:
            res = 0
            
            if self.nums[i] == 2:
                res += 1
                if i < len(self.nums) - 1:
                    res += self.dp(curr, i + 1)
            
            if i < len(self.nums) - 1:
                res += self.dp(curr, i + 1)

            self.store[curr][i] = res % MOD
            return res
        
        if self.nums[i] != curr:
            self.store[curr][i] = self.dp(curr, i + 1) if i < len(self.nums) - 1 else 0
            return self.store[curr][i]
        else:
            notake = self.dp(curr, i + 1) if i < len(self.nums) - 1 else 0
            take = self.dp(curr, i + 1) + self.dp(curr + 1, i + 1) if i < len(self.nums) - 1 else 0
            res = (notake + take) % MOD
            self.store[curr][i] = res
            return res
    
    def countSpecialSubsequences(self, nums: list[int]) -> int:
        self.nums = nums
        self.store = [[None for _ in range(len(nums))] for _ in range(3)]
        
        ans = self.dp(0, 0)
        #print(self.store)
        return ans


sol = Solution()
nums = [2,2,0,0]
print(sol.countSpecialSubsequences(nums))