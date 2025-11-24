from functools import cache

'''
we only need the last m cells, suppose we are doing row = 1, col = 1
suppose, m = 5, n = 5

for r = 1, c = 1
we only need _xxxx
             x____

for r = 1, c = 2
we only need __xxx
             xx___
this way the table size is 5 5 * 5 * 3^5 * 6 * 6.
'''

@cache
def dp(r: int, c: int, prev: str, i: int, e: int, R: int, C: int) -> int:
    if r == R:
        return 0
    elif c == C:
        return dp(r + 1, 0, prev, i, e, R, C)
    
    
    put0, put1, put2 = 0, 0, 0
    put0 = dp(r, c + 1, (prev + '0')[1:], i, e, R, C)

    if i > 0:
        put1 += 120
        if prev[0] != '0':
            put1 -= 30
            put1 += -30 if prev[0] == '1' else 20
        
        if c > 0:
            if prev[-1] == '1':
                put1 -= 60
            elif prev[-1] == '2':
                put1 -= 10

        put1 += dp(r, c + 1, (prev + '1')[1:], i - 1, e, R, C)

    if e > 0:
        put2 += 40
        if prev[0] != '0':
            put2 += 20
            put2 += -30 if prev[0] == '1' else 20

        if c > 0:
            if prev[-1] == '1':
                put2 -= 10
            elif prev[-1] == '2':
                put2 += 40

        put2 += dp(r, c + 1, (prev + '2')[1:], i, e - 1, R, C)

    ans = max(put0, put1, put2)
    return ans

class Solution:
    def getMaxGridHappiness(self, m: int, n: int, introvertsCount: int, extrovertsCount: int) -> int:
        dp.cache_clear()
        return dp(0, 0, '0' * n, introvertsCount, extrovertsCount, m, n)

print(dp(0, 0, '000', 1, 2, 2, 3))
    
