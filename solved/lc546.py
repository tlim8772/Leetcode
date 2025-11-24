from functools import *
from typing import *

def compress(lst: List[int]) -> List[List[int]]:
    out = []
    curr = lst[0]
    cnt = 0
    
    for i in range(len(lst)):
        if lst[i] == curr:
            cnt += 1
        else:
            out.append([curr, cnt])
            curr = lst[i]   
            cnt = 1
    out.append([curr, cnt])

    return out


class Solution:
    """
    first merge consecutive equal elements into elements [val, count]
    the 1st element (of the compressed array) is either remove itself or it can merge with another element
    of the same value
    dp(i, j, offset) = best result of subarray(i, j) with <offset> additional elements of value subarray[i][0]
    case 1: remove alone: result = cost to remove + dp(i + 1, j, 0)
    
    case 2: merge with some other element at index k 
    result = dp(i + 1, k - 1, 0) + dp(k, j, count + prev offset)
    
    """
    def removeBoxes(self, boxes: List[int]) -> int:
        compressed = compress(boxes)
        
        @cache
        def dp(i: int, j: int, offset: int) -> int:
            if i == j:
                return pow(compressed[i][1] + offset, 2)
            
            noMerge = pow(compressed[i][1] + offset, 2) + dp(i + 1, j, 0)

            curr = compressed[i][0]
            best = 0
            for k in range(i + 1, j + 1, 1):
                if compressed[k][0] != curr:
                    continue

                res = dp(i + 1, k - 1, 0) + dp(k, j, offset + compressed[i][1])
                best = max(best, res)
            
            res = max(best, noMerge)
            return res
        
        return dp(0, len(compressed) - 1, 0)
        

sol = Solution()
lst = [1,3,2,2,2,3,4,3,1]
print(sol.removeBoxes(lst))