from functools import cache, reduce
import math

def digit_sum(x: int) -> int:
    s = 0
    while x > 0:
        s += x % 10
        x = x // 10
    return s

def is_mono_incr(num: int) -> bool:
    s = str(num)
    for i in range(0, len(s) - 1):
        if s[i] >= s[i + 1]:
            return False
    return True

def is_mono_decr(num: int) -> bool:
    s = str(num)
    for i in range(0, len(s) - 1):
        if s[i] <= s[i + 1]:
            return False
    return True

def is_mono_incr_str(s: str) -> bool:
    for i in range(0, len(s) - 1):
        if s[i] >= s[i + 1]:
            return False
    return True

def is_mono_decr_str(s: str) -> bool:
    for i in range(0, len(s) - 1):
        if s[i] <= s[i + 1]:
            return False
    return True

def is_good(num):
    return is_mono_incr(num) or is_mono_decr(num)

@cache
def mono_incr_and_good_sum(prev_d: int, d_left: int, sum: int) -> int:
    if d_left == 0:
        return is_good(sum)
    
    if prev_d == 9:
        return 0
    
    total = 0
    for d in range(prev_d + 1, 10):
        total += mono_incr_and_good_sum(d, d_left - 1, sum + d)
    return total

@cache
def mono_decr_and_good_sum(prev_d: int, d_left: int, sum: int) -> int:
    if d_left == 0:
        return is_good(sum)
    
    if prev_d == 0:
        return 0
    
    total = 0
    for d in range(prev_d - 1, -1, -1):
        total += mono_decr_and_good_sum(d, d_left - 1, sum + d)
    return total

@cache
def good_sum(d_left: int, sum: int) -> int:
    if d_left == 0:
        return is_good(sum)
    
    return reduce(lambda a, x: a + good_sum(d_left - 1, sum + x), range(10), 0)

# returns numbers with d_left digits, that are at least
# mono incr, mono decr, sum of digits is good
def fancy(d_left: int) -> int:
    if d_left == 1:
        return 9
    
    mono_decr_and_mono_incr_and_good_sum_cnt = 0
   
    mono_decr_and_mono_incr_cnt = 0
    mono_decr_and_good_sum_cnt = reduce(lambda a, x: a + mono_decr_and_good_sum(x, d_left - 1, x), range(9, 0, -1), 0)
    mono_incr_and_good_sum_cnt = reduce(lambda a, x: a + mono_incr_and_good_sum(x, d_left - 1, x), range(1, 10), 0)

    mono_decr_cnt = math.comb(10, d_left)
    mono_incr_cnt = math.comb(9, d_left) # can only choose from 1 to 9.
    good_sum_cnt = reduce(lambda a, x: a + good_sum(d_left - 1, x), range(1, 10), 0)

    return mono_decr_cnt + mono_incr_cnt + good_sum_cnt \
    - mono_decr_and_mono_incr_cnt - mono_decr_and_good_sum_cnt - mono_incr_and_good_sum_cnt \
    + mono_decr_and_mono_incr_and_good_sum_cnt

# eiter mono increasing or sum is good
def fancy_incr_prev(start: bool, prev_d: int, d_left: int, sum: int) -> int:
    if d_left == 1:
        return reduce(lambda a, x: a + (x > prev_d or is_good(sum + x)), range(10), 0)
    
    mono_incr_and_good = reduce(lambda a, x: a + mono_incr_and_good_sum(x, d_left - 1, sum + x), range(prev_d + 1, 10), 0)
    
    good = reduce(lambda a, x: a + good_sum(d_left - 1, x), range(1 if start else 0, 10), 0)
    mono_incr = math.comb(9 - prev_d, d_left)
    
    return good + mono_incr - mono_incr_and_good

# either mono decrasing or sum is good
def fancy_decr_prev(start: bool, prev_d: int, d_left: int, sum: int) -> int:
    if d_left == 1:
        return reduce(lambda a, x: a + (x < prev_d or is_good(sum + x)), range(10), 0)
    
    mono_decr_and_good = reduce(lambda a, x: a + mono_decr_and_good_sum(x, d_left - 1, sum + x), range(9, 0 if start else -1, -1), 0)

    good = reduce(lambda a, x: a + good_sum(d_left - 1, x), range(1 if start else 0, 10), 0)
    mono_decr = math.comb(prev_d, d_left)

    return good + mono_decr - mono_decr_and_good

'''
basically we keep using Principle of Inclusion and Exclusion
'''    
def count_fancy(r: int | str, idx: int = 0, sum: int = 0,) -> int:
    if idx == 0 and 0 < r < 10:
        return r
    
    if isinstance(r, int):
        r = str(r)

    if idx == len(r):
        return is_good(int(r)) or is_good(sum)
    
    if idx == 0:
        d = int(r[idx])
        
        take = count_fancy(r, 1, sum + d)

        less_digits = reduce(lambda a, d_left: a + fancy(d_left), range(1, len(r)), 0)

        digits = [i for i in range(1, d)]
        
        mono_incr = 0
        for i in digits:
            mono_incr += math.comb(9 - i, len(r) - 1)

        mono_decr = 0
        for i in digits:
            mono_decr += math.comb(i, len(r) - 1)

        good = 0
        for i in digits:
            good += good_sum(len(r) - 1, i)

        mono_incr_and_good = 0
        for i in digits:
            mono_incr_and_good += mono_incr_and_good_sum(i, len(r) - 1, i)

        mono_decr_and_good = 0
        for i in digits:
            mono_decr_and_good += mono_decr_and_good_sum(i, len(r) - 1, i)

        notake = mono_incr + mono_decr + good - mono_incr_and_good - mono_decr_and_good

        return less_digits + notake + take
    
    d = int(r[idx])
    
    take = count_fancy(r, idx + 1, sum + d)

    digits = [i for i in range(0, d)]

    mono_incr = 0
    if is_mono_incr(r[:idx]):
        for i in digits:
            if is_mono_incr_str(r[:idx] + str(i)):
                mono_incr += math.comb(9 - i, len(r) - idx - 1)
    
    mono_decr = 0
    if is_mono_decr(r[:idx]):
        for i in digits:
            if is_mono_decr_str(r[:idx] + str(i)):
                mono_decr += math.comb(i, len(r) - idx - 1)

    good = 0
    for i in digits:
        good += good_sum(len(r) - idx - 1, sum + i)
    
    mono_incr_and_good = 0
    for i in digits:
        if is_mono_incr_str(r[:idx] + str(i)):
            mono_incr_and_good += mono_incr_and_good_sum(i, len(r) - idx - 1, sum + i)

    mono_decr_and_good = 0
    for i in digits:
        if is_mono_decr_str(r[:idx] + str(i)):
            mono_decr_and_good += mono_decr_and_good_sum(i, len(r) - idx - 1, sum + i)

    notake = mono_incr + mono_decr + good - mono_incr_and_good - mono_decr_and_good
    return take + notake

    
class Solution:
    def countFancy(self, l: int, r: int) -> int:
        return count_fancy(r) - (count_fancy(l - 1) if l > 1 else 0)

    
    




'''  
ans = fancy_incr_prev(True, 0, 3, 0)
ans2 = reduce(lambda a, x: a + (is_mono_incr(x) or is_good(digit_sum(x))), range(100, 1000), 0)
print(ans, ans2)

ans3 = fancy_decr_prev(True, 10, 3, 0)
ans4 = reduce(lambda a, x: a + (is_mono_decr(x) or is_good(digit_sum(x))), range(100, 1000), 0)
print(ans3, ans4)
'''

print(count_fancy(43000))

    
    


