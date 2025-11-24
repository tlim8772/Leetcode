from typing import List
'''
for each index i of target, we want to find the longest prefix starting at i s.t it is a prefix of a word in words.
we use string hashing, hash all prefixes of word in words.
use binary search at each index i of target

for each index i of target, if the longest prefix is of length l,
we can go to dp[i + 1], dp[i + 2] ... dp[i + l].
we can also form the entire prefix if i + l == len(target).
use segment tree to find min(dp[i + 1], dp[i + 2] ... dp[i + l]).
'''

P, M = 29, 602333120352133
powMod = [1 for _ in range(100000 + 1)]
powInvMod = [1 for _ in range(100000 + 1)]
invP = pow(P, -1, M)

for i in range(1, len(powMod)):
    powMod[i] = (P * powMod[i - 1]) % M
    powInvMod[i] = (invP * powInvMod[i - 1]) % M


class StringHash:
    def __init__(self, s: str):
        self.p = P
        self.m = M
    
        self.values = [0 for i in range(len(s))]
        self.values[0] = ord(s[0]) - ord('a') + 1
        for i in range(1, len(s)):
            self.values[i] = (ord(s[i]) - ord('a') + 1) * powMod[i] + self.values[i - 1]
            self.values[i] %= self.m

    # get the hash of s[s, e]
    def get_hash(self, s: int, e: int) -> int:
        l = 0 if s == 0 else self.values[s - 1]
        e = self.values[e]
        return ((e - l) * powInvMod[s]) % self.m
    
class SegTree:
    def __init__(self, n: int):
        self.n = n
        self.tree = [0 for i in range(4 * n)]

    def point_update(self, i: int, v: int, p: int = 0, s: int = 0, e: int = None):
        if e == None:
            e = self.n - 1

        if s == e:
            self.tree[p] = v
            return
        
        m = (s + e) >> 1
        if i <= m:
            self.point_update(i, v, (p << 1) + 1, s, m)
        else:
            self.point_update(i, v, (p << 1) + 2, m + 1, e)
        self.tree[p] = min(self.tree[(p << 1) + 1], self.tree[(p << 1) + 2])

    def range_query(self, l: int, r: int, p: int = 0, s: int = 0, e: int = None) -> int:
        if e == None:
            e = self.n - 1

        if s == e or (s == l and e == r):
            return self.tree[p]
        
        m = (s + e) >> 1
        if r <= m:
            return self.range_query(l, r, (p << 1) + 1, s, m)
        elif l > m:
            return self.range_query(l, r, (p << 1) + 2, m + 1, e)
        else:
            lres = self.range_query(l, m, (p << 1) + 1, s, m)
            rres = self.range_query(m + 1, r, (p << 1) + 2, m + 1, e)
            return min(lres, rres)
        
def get_prefix_hashes(words: list[str]) -> set[int]:
    out = set()
    for w in words:
        acc = 0
        for i, c in enumerate(w):
            acc += (ord(c) - ord('a') + 1) * powMod[i]
            acc %= M
            out.add(acc)

    return out

def get_longest_prefix_per_index(s: str, dic: set[int]):
    string_hash = StringHash(s)
    res = [-1 for _ in range(len(s))]
    for i in range(len(s)):
        start, end = i, len(s) - 1
        while start < end:
            m = (start + end + 1) // 2
            hash = string_hash.get_hash(i, m)
            if hash in dic:
                start = m 
            else:
                end = m - 1
        check = string_hash.get_hash(i, start)
        res[i] = start - i + 1 if check in dic else 0
    return res

class Solution:
    def minValidStrings(self, words: List[str], target: str) -> int:
        longest_prefix = get_longest_prefix_per_index(target, get_prefix_hashes(words))
        st = SegTree(len(target))
    
        last_res = 1 if longest_prefix[-1] != 0 else 999999
        st.point_update(len(target) - 1, last_res)
        for i in range(len(target) - 2, -1, -1):
            l = longest_prefix[i]

            if l == 0:
                st.point_update(i, 999999)
                continue

            start, end = i + 1, min(len(target) - 1, i + l)
            best = st.range_query(start, end)
            res = 1 if i + l == len(target) else 999999
            res = min(res, 1 + best)
            st.point_update(i, res)

        ans = st.range_query(0, 0)
        return ans if ans < 999999 else -1
    
sol = Solution()
words =  ["abc","aaaaa","bcdef"]
target = "aabcdabc"
print(sol.minValidStrings(words, target))

            


