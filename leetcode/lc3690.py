from typing import *

'''
Since len of array <= 6, we do bfs on all possible permutations of nums1.
Since nums2 is a permutation of nums1, we do compression, so num are [0,1,2,3,4,5].
The hash key is the 3 bits representation of [0..5] concated together.
Thing is we don't even need a hashmap because the key is unique.
Lets use python as we can have fancy list indexing.
'''

def hash(arr: List[int]) -> int:
    val = 0
    for i in range(len(arr)):
        val |= (arr[i] << (i * 3))
    return val

def getCompressedMap(arr: List[int]) -> dict[int,int]:
    res = {}
    temp = arr.copy()
    temp.sort()
    p = 0
    for i in range(len(temp)):
        if temp[i] in res:
            continue
        res[temp[i]] = p
        p += 1
    return res

'''
Here both nums1 and num2 have been compressed.
'''
def bfs(nums1: List[int], nums2: List[int]) -> int:
    hash_final = hash(nums2)
    dists = {}
    q = Deque[tuple[int, List[int]]]()
    q.append((0, nums1))

    while len(q) > 0:
        d, arr = q.popleft()
        hash_val = hash(arr)
        
        if hash_val in dists:
            continue
        dists[hash_val] = d

        if hash_val == hash_final:
            return d

        for start in range(0, len(arr)):
            for end in range(start + 1, len(arr) + 1):
                take_out = arr[start:end]
                remain = arr[:start] + arr[end:]

                for i in range(0, len(remain) + 1):
                    next = remain[:i] + take_out + remain[i:]
                    q.append((d + 1, next))

    return -1 # should not reach here

class Solution:
    def minSplitMerge(self, nums1: List[int], nums2: List[int]) -> int:
        compressedMap = getCompressedMap(nums1)
        arr1 = list(map(lambda x: compressedMap[x], nums1))
        arr2 = list(map(lambda x: compressedMap[x], nums2))
        #print(arr1, arr2)

        ans = bfs(arr1, arr2)
        return ans
    
sol = Solution()
nums1 = [1,1,2,3,4,5]
nums2 = [5,4,3,2,1,1]
print(sol.minSplitMerge(nums1, nums2))