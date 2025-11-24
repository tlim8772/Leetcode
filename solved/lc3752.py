'''
simple greedy. 
let curr_sum = sum(1,2...n).
then starting from the right, if curr_sum - 2 * (idx + 1) is >= target, we take it
greedy works suppose we can minus i, but the optimal solution is not to minus i
then we must minus j, j < i.
if there are at least 2 numbers, k + j to take over, we can replace it with m + i,
where m < k.
if only single number or k = 1, then it was not possible to minus 2 * i anyway
'''

class Solution:
    def lexSmallestNegatedPerm(self, n: int, target: int) -> list[int]:
        arr = [i + 1 for i in range(n)]
        curr_sum = sum(arr)
        
        idx = n - 1
        while curr_sum > target and idx >= 0:
            if curr_sum - 2 * (idx + 1) >= target:
                arr[idx] *= -1
                curr_sum -= 2 * (idx + 1)
            idx -= 1

        if curr_sum != target:
            return []
        else:
            arr.sort()
            return arr
        
sol = Solution()
print(sol.lexSmallestNegatedPerm(1, -3))
            
        