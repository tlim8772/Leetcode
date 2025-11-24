from typing import *

'''
cute problem
just start from top glass, let say we pour x litres, then x - 1 litres will spillover to next row,
the 2 cups will receive half of the excess, consider the excess of the bottom 2 cups and continue
'''

class Solution:
    def champagneTower(self, poured: int, query_row: int, query_glass: int) -> float:
        lst: List[List[float]] = []
        for i in range(100):
            lst.append([0 for j in range(i + 1)])

        lst[0][0] = poured
        for i in range(99):
            for j in range(i + 1):
                left = lst[i][j] - 1
                
                if lst[i][j] > 1: 
                    lst[i][j] = 1
                
                if left > 0:
                    lst[i + 1][j] += left / 2
                    lst[i + 1][j + 1] += left / 2
                
                #print(lst[i][j])

        return lst[query_row][query_glass]

sol = Solution()
print(sol.champagneTower(100000009, 33, 17))


        