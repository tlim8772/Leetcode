from collections import Counter

'''
how this question is hard and has an initial acceptance rate of ~10% after contest is baffling.
2 pass stack solution.
for 1st pass, we pop char larger than char we are currently processing if count[to_pop_char] > 1
2nd pass is for strings like 'aa'
we remove char if the last stack2 char is empty char i.e '', or is lesser than char,
else we put it in stack2.
reverse stack2 and join
'''

class Solution:
    def lexSmallestAfterDeletion(self, s: str) -> str:
        store: Counter[str] = Counter(s)
        stack: list[str] = []

        for c in s:
            while len(stack) > 0 and (last := stack[-1]) > c and store[last] > 1:
                stack.pop()
                store[last] -= 1
            stack.append(c)

        stack2: list[str] = []
        for c in stack[::-1]:
            if (last := store[c]) > 1 and (len(stack2) == 0 or stack2[-1] < c):
                store[c] -= 1
                continue
            stack2.append(c)


        return ''.join(stack2[::-1])
                


sol = Solution()
print(sol.lexSmallestAfterDeletion('cdeabzbzcde'))