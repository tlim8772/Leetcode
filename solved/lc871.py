from sortedcontainers import SortedList
from typing import List

'''
a greedy solution is needed. key is that if we can reach station i, i + 1, i + 2 ... j
we always take the largest fuel amount first because we have infinite storage tank.
let [ptr, n) be station whose fuel is not in the priority queue yet.
if with current fuel, we cannot reach stations[ptr][0], then pop from pq, until we can. (if cannot we break)
then add the fuel of stations we can reach.
do this until ptr == len(stations).

then we pop from max pq until we can reach target

'''

class Solution:
    def minRefuelStops(self, target: int, startFuel: int, stations: List[List[int]]) -> int:
        pq: SortedList[int] = SortedList()
        taken = 0
        total_fuel = startFuel
        ptr = 0
        
        while total_fuel < target:
            if ptr == len(stations):
                break

            # we take as little stations as needed until we can cross to the next segment
            while ptr < len(stations) and len(pq) > 0 and total_fuel < stations[ptr][0]:
                total_fuel += pq.pop()
                taken += 1

            # after taking all stations still cannot reach next segment, then impossible
            if ptr < len(stations) and total_fuel < stations[ptr][0]:
                break
            
            # add the stations' petrol in the new segment
            while ptr < len(stations) and total_fuel >= stations[ptr][0]:
                pq.add(stations[ptr][1])
                ptr += 1

        while len(pq) > 0 and total_fuel < target:
            total_fuel += pq.pop()
            taken += 1

        return -1 if total_fuel < target else taken

            
    

sol = Solution()
target = 100
startFuel = 10
stations = [[10,60],[20,30],[30,30],[60,40]]
print(sol.minRefuelStops(target, startFuel, stations))
                