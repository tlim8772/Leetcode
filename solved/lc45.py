from collections import deque

# greedy solution required for O(n).
# for each element, store the rightmost index reachable, basically it is i + arr[i].
# start from 0, always jump to the end if possible, else jump to the element with the rightmost reachable index.
# need to use monotonic queue to get max of a 2 pointer window.

# suppose we do not jump to the element with the rightmost reachable index at index j.
# case 1: k > j
# then we can jump to index j, and whatever index we go to from k, we can do the same with j.
# case 2: k < j.
# the next index after k, k' has to be > j.
# but then we can just go from j to k'.

# algo is.
# suppose we are at index i
# monotonic queue stores max for window i + 1 to i + arr[i]
# jump to j, pop elements from i + 1 to to its limit, then add the new reacable elements from j.
# this is because if we jump to an index from j to k, k <= limit.
# then reachable[k] must be greater than reachable[j]. (draw out to visualize)
# then we would have jump to k instead of j.

class monotonic_queue[T]:
    def __init__(self):
        self.q = deque[tuple[int, T]]()

    def get_max(self) -> tuple[int, T]:
        return self.q[0] if len(self.q) > 0 else None

    def pop(self, idx: int):
        if len(self.q) > 0 and self.q[0][0] == idx:
            self.q.popleft()

    def push(self, idx: int, val: T):
        while len(self.q) > 0 and self.q[-1][1] <= val:
            self.q.pop()
        self.q.append((idx, val))

class Solution:
    def jump(self, nums: list[int]) -> int:
        arr = []
        for i, v in enumerate(nums):
            arr.append(min(len(nums) - 1, i + v))

        mono_q = monotonic_queue[int]()

        # init the monotonic queue.
        curr_idx = 0
        curr_cnt = 0
        start = 1
        limit = arr[0]

        for i in range(1, limit + 1):
            mono_q.push(i, arr[i])

       
        while True:
            if curr_idx == len(nums) - 1:
                return curr_cnt

            pair = mono_q.get_max()
            if pair == None:
                return -1

            next_idx = pair[0]
            new_limit = pair[1]
            curr_cnt += 1

            for i in range(start, limit + 1):
                mono_q.pop(i)

            for i in range(limit + 1, new_limit + 1):
                mono_q.push(i, arr[i])

            curr_idx = next_idx
            start = limit + 1
            limit = new_limit

sol = Solution()
nums = [10] * 1000000
ans = sol.jump(nums)
print(ans)

        
