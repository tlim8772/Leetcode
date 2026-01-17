'''
backtracking and pruning.
start from the least significant column, if char is not assigned a digit, assign 1.
when we reach the result, check if assignment (so far) is valid.

lots of stupid checks due to no leading zeros.
single digit number eg ("A") can be 0.
the most significant digit of result cannot be 0 too, unless result is a single digit number.
'''

class Store:
    def __init__(self):
        self.charToDigit: dict[str, int] = {}
        self.digToChar: dict[int, str] = {}

    def is_digit_used(self, dig: int) -> bool:
        return dig in self.digToChar
    
    def is_char_used(self, chr: str) -> bool:
        return chr in self.charToDigit
    
    def set_char_to_digit(self, chr: str, dig: int):
        self.charToDigit[chr] = dig
        self.digToChar[dig] = chr

    def get_digit_from_chr(self, chr: str) -> int | None:
        return self.charToDigit.get(chr)
    
    def remove_mapping(self, chr: str, dig: int):
        del self.charToDigit[chr]
        del self.digToChar[dig]

    def print_mapping(self):
        mapping = list(self.charToDigit.items())
        mapping.sort(key=lambda pair: pair[0])
        print(mapping)


def can_be_zero(col: int, word: str) -> bool:
    return len(word) == 1 or col < len(word) - 1

def helper(col: int, row: int, sum: int, words: list[str], res: str, store: Store) -> bool:
    if col == len(res):
        if sum == 0:
            store.print_mapping()
            return True
        
        return False
    
    if row == len(words):
        chr = res[col]
        dig, carry = sum % 10, sum // 10
        can_zero = can_be_zero(col, res)

        if store.is_char_used(chr):
            if dig != store.get_digit_from_chr(chr):
                return False
            
            if not can_zero and store.get_digit_from_chr(chr) == 0:
                return False
            
            return helper(col + 1, 0, carry, words, res, store)
        
        else:
            if store.is_digit_used(dig):
                return False
            
            if not can_zero and dig == 0:
                return False
            
            store.set_char_to_digit(chr, dig)
            ans = helper(col + 1, 0, carry, words, res, store)
            store.remove_mapping(chr, dig)
            return ans
        
    if col >= len(words[row]):
        return helper(col, row + 1, sum, words, res, store)
    
    chr = words[row][col]
    can_zero = can_be_zero(col, words[row])

    if store.is_char_used(chr):
        if not can_zero and store.get_digit_from_chr(chr) == 0:
            return False
        
        return helper(col, row + 1, sum + store.get_digit_from_chr(chr), words, res, store)
    

    for dig in range(1 - can_zero, 10):
        if store.is_digit_used(dig):
            continue

        store.set_char_to_digit(chr, dig)
        ans = helper(col, row + 1, sum + dig, words, res, store)
        store.remove_mapping(chr, dig)

        if ans:
            return True
        
    return False





class Solution:
    def isSolvable(self, words: list[str], result: str) -> bool:
        if max(map(lambda s: len(s), words)) > len(result):
            return False
        
        words_reversed = list(map(lambda s: s[::-1], words))
        result_reversed = result[::-1]
        store = Store()
        
        return helper(0, 0, 0, words_reversed, result_reversed, store)
    

sol = Solution()
words = ["A"]
result = "AA"

print(sol.isSolvable(words, result))

