from typing import List
from collections import defaultdict
from functools import reduce
'''
define the residue of a number to be prime factos whose power is odd.
for example 12 = 2^2 * 3, residue is (3), 35 = 5 * 7, residue is (5, 7).
x * y is square iff their residue are equal.
do dfs, store residue in a hashmap, when in a node, find the freq of the residue of this number
'''



'''
find whether a number is prime and also the prime factors of a number
'''
class Sieve:
    def __init__(self, n):
        self.n = n
        self.is_prime = [True for i in range(n + 1)]
        self.prime_factors: list[list[tuple[int,int]]] = [[] for _ in range(n + 1)]
        self.process()

    def process(self):
        curr = [i for i in range(self.n + 1)]
        for i in range(2, self.n + 1):
            if not self.is_prime[i]:
                continue
            
            for j in range(i * i, self.n + 1, i):
                self.is_prime[j] = False

            # calculating prime power for composite numbers eg 17^1, 17^2, 17^3
            for j in range(i, self.n + 1, i):
                p = 0
                while curr[j] % i == 0:
                    p += 1
                    curr[j] //= i
                self.prime_factors[j].append((i, p))

'''
Use global variable sieve here so we do not recompute sieve when processing a new test case.
it seriously works wth.
'''
sieve = Sieve(100000)

class Solution:
    def __init__(self):
        self.adj = []
        self.store: defaultdict[tuple[int, ...], int] = defaultdict(int)
        self.sieve: Sieve = sieve
    
    def getAdj(self, n: int, edges: list[list[int]]) -> list[list[int]]:
        self.adj = [[] for _ in range(n)]
        for e in edges:
            self.adj[e[0]].append(e[1])
            self.adj[e[1]].append(e[0])
    
    def dfs(self, v: int, p: int, nums: list[int]) -> int:
        residue = []
        for f in self.sieve.prime_factors[nums[v]]:
            if f[1] & 1:
                residue.append(f[0])
        residue = tuple(residue)
        
        sum = self.store[residue]
        self.store[residue] += 1
        
        for next in self.adj[v]:
            if next == p:
                continue
            sum += self.dfs(next, v, nums)
        
        self.store[residue] -= 1
        return sum
    
    def sumOfAncestors(self, n: int, edges: List[List[int]], nums: List[int]) -> int:
        #self.sieve = Sieve(max(nums))
        self.getAdj(n, edges)
        return self.dfs(0, 0, nums)
        

sol = Solution()
n = 14
edges = [[0,1],[1,2],[2,3],[2,4],[1,5],[1,6],[5,7],[4,8],[8,9],[7,10],[2,11],[10,12],[6,13]]
nums = [32889,32889,32889,32889,32889,32889,32889,32889,32889,32889,32889,32889,63895,64825]
print(sol.sumOfAncestors(n, edges, nums))


