from functools import cache
MOD = int(1e9 + 7)


class Solution:
    def __init__(self):
        self.min_sum = None
        self.max_sum = None

    @cache
    def dp(self, i: int, start: bool, sum: int) -> int:
        if i == 0:
            return self.min_sum <= sum and sum <= self.max_sum
        
        ans = 0
        for d in range(start, 10):
            if sum + d > self.max_sum:
                continue
            ans += self.dp(i - 1, 0, sum + d)
            ans %= MOD
        return ans
    
    def helper(self, i: int, sum: int, num: str) -> int:
        if num == '0':
            return 0
        
        if i == len(num):
            return self.min_sum <= sum and sum <= self.max_sum
        
        ans = 0
        if i == 0:
            for num_digs in range(1, len(num)):
                ans += self.dp(num_digs, 1, 0)
                ans %= MOD

        d = int(num[i])
        not_same = 0
        for dg in range(0 + (i == 0), d):
            not_same += self.dp(len(num) - i - 1, 0, sum + dg)
            not_same %= MOD

        same = self.helper(i + 1, sum + d, num)

        return (ans + not_same + same) % MOD

    def count(self, num1: str, num2: str, min_sum: int, max_sum: int) -> int:
        self.min_sum = min_sum
        self.max_sum = max_sum
        return (self.helper(0, 0, num2) - self.helper(0, 0, str(int(num1) - 1))) % MOD
    
sol = Solution()
print(sol.count('1', '5', 1, 5))