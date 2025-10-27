from typing import List
from collections import defaultdict
from sortedcontainers import SortedList
'''
a subarray can be repeated iff it consists of the same elements.
we store indices based on their prefix sum % k in a hashmap.
if at index i, the start of the range of equal elems appear before, we only consider end indices after the range.
'''


'''
returns the [start, end) of a range of equal elems
'''
def get_start_end(nums: list[int]) -> list[tuple[int,int]]:
    start_end: list[tuple[int,int]] = [(-1, -1) for _ in range(len(nums))]
    i = 0
    while i < len(nums):
        pos, elem = i, nums[i]
        while i < len(nums) and nums[i] == elem:
            i += 1
        
        for p in range(pos, i):
            start_end[p] = (pos, i)
    return start_end

def collect_mod_k(nums: list[int], k: int) -> tuple[list[int], defaultdict[int, SortedList[int]]]:
    curr: int = 0
    prefix_sums: list[int] = [0 for _ in range(len(nums))]
    out: defaultdict[int, SortedList[int]] = defaultdict(SortedList)
    for i in range(len(nums)):
        curr += nums[i]
        prefix_sums[i] = curr
        
        m = curr % k
        out[m].add(i)

    return prefix_sums, out


class Solution:
    def numGoodSubarrays(self, nums: List[int], k: int) -> int:
        start_ends = get_start_end(nums)
        prefix_sums, store = collect_mod_k(nums, k)
        cnt = 0

        for i in range(len(nums)):
            left_mod = 0 if i == 0 else prefix_sums[i - 1] % k
            start, end = start_ends[i]
            pos_store = store[left_mod]
            lim = i if i == start else end
            ans = len(pos_store) - pos_store.bisect_left(lim)
            #print(i, ans)
            cnt += ans

        return cnt
        
sol = Solution()
nums = [2,2,2,2,2,2]
print(sol.numGoodSubarrays(nums, 3))