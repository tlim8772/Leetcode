import java.util.*;

// greedy always take the pair with the largest left
// suppose no optimal solution contains pair with largest left, remove the last pair in any optimal solution
// and replace with pair with the largest lefts

class Solution {
    public int findLongestChain(int[][] pairs) {
        PriorityQueue<int[]> pq = new PriorityQueue<>((x, y) -> y[0] - x[0]);
        int end = 999999999;
        int sum = 0;
        while (!pq.isEmpty()) {
            int[] pair = pq.poll();
            if (pair[1] < end) {
                sum ++;
                end = pair[0];
            }
        }
        return sum;
    }
}