import itertools

# just check all squares.
# use prefix squares to reduce the time complexity of checking to O(n) instead of O(n^2),
# where n is the length of the square.

class Store:
    def __init__(self, grid: list[list[int]]):
        self.grid = grid
        self.R = len(grid)
        self.C = len(grid[0])
        self.store = [[0 for _ in range(self.C)] for _ in range(self.R)]
        self.dp()

    def valid(self, r: int, c: int) -> bool:
        return r >= 0 and r < self.R and c >= 0 and c < self.C

    def dp(self):
        DIRS = [(-1, -1, -1), (-1, 0, 1), (0, -1, 1)]
        for k in range(0, self.R + self.C - 1):
            for r in range(max(0, k - self.C + 1), min(self.R - 1, k) + 1):
                c = k - r
                sum = self.grid[r][c]
                
                for dx, dy, sign in DIRS:
                    nr, nc = r + dx, c + dy
                    if not self.valid(nr, nc):
                        continue
                    sum += self.store[nr][nc] * sign

                self.store[r][c] = sum

    def query(self, tx: int, ty: int, bx: int, by: int) -> int:
        sum = 0
        
        if self.valid(tx - 1, ty - 1):
            sum += self.store[tx - 1][ty - 1]
        
        if self.valid(tx - 1, by):
            sum -= self.store[tx - 1][by]
        
        if self.valid(bx, ty - 1):
            sum -= self.store[bx][ty - 1]

        sum += self.store[bx][by]
        return sum

def count_diagonal(tx: int, ty: int, bx: int, by: int, dir: str, grid: list[list[int]]) -> int:
    if dir == 'up':
        dir = (-1, 1)
    elif dir == 'down':
        dir = (1, 1)
    else:
        raise ValueError('invalid dir')
    
    sum = 0
    while True:
        sum += grid[tx][ty]
        if tx == bx and ty == by:
            break
        tx += dir[0]
        ty += dir[1]
    return sum


class Solution:
    def largestMagicSquare(self, grid: list[list[int]]) -> int:
        R, C = len(grid), len(grid[0])
        store = Store(grid)
        best = 1
        for r, c in itertools.product(range(R), range(C)):
            for l in range(2, min(R - r, C - c) + 1):
                key = store.query(r, c, r, c + l - 1)
                res = True

                # check rows
                for row in range(r, r + l):
                    if store.query(row, c, row, c + l - 1) != key:
                        res = False
                        break
                
                # check cols
                if res:
                    for col in range(c, c + l):
                        if store.query(r, col, r + l - 1, col) != key:
                            res = False
                            break

                # check down diag
                if res:
                    if count_diagonal(r, c, r + l - 1, c + l - 1, 'down', grid) != key:
                        res = False

                # check up diag
                if res:
                    if count_diagonal(r + l - 1, c, r, c + l - 1, 'up', grid) != key:
                        res = False

                if res:
                    best = max(best, l)
        return best
                        



sol = Solution()
grid = [[8,1,6],[3,5,7],[4,9,2],[7,10,9]]
print(sol.largestMagicSquare(grid))

