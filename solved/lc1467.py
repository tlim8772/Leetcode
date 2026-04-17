from functools import cache, reduce
import math

# the total # of permutations is factorial(sum(balls)) / (factorial(balls[0]) * factorial(balls[1]) ... * factorial(balls[n - 1])).
# we want to find the # of valid permutations, 
# i.e permuations where the # of distinct colors in the 1st half = # of distinct colors in the 2nd half.

# use dp(curr distinct in 0, curr distinct in 0, taken balls in 0, idx).
# at idx i, we have slots0 left for 1st half and slots1 left for 2nd half.
# we can take x balls to give 1st half and balls[idx] - x to give to 2nd half,
# subject to validity, i.e each slot can take exactly sum(balls) / 2
# num of ways is comb(slots0, x) * comb(slots1) * dp(distinc0, distinct1, taken + x, i + 1)
# we add up for each value of x.


class Solution:
    def __init__(self):
        self.store: dict[tuple[int,int,int,int], int] = {}

        self.balls: list[int] = None
        self.prefix_sum: list[int] = None
        self.lim: int = 0
        

    def dp(self, d0: int, d1: int, taken0: int, i) -> int:
        if i == len(self.balls):
            return 1 if d0 == d1 else 0
        
        key = (d0, d1, taken0, i)
        if key in self.store:
            return self.store[key]
        
        left0 = self.lim - taken0
        left1 = self.lim if i == 0 else self.lim - (self.prefix_sum[i - 1] - taken0)
        
        sum = 0
        for b in range(0, min(left0, self.balls[i]) + 1):
            give0 = b
            give1 = self.balls[i] - b

            if left1 < give1:
                continue

            res = math.comb(left0, give0) * math.comb(left1, give1) * \
                self.dp(d0 + (give0 > 0), d1 + (give1 > 0), taken0 + b, i + 1)
            
            sum += res

        self.store[key] = sum
        return sum


        

    def getProbability(self, balls: list[int]) -> float:
        self.lim = sum(balls) // 2
        
        self.prefix_sum = [0 for _ in range(len(balls))]
        for i, b in enumerate(balls):
            self.prefix_sum[i] = b if i == 0 else b + self.prefix_sum[i - 1]

        self.balls = balls

        total_perms = math.factorial(sum(balls)) / reduce(lambda a, x: a * math.factorial(x), balls, 1)

        total_valid_perms = self.dp(0, 0, 0, 0)

        return total_valid_perms / total_perms
    

sol = Solution()

balls = [6,6,6,6,6,6,6,6]
print(sol.getProbability(balls))