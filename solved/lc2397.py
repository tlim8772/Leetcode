class Solution:
    def check_all_rows_covered(self, bm: int, matrix: list[list[int]]) -> bool:
        COLS = len(matrix[0])

        num_rows = 0
        for r in matrix:
            all_covered = True
            
            for i in range(COLS):
                if r[i] == 0:
                    continue
                
                if ((bm >> i) & 1) == 0:
                    all_covered = False
                    break

            num_rows += all_covered
        
        return num_rows
    
    def gen_bm(self, idx: int, lim: int, count: int, bm: int, store: list[int]):
        if count == 0:
            store.append(bm)
            return
        
        if idx == lim:
            if count == 0:
                store.append(bm)
            return
        
        self.gen_bm(idx + 1, lim, count - 1, bm + (1 << idx), store)
        self.gen_bm(idx + 1, lim, count, bm, store)
        
        


    
    def maximumRows(self, matrix: list[list[int]], numSelect: int) -> int:
        valid_bms = []
        self.gen_bm(0, len(matrix[0]), numSelect, 0, valid_bms)
        #print(valid_bms)
        mapped = map(lambda bm: self.check_all_rows_covered(bm, matrix), valid_bms)
        #print(list(mapped))
        return max(map(lambda bm: self.check_all_rows_covered(bm, matrix), valid_bms))
    
sol = Solution()
matrix = [[0,0,0],[1,0,1],[0,1,1],[0,0,1]]; numSelect = 2
print(sol.maximumRows(matrix, numSelect))

