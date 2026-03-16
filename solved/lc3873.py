'''
we use DSU, group points into connected components.
the best result is the sum of the top 2 connected components by size + 1.
to join 2 connected components, we simply choose 1 x value and 1 y value.
it cannot be that this (x, y) is already a point in any 1 of the 2 connected components, 
otherwise the 2 connected components will be joined together.
'''

from collections import defaultdict
import heapq

class DSU:
    def __init__(self, n: int):
        self.parents = [i for i in range(n)]
        self.weights = [1 for _ in range(n)]

    def find(self, u: int) -> int:
        p = self.parents[u]
        if p == u:
            return u
        top = self.find(p)
        self.parents[u] = top
        return top
    
    def join(self, u: int, v: int):
        pu, pv = self.find(u), self.find(v)
        if pu == pv:
            return
        wu, wv = self.weights[pu], self.weights[pv]
        if wu < wv:
            return self.join(v, u)
        self.parents[pv] = pu
        self.weights[pu] += wv

class Solution:
    def maxActivated(self, points: list[list[int]]) -> int:
        store_x: defaultdict[int, list[int]] = defaultdict(list)
        store_y: defaultdict[int, list[int]] = defaultdict(list)
        dsu = DSU(len(points))

        for i, p in enumerate(points):
            store_x[p[0]].append(i)
            store_y[p[1]].append(i)

        for _, v in store_x.items():
            for i in range(len(v) - 1):
                dsu.join(v[i], v[i + 1])
            
        for _, v in store_y.items():
            for i in range(len(v) - 1):
                dsu.join(v[i], v[i + 1])

        #print(dsu.parents, dsu.weights)

        cc_and_weights: list[tuple[int,int]] = []
        for i, pair in enumerate(zip(dsu.parents, dsu.weights)):
            if i != pair[0]:
                continue
            cc_and_weights.append((i, pair[1]))

        top2 = heapq.nlargest(2, cc_and_weights, key=lambda pair: pair[1])
        #print(top2)

        return sum(map(lambda p: p[1], top2)) + 1
    
sol = Solution()
points = [[1,1],[1,2],[2,2],[2,1]]
print(sol.maxActivated(points))



