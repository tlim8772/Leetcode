from typing import List
from collections import defaultdict
from sortedcontainers import SortedList

'''
use a hashmap with key=(last elem, prefix sum) and value is all the pos in the array with key
for index i
find number of indices j, with j >= i + 2 and key=(capacity[i], prefix_sums[i] + 2 * capacity[i])
'''

class Solution:
    def countStableSubarrays(self, capacity: List[int]) -> int:
        store: defaultdict[tuple[int,int], SortedList[int]] = defaultdict(SortedList)
        
        prefix_sums = [0 for _ in range(len(capacity))]
        curr = 0
        for i in range(len(capacity)):
            curr += capacity[i]
            store[(capacity[i], curr)].add(i)
            prefix_sums[i] = curr

        cnt = 0
        for i in range(len(capacity)):
            target = (capacity[i], prefix_sums[i] + 2 * capacity[i])
            lst = store[target]
            idx = lst.bisect_left(i + 2)
            cnt += len(lst) - idx

        return cnt
    

sol = Solution()
cap = [9,3,3,3,9]
print(sol.countStableSubarrays(cap))
