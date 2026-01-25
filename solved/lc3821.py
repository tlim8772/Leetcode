import math

'''
1st find # of zeros.
we use nCr to find # of numbers with k 1s and m 0s, and check if it is > curr_n.
if yes, we have to add another 0, else we stop.

then we iterate from left to right, the 1st (most significant) digit has to be 1.
for each i, we place 0, find # of numbers, if > curr_n, then we have to put 1, else must put 0.
'''

class Solution:
    def nthSmallest(self, n: int, k: int) -> int:
        # find how many 0s we have
        num_0 = 0
        while True:
            new_n = n - math.comb(k - 1 + num_0, num_0)
            if new_n <= 0:
                break
            num_0 += 1
            n = new_n

        
        # 1st digit (0 index) is 1. 
        # we check 2nd digit onwards, place 0 first, then count how 
        # many numbers, if > k, then must put 0, else must put 1
        arr = [0 for _ in range(k + num_0)]
        ones, zeros = k - 1, num_0
        arr[0] = 1
        
        for i in range(1, len(arr)):
            if zeros == 0 and ones > 0:
                arr[i] = 1
                continue
            elif ones == 0 and zeros > 0:
                break

            how_many = math.comb(ones + zeros - 1, ones)
            if how_many >= n:
                zeros -= 1
                arr[i] = 0
            else:
                ones -= 1
                arr[i] = 1
                n -= how_many

        
        s = ''.join(map(lambda x: str(x), arr))
        #print(s)
        return int(s, 2)
    
sol = Solution()
n, k = 4, 2
print(sol.nthSmallest(n, k))
print(math.comb(0, 0))