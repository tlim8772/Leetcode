from collections import defaultdict

'''
balanced subarray: # distinct even numbers == # distinct odd numbers

high level idea:
for each l in [0,n):
    find the rightmost r s.t [l,r] is balanced

we store a segment tree where each index is [-1, 1, 0].
-1 if it is the 1st odd number, 1 if it is the 1st even number, 0 if the number is not distinct anymore.
then segtree[i] = sum of the elems in [l, i].
given l, we want to find the largest r s.t segtree[r] = 0

KEY IDEA: consective entries in the segtree differ by 1 or 0, we can answer the abve query by storing the
(min, max) of the range. if (min, max) contains 0, then this range has 0, else it does not

when we move from l to l + 1, find the next occurence of nums[l], eg at kth pos, 
then adjust the elems in segtree[l + 1, k - 1] i.e -1 if nums[l] is even or +1 if nums[l] is odd

then for l + 1, find the rightmost elem that is 0
'''
class SegTree:
    def __init__(self, arr: list[int]):
        self.n = len(arr)
        self.tree: list[list[int]] = [[0, 0] for _ in range(4 * self.n)]
        self.accu: list[int] = [0 for _ in range(4 * self.n)]
        self.build(0, 0, self.n - 1, arr)
        

    def build(self, p: int, s: int, e: int, arr: list[int]) -> None:
        if s == e:
            self.tree[p] = [arr[s], arr[s]]
            return
        
        m = (s + e) >> 1
        self.build((p << 1) + 1, s, m, arr)
        self.build((p << 1) + 2, m + 1, e, arr)
        self.tree[p][0] = min(self.tree[(p << 1) + 1][0], self.tree[(p << 1) + 2][0])
        self.tree[p][1] = max(self.tree[(p << 1) + 1][1], self.tree[(p << 1) + 2][1])
        
    def range_add(self, l: int, r: int, val: int, p: int = 0, s: int = 0, e: int = -1, acc: int = 0) -> None:
        if e == -1:
            e = self.n - 1
        
        if s == e or (s == l and e == r):
            self.accu[p] += val
            for i in range(2):
                self.tree[p][i] += val
            return
        
        m = (s + e) >> 1
        new_acc = acc + self.accu[p]
        if r <= m:
            self.range_add(l, r, val, (p << 1) + 1, s, m, new_acc)
        elif l > m:
            self.range_add(l, r, val, (p << 1) + 2, m + 1, e, new_acc)
        else:
            self.range_add(l, m, val, (p << 1) + 1, s, m, new_acc)
            self.range_add(m + 1, r, val, (p << 1) + 2, m + 1, e, new_acc)
        
        self.tree[p][0] = new_acc + min(self.tree[(p << 1) + 1][0], self.tree[(p << 1) + 2][0]) - acc
        self.tree[p][1] = new_acc + max(self.tree[(p << 1) + 1][1], self.tree[(p << 1) + 2][1]) - acc

    def query(self, l: int, r: int, p: int = 0, s: int = 0, e: int = -1, acc: int = 0) -> tuple[int,int]:
        if e == -1:
            e = self.n - 1
        
        if s == e or (s == l and e == r):
            return (self.tree[p][0] + acc, self.tree[p][1] + acc)
        
        m = (s + e) >> 1
        new_acc = acc + self.accu[p]
        if r <= m:
            return self.query(l, r, (p << 1) + 1, s, m, new_acc)
        elif l > m:
            return self.query(l, r, (p << 1) + 2, m + 1, e, new_acc)
        else:
            lans = self.query(l, m, (p << 1) + 1, s, m, new_acc)
            rans = self.query(m + 1, r, (p << 1) + 2, m + 1, e, new_acc)
            return (min(lans[0], rans[0]), max(lans[1], rans[1]))
        
    def find_righmost0(self, p: int = 0, s: int = 0, e: int = -1, acc: int = 0) -> int:
        if e == -1:
            e = self.n - 1
        
        arr = list(map(lambda x: x + acc, self.tree[p]))
        if arr[1] < 0 or arr[0] > 0:
            return -1
        elif s == e:
            return s
        
        m = (s + e) >> 1
        new_acc = acc + self.accu[p]
        rans = self.find_righmost0((p << 1) + 2, m + 1, e, new_acc)
        return rans if rans > -1 else self.find_righmost0((p << 1) + 1, s, m, new_acc)
        


        

class Solution:
    def longestBalanced(self, nums: list[int]) -> int:
        elem_pos: defaultdict[int, list[int]] = defaultdict(list)
        for i in range(len(nums) - 1, -1, -1):
            elem_pos[nums[i]].append(i)

        seen: set[int] = set()
        arr = [0 for _ in range(len(nums))]
        arr[0] = -1 if nums[i] & 1 else 1
        seen.add(nums[0])
        for i in range(1, len(nums)):
            if nums[i] in seen:
                arr[i] = arr[i - 1]
                continue
            seen.add(nums[i])
            arr[i] = arr[i - 1] + (-1 if nums[i] & 1 else 1)
        #print(arr)
        st = SegTree(arr)
        best = 0
        for i in range(len(nums)):
            res = st.find_righmost0()
            if res >= i:
                best = max(best, res - i + 1)

            elem_pos[nums[i]].pop()
            next = elem_pos[nums[i]][-1] if len(elem_pos[nums[i]]) > 0 else len(nums)
            change = 1 if nums[i] & 1 else -1
            st.range_add(i, next - 1, change)
        return best
    
sol = Solution()
print(sol.longestBalanced([8,8,31,42]))


        
            
        
 
    