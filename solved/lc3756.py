'''
simple prefix queries, have to find mod inv, but python does that for us already in pow(base, exp, mod)
getting the concated string is simply dividing by the appropiate pow of 10
'''

MOD = int(1e9 + 7)

class Solution:
    def sumAndMultiply(self, s: str, queries: list[list[int]]) -> list[int]:
        prefix_arr = [0 for _ in range(len(s))]
        sum_arr = [0 for _ in range(len(s))]
        cnt_arr = [0 for _ in range(len(s))]
        
        for i in range(len(s) - 1, -1, -1):
            prev_prefix, prev_sum, prev_cnt = (0, 0, 0) if i == len(s) - 1 else (prefix_arr[i + 1], sum_arr[i + 1], cnt_arr[i + 1])
            if s[i] == '0':
                prefix_arr[i] = prev_prefix
                sum_arr[i] = prev_sum
                cnt_arr[i] = prev_cnt
            else:
                d = (int(s[i]) * pow(10, prev_cnt, MOD)) % MOD
                prefix_arr[i] = (d + prev_prefix) % MOD
                sum_arr[i] = (int(s[i]) + prev_sum) % MOD
                cnt_arr[i] = 1 + prev_cnt

        out: list[int] = []
        for q in queries:
            l, r = q[0], q[1]
            digit_sum = sum_arr[l] - (0 if r == len(s) - 1 else sum_arr[r + 1])
            num = prefix_arr[l] - (0 if r == len(s) - 1 else prefix_arr[r + 1])
            outside_cnt = 0 if r == len(s) - 1 else cnt_arr[r + 1]
            num *= pow(10, -outside_cnt, MOD)
           
            res = (num * digit_sum) % MOD
            out.append(res)
        
        return out

sol = Solution()
s = '10203004'
queries = [[0,7],[1,3],[4,6]]
print(sol.sumAndMultiply(s, queries))