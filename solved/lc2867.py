import math
'''
double dfs problem.
root the tree at node 1. (tree is 1 indexed)

dfs1 is to find for each subtree rooted at i, 
[# of paths with 1 prime starting at i, # of paths with 0 prime starting at i].

dfs2 is to find for each node, if we root it at that node,
[# of paths with 1 prime starting at i, # of paths with 0 prime starting at i]

so each path (a, b), a != b is counted twice, a == b is counted once (but we don't want this)
'''

class Sieve:
    def __init__(self, n: int):
        self.n = n
        self.is_prime = [True] * (n + 1)
        self.is_prime[0], self.is_prime[1] = False, False

        for i in range(2, int(math.sqrt(n)) + 1):
            if self.is_prime[i]:
                for j in range(i * i, self.n + 1, i):
                    self.is_prime[j] = False


sieve = Sieve(100000)


class Solution:
    def __init__(self):
        self.adj: list[list[int]] = None
        self.store: list[list[int]]= None
        self.num_primes: int = 0

    def initialise(self, n: int):
        self.adj = [[] for _ in range(0, n + 1)]
        self.store = [[0, 0] for _ in range(0, n + 1)]
        self.num_primes = 0

    def count_primes(self, n: int):
        for i in range(1, n + 1):
            if sieve.is_prime[i]:
                self.num_primes += 1

    def get_adj(self, edges: list[list[int]]):
        for e in edges:
            self.adj[e[0]].append(e[1])
            self.adj[e[1]].append(e[0])

    def dfs1(self, v: int, p: int):
        p1, p0 = 0, 0
        for c in self.adj[v]:
            if c == p:
                continue
            
            self.dfs1(c, v)
            p1 += self.store[c][0]
            p0 += self.store[c][1]

        if sieve.is_prime[v]:
            self.store[v][0] = 1 + p0
            self.store[v][1] = 0
        else:
            self.store[v][0] = p1
            self.store[v][1] = 1 + p0

    def dfs2(self, v: int, p: int):
        if v != p:
            if sieve.is_prime[v]:
                if sieve.is_prime[p]:
                    pass # nothing to do
                else:
                    self.store[v][0] += self.store[p][1]
            else:
                if sieve.is_prime[p]:
                    self.store[v][0] += self.store[p][0] - self.store[v][1]
                else:
                    self.store[v][0] += self.store[p][0] - self.store[v][0]
                    self.store[v][1] += self.store[p][1] - self.store[v][1] 
            
        for c in self.adj[v]:
            if c != p:
                self.dfs2(c, v)

        

    
    def countPaths(self, n: int, edges: list[list[int]]) -> int:
        self.initialise(n)
        self.count_primes(n)
        self.get_adj(edges)

        self.dfs1(1, 1)
        #print(self.store)
        self.dfs2(1, 1)
        #print(self.store)

        sum = 0
        for res in self.store:
            sum += res[0]
        sum -= self.num_primes
        sum //= 2
        return sum
    

sol = Solution()
n = 4
edges = [[1,2],[4,1],[3,4]]
print(sol.countPaths(n, edges))