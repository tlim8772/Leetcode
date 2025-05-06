from collections import defaultdict
from typing import List, DefaultDict

'''
key here is to group names by their 1st char, not their suffix
so example we have ('a', bunch of suffixes that start with 'a') and ('b', bunch of suffixes that start with 'b')
then the number of pairs is (setA - setB) * (setB - setA) * 2 here we are taking set difference so setA - setB is all elements
in setA and not in setB

since only have 26 char, just check them all
'''

class Solution:
    def distinctNames(self, ideas: List[str]) -> int:
        store: DefaultDict[str, set[str]] = defaultdict(set)
        for s in ideas:
            lst = store[s[0]]
            lst.add(s[1:])

        sum = 0
        for i in range(0, 26):
            for j in range(i + 1, 26):
                setI: set[str] = store[chr(i + ord('a'))]
                setJ: set[str] = store[chr(j + ord('a'))]
                
                diffI = len(setI.difference(setJ))
                diffJ = len(setJ.difference(setI))
                sum += diffI * diffJ * 2

        return sum
    

sol = Solution()
ideas = ["coffee","donuts","time","toffee"]
print(sol.distinctNames(ideas))