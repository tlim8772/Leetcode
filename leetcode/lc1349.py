from functools import cache

'''
let dp(r, c, bm) be max # of students we can put given the current bitmask.
the bitmask store the top row and all students to the left in the current row.

example 
r = 1, c = 1
 .###
 #*..

r = 1, c = 2
..##
##*.

as we shift right, we pop the last element and append the new element (1 if we put a student, else 0).
'''

class Solution:
    def __init__(self):
        self.R = None
        self.C = None
        self.seats = None
        self.queue_bm = None
        
        self.DIRS = [(-1,-1), (-1,1), (0,-1)]
        

    def is_valid(self, r: int, c: int) -> bool:
        return r >= 0 and r < self.R and c >= 0 and c < self.C

    @cache
    def dp(self, r: int, c: int, bm: int) -> int:
        if r == self.R:
            return 0
        elif c == self.C:
            return self.dp(r + 1, 0, bm)
        elif self.seats[r][c] == '#':
            return self.dp(r, c + 1, (bm << 1) & self.queue_bm)
        
        up_left = not self.is_valid(r + self.DIRS[0][0], c + self.DIRS[0][1]) or not (bm >> self.C) & 1
        up_right = not self.is_valid(r + self.DIRS[1][0], c + self.DIRS[1][1]) or not (bm >> (self.C - 2)) & 1
        left = not self.is_valid(r + self.DIRS[2][0], c + self.DIRS[2][1]) or not bm & 1
        
        put, no_put = 0, 0
        if up_left and up_right and left:
            put = 1 + self.dp(r, c + 1, ((bm << 1) + 1) & self.queue_bm)
        no_put = self.dp(r, c + 1, (bm << 1) & self.queue_bm)
        
        return max(put, no_put)
            
    
    def maxStudents(self, seats: list[list[str]]) -> int:
        self.R, self.C = len(seats), len(seats[0])
        self.seats = seats
        self.queue_bm = (1 << (self.C + 1)) - 1
        #print(bin(self.queue_bm))
        return self.dp(0, 0, 0)

sol = Solution()   
seats = [["#",".",".",".","#"],[".","#",".","#","."],[".",".","#",".","."],[".","#",".","#","."],["#",".",".",".","#"]]
print(sol.maxStudents(seats))