from collections import defaultdict
from sortedcontainers import SortedDict
'''
similar to question on finding smallest permutation of s that is strictly larger than t.
but this time the permutation must be a palindrome.
we check i in [0, len(target) // 2], whether we can take target[i] (s.t later on, we make it larger)
or we have to take the smallest remaining character that > target[i]
'''

def canBePalindrome(s: str):
    out = defaultdict(int)
    for c in s:
        out[c] += 1
    
    odd, even = 0, 0
    for _, v in out.items():
        (even := even + 1) if v % 2 == 0 else (odd := odd + 1)

    return odd == 0 if len(s) % 2 == 0 else odd == 1

'''
self.store[i] = tuple[int, int]
index 0 contains whether we can make a palindrome string that is strictly greater than target
index 1 contains the action, 0 if we take target[i] or 1 if we take the smallest remaining character larger than target[i]
'''
class Solution:
    def __init__(self):
        self.store: list[tuple[int,int,str]] = []
        self.middle = '?'

    '''
    store[char] stores the number of uses of this char for the 1st half.
    store[char] is never 0.
    '''
    def helper(self, s: str, target: str, i: int, used: list[str], store: SortedDict[str,int]) -> bool:
        #print(used)
        if i == len(target) // 2:
            second_half = [self.middle] if len(target) % 2 == 1 else []
            second_half += list(reversed(used))
            second_half = ''.join(second_half)
            return True if target[len(target) // 2:] < second_half else False
        
        elif self.store[i][0] != -1:
            return self.store[i][0]
        
        same = False
        if target[i] in store:
            used.append(target[i])
            store[target[i]] -= 1
            if store[target[i]] == 0:
                store.pop(target[i])
            
            same = self.helper(s, target, i + 1, used, store)
            
            used.pop()
            if target[i] not in store:
                store[target[i]] = 1
            else:
                store[target[i]] += 1

        if same:
            self.store[i] = (True, 0, target[i])
            return True

        idx = store.bisect_right(target[i])
        if idx < len(store.keys()):
            self.store[i] = (True, 1, store.keys()[idx])
            return True
        else:
            self.store[i] = (False, -1, '?')
            return False

    def lexPalindromicPermutation(self, s: str, target: str) -> str:
        if not canBePalindrome(s):
            return ""
        
        self.store = [(-1, -1, '?') for i in range(len(s))]
        
        store: SortedDict[str,int] = SortedDict()
        for c in s:
            if c not in store:
                store[c] = 1
            else:
                store[c] += 1

        if len(s) % 2 == 1:
            for k, v in store.items():
                if v % 2 == 1:
                    self.middle = k

        for k in list(store.keys()):
            store[k] //= 2
            if store[k] == 0:
                store.pop(k)
    
        res = self.helper(s, target, 0, [], store)
        if not res:
            return ""
        
        out = []
       
        for i in range(0, len(s) // 2):
            _, action, c = self.store[i]
            store[c] -= 1
            out.append(c)
            if action == 1:
                for k, v in store.items():
                    out += [k for _ in range(v)]
                break

        second_half = list(reversed(out)) if len(s) % 2 == 0 else [self.middle] + list(reversed(out))
        ans = ''.join(out + second_half)
        return ans
        

        

sol = Solution()
s, target = "abababababababababab", "babababababababababa"
print(sol.lexPalindromicPermutation(s, target))