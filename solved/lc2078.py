import heapq
# for each color get the leftmost and rightmost houses.
# then among all the different colors get the rightmost house and the 2nd rightmost.
# for each color, suppose it is the leftmost house, it will pair with the rightmost house
# unless the rightmost house is the same color, then take the 2nd best.

class Solution:
    def maxDistance(self, colors: list[int]) -> int:
        store: dict[int,list[int]] = {}

        for i, c in enumerate(colors):
            if c not in store:
                store[c] = [i, i]
            else:
                store[c][1] = i

        top2 = heapq.nlargest(2, map(lambda p: (p[0], p[1][1]), store.items()), key=lambda p: p[1])

        best = 0
        for c, lst in store.items():
            left = lst[0]
            if c == top2[0][0]:
                best = max(best, abs(left - top2[1][1]))
            else:
                best = max(best, abs(left - top2[0][1]))

        return best

sol = Solution()
colors = [1,1,1,6,1,1,1]
ans = sol.maxDistance(colors)
print(ans)
