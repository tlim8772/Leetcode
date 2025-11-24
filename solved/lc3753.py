from functools import cache
'''
dp(prev, rise_fall, start, digits)
prev: prev digit.
rise_fall: -1 means decrease, 0 means flat, 1 means increase.
start: whether this is the very 1st digit or not.
digits: digits left to slot.

slightly different from normal dp, because we want sum of waveliness of all digits in a range.
so when we hit a peak, we add up all the times this peak can appear 
i.e multiply by pow(10, digits remaining).
'''

def clip(val: int, mi: int = -1, ma: int = 1) -> int:
    if val < mi:
        return mi
    elif val > ma:
        return ma
    else:
        return val
    
def is_peak_or_valley(x, y, z) -> bool:
    return (y > x and y > z) or (y < x and y < z)

def count_peak_valley(lst: list[int]) -> bool:
    sum = 0
    for i in range(1, len(lst) - 1):
        if is_peak_or_valley(lst[i - 1], lst[i], lst[i + 1]):
            sum += 1
    return sum

def split_num_to_list(n: int) -> list[int]:
    lst = []
    while n > 0:
        lst.append(n % 10)
        n //= 10
    lst.reverse()
    return lst

@cache
def dp(prev: int, rise_fall: int, start: bool, digits: int) -> int:
    if digits == 0:
        return 0
    
    if start:
        res = 0
        for i in range(1, 10):
            res += dp(i, 0, 0, digits - 1)
        return res
    
    res = 0
    for i in range(0, 10):
        if i > prev and rise_fall == -1:
            res += pow(10, digits - 1) + dp(i, 1, 0, digits - 1)
        elif i < prev and rise_fall == 1:
            res += pow(10, digits - 1) + dp(i, -1, 0, digits - 1)
        else:
            res += dp(i, clip(i - prev), 0, digits - 1)
    return res

def helper(idx: int, num: list[int]) ->int:
    if idx == len(num):
        return count_peak_valley(num)
    
    sum = 0
    if idx == 0:
        for i in range(1, len(num)):
            sum += dp(0, 0, 1, i)
    
    for i in range(0 + (idx == 0), num[idx]):
        rise_fall = 0 if idx == 0 else clip(i - num[idx - 1])
        # here we have to multiply all the times wavliness(num[0:idx] + [i]) can appear
        sum += count_peak_valley(num[0:idx] + [i]) * pow(10, len(num) - idx - 1) + dp(i, rise_fall, 0, len(num) - idx - 1)
    sum += helper(idx + 1, num)

    return sum

class Solution:
    def totalWaviness(self, num1: int, num2: int) -> int:
        return helper(0, split_num_to_list(num2)) - helper(0, split_num_to_list(num1 - 1))

print([1,2,3] + [2])
print(helper(0, [1,2,3,4,5]))