from functools import cache
'''
side = 0 means odd pos, side = 1, mean even pos.
odd is neg, even is pos.
side initially is false, as we start from left with position 1.

simple digit dp
'''

@cache
def dp(num: int, diff: int, side: bool, start: bool) -> int:
    if num == 0:
        return 1 if diff == 0 else 0
    
    sum = 0
    for d in range(start, 10):
        new_diff = diff + d if side else diff - d
        sum += dp(num - 1, new_diff, not side, False)
    
    return sum

def helper(str_num: str, i: int, diff: int) -> int:
    if i == len(str_num):
        return 1 if diff == 0 else 0
    
    sum = 0
    if i == 0:
        for j in range(2, len(str_num)):
            sum += dp(j, 0, False, True)
    
    d = ord(str_num[i]) - ord('0')

    sum += helper(str_num, i + 1, diff + (d if i % 2 == 1 else -d))

    for next in range(i == 0, d):
        sum += dp(len(str_num) - i - 1, diff + (next if i % 2 == 1 else -next), (i + 1) % 2 == 1, False)

    return sum

class Solution:
    def countBalanced(self, low: int, high: int) -> int:
        return helper(str(high), 0, 0) - (0 if low == 1 else helper(str(low - 1), 0, 0))


print(Solution().countBalanced(50948, 62036))
