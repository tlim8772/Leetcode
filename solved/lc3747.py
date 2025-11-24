'''
if num has lesser digits than n, ans is simply 9^(# digits).
if hame same # of digits, do digit dp.
'''

class Solution:

    def helper(self, i: int, num: str):
        if i == len(num):
            return 1
        
        digit = num[i]
        if digit == '0':
            return 0
        elif digit == '1':
            return self.helper(i + 1, num)
        else:
            not_same = (ord(digit) - ord('1')) * pow(9, len(num) - i - 1)
            same = self.helper(i + 1, num)
            return same + not_same
    
    def countDistinct(self, n: int) -> int:
        num = str(n)
        ans = 0

        for i in range(1, len(num)):
            ans += pow(9, i)

        ans += self.helper(0, num)

        return ans
    
sol = Solution()
print(sol.countDistinct(10))