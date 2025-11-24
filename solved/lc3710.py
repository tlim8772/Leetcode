from typing import TypeVar, Generic, Callable, List
from collections import defaultdict
import math

'''
view the problem as a graph, we have a clique Kn, and weight of each edge is the manhatten
distance between node i and node j.
consider all edges with weight >= k, there exists a valid partition i.e each partition is a clique 
if the complement is a bipartite graph.
proof =>
if there exist a valid partition s.t each partition is a clique, in the complement graph, there are no
edges in each of the partition, and only edges from partition 1 to partition 2.
proof <=
then for each partition, in the original graph, must be a clique.

what if the graph has > 2 connected components, then the complement graph can never be bipartite.
because there is an odd cycle, actually a triangle
'''


def manhatten_dist(p1: list[int], p2: list[int]) -> int:
    return abs(p1[0] - p2[0]) + abs(p1[1] - p2[1])

class Solution:
    def __init__(self):
        self.man_dist_dict: defaultdict[tuple[int,int], int] = defaultdict(int)
    
    def store_man_dist(self, points: list[list[int]]):
        for i in range(len(points)):
            for j in range(i + 1, len(points)):
                self.man_dist_dict[(i, j)] = manhatten_dist(points[i], points[j])

    def check_bipartite(self, v: int, color: int, points: list[list[int]], visited: list[int], lower_bound: int) -> bool:
        visited[v] = color
        for j in range(len(points)):
            if v == j:
                continue
            elif self.man_dist_dict[(min(v, j), max(v, j))] >= lower_bound:
                continue
            elif visited[j] != -1:
                if visited[v] == visited[j]:
                    return False
            else:
                ans = self.check_bipartite(j, 1 - color, points, visited, lower_bound)
                if not ans:
                    return False
        return True

    
    def helper(self, points: List[List[int]], lower_bound: int) -> bool:
        visited = [-1 for _ in range(len(points))]
        for i in range(len(points)):
            if visited[i] != -1:
                continue
            
            ans = self.check_bipartite(i, 0, points, visited, lower_bound)
            if not ans:
                return False
        
        return True

    def maxPartitionFactor(self, points: List[List[int]]) -> int:
        if len(points) <= 2:
            return 0
        
        self.store_man_dist(points)
        
        s, e = 0, int(4e10)
        while s < e:
            m = (s + e + 1) // 2
            ans = self.helper(points, m)
            if ans:
                s = m
            else:
                e = m - 1
        

        return s

sol = Solution()
points = [[0,0],[0,2],[2,0],[2,2]]
print(sol.maxPartitionFactor(points))