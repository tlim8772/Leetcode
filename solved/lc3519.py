from functools import cache
import sys
sys.setrecursionlimit(1000000)
MOD = int(1e9 + 7)

'''
use python to handle BigIntegers. It is simple digit dp once we convert the string in base 10 to base b
'''

# the last digit is nuum % base, then num = num / base and repeat
def convert_base(s: str, base: int) -> str: 
    num = int(s)
    lst = []
    
    while num > 0:
        a = num % base
        num = num // base
        lst.append(str(a))

    return ''.join(reversed(lst))


 # we do not need to worry about 0, as there cannot be any
@cache
def helper(prev: int, left: int, base: int) -> int:
    if left == 0:
        return 1
    elif prev == base:
        return 0
    
    # next digit is prev or > prev. Better then looping over all possible values of next digit
    ans = helper(prev, left - 1, base) + helper(prev + 1, left, base)
    ans %= MOD
    return ans
    

# the number considered have the same number of digits
def helper2(prev: int, i: int, s: str, base: int) -> int:
    if i == len(s):
        return 1
    
    prev = 1 if i == 0 else max(prev, int(s[i - 1]))
    curr_digit = int(s[i])

    take_same = 0 if curr_digit < prev else helper2(prev, i + 1, s, base)

    # to get all possible values with curr digit in [prev, lim - 1], we can subtract to make use of 
    # how helper is defined
    take_lesser = 0 if curr_digit <= prev else helper(prev, len(s) - i, base) - helper(int(s[i]), len(s) - i, base)
    
    ans = take_same + take_lesser
    ans %= MOD
    return ans

def count_leq(s: str, base: int) -> int:
    sum = 0
    for i in range(1, len(s)):
        sum += helper(1, i, base)
    
    same_digit_cnt = helper2(1, 0, s, base)
    #print(sum)
    #print(same_digit_cnt)
    
    ans = sum + same_digit_cnt
    ans %= MOD
    return ans

    

class Solution:
    def countNumbers(self, l: str, r: str, b: int):
        l = str(int(l) - 1)
        left_ans = 0 if l == '0' else count_leq(convert_base(l, b), b)
        right_ans = count_leq(convert_base(r, b), b)

        return (right_ans - left_ans + MOD) % MOD
    

   

base = 9
print(count_leq(convert_base('122', base), base))
print(count_leq(convert_base('12345678912', base), base))

s = Solution()
print(s.countNumbers('23', '28', 8))
