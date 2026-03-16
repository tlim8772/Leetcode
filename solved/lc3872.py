
'''
just process the difference between 2 consecutive elements.
tedious problem with requires careful edge case handling.
'''

import itertools

# out[i] = nums[i] - nums[i + 1]
def get_consec_diff(nums: list[int]) -> list[int]:
    out = []
    for i in range(len(nums) - 1):
        out.append(nums[i] - nums[i + 1])
    return out

# for index i, get cnt, where nums[i - c + 1, i] have the same value
def get_left_cnt(nums: list[int]) -> list[int]:
    out = [1]
    for i in range(1, len(nums)):
        out.append(out[i - 1] + 1 if nums[i] == nums[i - 1] else 1)
    return out

def get_right_cnt(nums: list[int]) -> list[int]:
    out = [1 for _ in range(len(nums))]
    for i in range(len(nums) - 2, -1, -1):
        out[i] = out[i + 1] + 1 if nums[i] == nums[i + 1] else 1
    return out

def longestArithmetic(nums: list[int]) -> int:
    if 1 <= len(nums) <= 2:
        return len(nums)
    
    diffs = get_consec_diff(nums)
    left_cnts = get_left_cnt(diffs)
    right_cnts = get_right_cnt(diffs)

    best = max(left_cnts + right_cnts) + 1

    for i in range(len(nums)):
        if i == 0:
            best = max(best, 1 + right_cnts[1] + 1)
        elif i == len(nums) - 1:
            best = max(best, 1 + left_cnts[-2] + 1)

        else:
            # change to fit right
            if i != len(nums) - 2:
                right_diff = diffs[i + 1]
                new_elem = nums[i + 1] + right_diff
                left_diff = nums[i - 1] - new_elem
                
                new_len = 1 + right_cnts[i + 1]
                if left_diff == right_diff:
                    new_len += 1
                    
                    if i > 1 and left_diff == diffs[i - 2]:
                        new_len += left_cnts[i - 2]

                best = max(best, new_len + 1)

            if i != 1:
                left_diff = diffs[i - 2]
                new_elem = nums[i - 1] - left_diff
                right_diff = new_elem - nums[i + 1]

                new_len = 1 + left_cnts[i - 2]
                if right_diff == left_diff:
                    new_len += 1

                    if i < len(nums) - 2 and right_diff == diffs[i + 1]:
                        new_len += right_cnts[i + 1]
                
                best = max(best, new_len + 1)


    return best

class Solution:
    def longestArithmetic(self, nums: list[int]) -> int:
        return longestArithmetic(nums)





lst = [1, 2, 6, 7]
print(longestArithmetic(lst))
