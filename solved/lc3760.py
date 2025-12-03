'''
greedy. start from left to right, if see a new char, add 1 to cnt.
max # of substring (or cnt) is 26.
'''


class Solution:
    def maxDistinct(self, s: str) -> int:
        seen = set()
        cnt = 0
        for c in s:
            if c not in seen:
                seen.add(c)
                cnt += 1
        return cnt