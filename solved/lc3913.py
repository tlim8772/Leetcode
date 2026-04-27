from collections import Counter

class Solution:
    def sortVowels(self, s: str) -> str:
        vowels = ['a', 'e', 'i', 'o', 'u']
        cnter = Counter(s)
        vowel_cnt = filter(lambda p: p[0] in vowels, cnter.items())
        sorted_vowel_cnt = sorted(vowel_cnt, key=lambda p: p[1], reverse=True)
        vowel_str = ''.join(map(lambda p: p[0] * p[1], sorted_vowel_cnt))
        ptr = 0

        out = []
        for i in range(len(s)):
            if s[i] in vowels:
                out.append(vowel_str[ptr])
                ptr += 1
            else:
                out.append(s[i])
        return ''.join(out)
    
sol = Solution()

s = 'leetcode'
print(sol.sortVowels(s))