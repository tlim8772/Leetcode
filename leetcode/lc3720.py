from sortedcontainers import SortedList
'''
use dp
build the string from left to right.
at index i, we can either take smallest elem > target[i] or target[i] itself.
but it can be that taking target[i] is wrong.
see s = 'aab', t = 'abb'
so we use dp to handle these cases
dp(i) means is it possible to build strictly greater string s.t res[:i - 1] == target[:i - 1]
'''
class Solution:
    def __init__(self):
        self.store: list[int] = []

    # dp(i) means out[:i-1] == target[:i-1]
    # for index i, we can either take target[i] or the smallest elem > target[i]
    # dp(i) is 
    # 0 if we can target[i]
    # 1 if we must take a elem > target[i]
    # 2 if impossible to build a string
    # invariant: store should be unchanged when function finishes
    def helper(self, i: int, store: SortedList, target: str) -> int:
        if self.store[i] != -1:
            return self.store
        elif ''.join(store)[-1::-1] <= target[i:]:
            self.store[i] = 2
            return 2
        
        left_idx = store.bisect_left(target[i])
        if store[left_idx] > target[i]:
            self.store[i] = 1
            return 1
        else:
            c = store.pop(left_idx)
            res = self.helper(i + 1, store, target)
            store.add(c)
            
            if res != 2:
                self.store[i] = 0
                return 0
            else:
                self.store[i] = 1
                return 1

    def build(self, i: int, out: list[str], store: SortedList, target: str):
        if self.store[i] == 2:
            return ''
        elif self.store[i] == 1:
            idx = store.bisect_right(target[i])
            c = store.pop(idx)
            out.append(c)
            for next in store:
                out.append(next)
            return ''.join(out)
        else:
            out.append(target[i])
            store.discard(target[i])
            return self.build(i + 1, out, store, target)




    def lexGreaterPermutation(self, s: str, target: str) -> str:
        self.store = [-1 for _ in range(len(target))]
        store = SortedList(s)
        self.helper(0, store, target)
        return self.build(0, [], store, target)
    
sol = Solution()
s = 'leet'
t = 'code'
print(sol.lexGreaterPermutation(s, t))
        
