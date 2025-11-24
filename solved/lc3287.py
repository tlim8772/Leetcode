import copy

'''
use dp (kind of) to find all possible OR of k elems in range [0, i] and [i, n - 1].
use trie to find max e xor x, e in SetE and x in SetX.
we inser all elems of SetX into the trie.
given e, we check the largest power, if it is 0, we want 1, if 1 want 0, if cannot then take the equal elem.
The greedy choice of maximising the largest power always work as 2^x > 2^0 + 2^1 + 2^2 ... 2^x-1.
'''

class Node:
    def __init__(self):
        self.nexts = [None for _ in range(2)]

class Trie:
    def __init__(self):
        self.root = Node()
        self.cnt = 0

    def insert(self, x: int, p: int = 6, curr: Node = None):
        if p == -1:
            self.cnt += 1
            return
        
        if curr == None:
            curr = self.root

        c = (x >> p) & 1
        if curr.nexts[c] == None:
            curr.nexts[c] = Node()
        
        self.insert(x, p - 1, curr.nexts[c])


    def get_max(self, x: int, curr: Node, p: int = 6) -> int:
        if p == -1:
            return 0
        
        if curr == None:
            return -999999
        
        c = (x >> p) & 1
        ans = (1 << p) + self.get_max(x, curr.nexts[1 - c], p - 1) if curr.nexts[1 - c] != None else self.get_max(x, curr.nexts[c], p - 1)
        return ans

class Solution:
    def maxValue(self, nums: list[int], k: int) -> int:
        left_pass = [[set[int]() for _ in range(k + 1)] for i in range(len(nums))]
        right_pass = copy.deepcopy(left_pass)

        for i in range(len(nums)):
            left_pass[i][1].add(nums[i])

            if i != 0:
                for j in range(1, k + 1):
                    left_pass[i][j].update(left_pass[i - 1][j])
                    for e in left_pass[i - 1][j - 1]:
                        left_pass[i][j].add(nums[i] | e)
            
        for i in range(len(nums) - 1, -1, -1):
            right_pass[i][1].add(nums[i])
            
            if i != len(nums) - 1:
                for j in range(1, k + 1):
                    right_pass[i][j].update(right_pass[i + 1][j])
                    for e in right_pass[i + 1][j - 1]:
                        right_pass[i][j].add(nums[i] | e)
                           
        #print(left_pass)
        #print(right_pass)
        elems: dict[int,int] = {}
        trie = Trie()
        best = -1
        
        for i in range(len(nums) - k):
            for x in left_pass[i][k]:
                if x not in elems:
                    elems[x] = 1
                else:
                    elems[x] += 1
    
        for i in range(len(nums) - 1, len(nums) - k - 1, -1):
            for e in right_pass[i][k]:
                trie.insert(e)

        for i in range(len(nums) - k - 1, k - 2, -1):
            for x in elems:
                #print(i, x)
                res = trie.get_max(x, trie.root)
                best = max(best, res)

            for x in left_pass[i][k]:
                elems[x] -= 1
                if elems[x] == 0:
                    elems.pop(x)

            for x in right_pass[i][k]:
                trie.insert(x)

        return best
    
sol = Solution()
nums = [2,42]
k = 1
print(sol.maxValue(nums, k))

            
            
