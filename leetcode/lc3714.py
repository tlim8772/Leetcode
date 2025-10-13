from functools import reduce
from collections import defaultdict

'''
split into 3 cases
case 1: 1 distinct character only

case 2: 2 distinct characters only. How to find ? at index i, find cnt(a) - cnt(b).
        for any 2 indice with the same difference, then [i, j] is a valid substring.

case 3: maintain a tuple (cnt(a) - cnt(b), cnt(a) - cnt(c)).
        if 2 indices i, jhave the same tuple, then s[i:j + 1] is a valid substring.

'''

def case1(s: str) -> int:
    best = 0
    curr_char, curr_cnt = s[0], 0
    for c in s:
        if c == curr_char:
            curr_cnt += 1
        else:
            best = max(best, curr_cnt)
            curr_char = c
            curr_cnt = 1
    best = max(best, curr_cnt)
    return best

def helper2(s: str, c1: str, c2: str) -> int:
    diff = 0
    store: defaultdict[int, list[int]] = defaultdict(list)
    store[0].append(-1)
    
    for i in range(len(s)):
        diff = diff + 1 if s[i] == c1 else diff - 1
        store[diff].append(i)
    
    return reduce(lambda acc, x: max(acc, x[-1] - x[0]), store.values(), 0)

def case2(s: str) -> int:
    chars = 'abc'
    best = 0
    for i in range(len(chars)):
        for j in range(i + 1, len(chars)):
            p = 0
            for k in range(len(s)):
                if s[k] != chars[i] and s[k] != chars[j]:
                    best = max(best, helper2(s[p:k], chars[i], chars[j]))
                    p = k + 1
            best = max(best, helper2(s[p:], chars[i], chars[j]))
    return best

'''
chars are only a, b, c
diff1 = cnt(a) - cnt(b), diff2 = cnt(a) - cnt(c)
'''
def case3(s: str) -> int:
    diff1, diff2 = 0, 0
    store: defaultdict[tuple[int,int], list[int]] = defaultdict(list)
    store[(0, 0)].append(-1)

    for i in range(len(s)):
        if s[i] == 'a':
            diff1 += 1
            diff2 += 1
        elif s[i] == 'b':
            diff1 -= 1
        else:
            diff2 -= 1
        store[(diff1, diff2)].append(i)

    return reduce(lambda acc, x: max(acc, x[-1] - x[0]), store.values(), 0)
    

class Solution:
    def longestBalanced(self, s: str) -> int:
        return max(case1(s), case2(s), case3(s))
    
sol = Solution()
s = 'abbac'
print(sol.longestBalanced(s))