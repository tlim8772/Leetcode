
# go from right to left.
# robot[i] will merge with robot[i - 1] if robot[i - 1] is faster
# or their initial position difference is <= k.

# need to handle t = 0 seperately.
# so first pass we merge consecutive distances are <= k.
# 2nd pass we merge robots with slower speeds.
# basically we want number of subarray, where each subarray is strictly decreasing.
# eg [4, 2, 6] -> [4, 2], [6]
# [10, 8, 9, 12] -> [10, 8], [9], [12]
 

class Solution:
    def countGroups(self, position: list[int], speed: list[int], distance: int) -> int:
        s1: list[tuple[int,int]] = []
        for p, s in zip(position, speed):
            if len(s1) == 0:
                s1.append((p, s))
            else:
                last = s1[-1]
                if p - last[0] <= distance:
                    s1.pop()
                s1.append((p, s))

        s2 = []
        for _, s in s1:
            while len(s2) > 0 and s2[-1] > s:
                s2.pop()
            s2.append(s)

        return len(s2)

sol = Solution()
position = [1,5,9]
speed = [3,2,2]
distance = 2

ans = sol.countGroups(position, speed, distance)
print(ans)


