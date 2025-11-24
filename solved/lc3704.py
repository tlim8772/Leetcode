import functools
import itertools

'''
we build a, b from right to left of normal number system.
a, b: index of a we are building. So a = 2 means we are considering the 10^2 digit
is_a_zero: means we put a 0 digit, so all subsequent digit we place on the left has to be 0 (so only leading 0s)
is_b_zero: see above
carry: means there is a carry so must add 1

if is_a_zero, never ever increment a again, there is no need.
this is to check if the number we build for a, b is 0.
'''
def dp1(a: int, b: int, i: int, carry: bool, is_a_zero: bool, is_b_zero: int, n: str, a_num: int, b_num: int) -> int:
    if i == len(n):
        if carry or a_num == 0 or b_num == 0:
            return 0 # because now we have a 1 in front
        else:
            print(a_num, b_num)
            return 1
    
   
    poss_a = [i for i in range(0, 10)] if not is_a_zero else [0]
    poss_b = [i for i in range(0, 10)] if not is_b_zero else [0]

    cnt = 0
    for pair in itertools.product(poss_a, poss_b):
        ans = carry + pair[0] + pair[1]
        if ans % 10 != int(n[i]):
            continue
        
        new_a = a_num + pair[0] * pow(10, a)
        new_b = b_num + pair[1] * pow(10, b)
        cnt += dp1(a + pair[0] != 0, b + pair[1] != 0, i + 1, ans // 10, pair[0] == 0, pair[1] == 0, n, new_a, new_b)
    
    return cnt

@functools.cache
def dp2(a: int, b: int, i: int, carry: bool, is_a_zero: bool, is_b_zero: int, n: str) -> int:
    if i == len(n):
        if carry or (a == 0 and is_a_zero) or (b == 0 and is_b_zero):
            return 0 # because now we have a 1 in front
        else:
            return 1
    
   
    poss_a = [i for i in range(0, 10)] if not is_a_zero else [0]
    poss_b = [i for i in range(0, 10)] if not is_b_zero else [0]

    cnt = 0
    for pair in itertools.product(poss_a, poss_b):
        ans = carry + pair[0] + pair[1]
        if ans % 10 != int(n[i]):
            continue
        
        cnt += dp2(a + pair[0] != 0, b + pair[1] != 0, i + 1, ans // 10, pair[0] == 0, pair[1] == 0, n)
    
    return cnt
            

class Solution:
    def countNoZeroPairs(self, n: int) -> int:
        rev_str = str(n)[::-1]
        return dp2(0, 0, 0, 0, 0, 0, rev_str)
    
sol = Solution()
n = 11
print(sol.countNoZeroPairs(n))