package leetcode;
import java.util.*;

// just a math question
// the palindrome sets come in 4, 2, 1
// 2 if the indices are in the middle row / column when num of row / columns are odd
// 1 if the indice in the center of a grid with odd num of rows and odd num of cols
// in palindromic matrix, num of 1 need to be multiple of 4, so set of 4, simply change whichever bit is lesser
// for set of 2, simply also change if the 2 bits are different
// consider the set of 2 where both indices are 1, if the numbe of such sets are odd, we need 1 more set of 2 with 2 '1' bits
// if even done already
// so basically, when changing the 0 1 sets, we can alwayschange the correct number of (1 1) and (0 0) so that number 
// of (1 1) sets is even in the end
// in any way, sum of changes is still number of 0 1 sets
// but if no (0 1) sets and sets of (1, 1) is odd, need to change 2 more bits
// set of 1, if it is 1 bit need to change

class Solution {
    int m;
    int n;
    int setOf4;
    int setOf2_00;
    int setOf2_01;
    int setOf2_11;
    boolean[][] visited;
    int[][] grid;
    int ans = 0;

    void process(ArrayList<int[]> indices) {
        if (indices.size() == 4) {
            setOf4 ++;
            int c0 = 0;
            int c1 = 0;
            for (int[] idx : indices) {
                if (grid[idx[0]][idx[1]] == 0) c0 ++;
                else c1 ++;
            }
            ans += Math.min(c0, c1);
        } else if (indices.size() == 1) {
            // only change if bit is 1
            ans += (grid[indices.get(0)[0]][indices.get(0)[1]]) == 0 ? 0 : 1;
        } else {
            int c0 = 0;
            int c1 = 0;
            for (int[] idx : indices) {
                if (grid[idx[0]][idx[1]] == 0) c0 ++;
                else c1 ++;
                ans += Math.min(c0, c1);
            }
            if (c0 == 2) setOf2_00 ++;
            else if (c1 == 2) setOf2_11 ++;
            else setOf2_01 ++;
        }
    }

    public int minFlips(int[][] grid) {
        this.grid = grid;
        int m = grid.length;
        int n = grid[0].length;
        setOf4 = 0;
        setOf2_00 = 0;
        setOf2_01 = 0;
        setOf2_11 = 0;
        ans = 0;
        visited = new boolean[m][n];
        for (int i = 0; i < m; i ++) {
            for (int j = 0; j < n; j ++) {
                visited[i][j] = false;
            }
        }

        for (int r = 0; r < m; r ++) {
            for (int c = 0; c < n; c ++) {
                if (visited[r][c]) continue;
                ArrayList<int[]> store = new ArrayList<>();
                
                if (!visited[r][c]) {
                    store.add(new int[] {r, c});
                    visited[r][c] = true;
                }
                if (!visited[m - 1 - r][c]) {
                    store.add(new int[] {m - 1 - r, c});
                    visited[m - 1 - r][c] = true;
                }
                if (!visited[r][n - 1 - c]) {
                    store.add(new int[] {r, n - 1 - c});
                    visited[r][n - 1 - c] = true;
                }
                if (!visited[m - 1 - r][n - 1 - c]) {
                    store.add(new int[] {m - 1 - r, n - 1 - c});
                    visited[m - 1 - r][n - 1 - c] = true;
                }
                process(store);

            }
        }

        //System.out.println(setOf4 + " " + setOf2_00 + " " + setOf2_01 + " " + setOf2_11);
        if (setOf2_11 % 2 == 1 && setOf2_01 == 0) ans += 2;
        

        return ans;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        int[][] grid = {{1,0,0},{0,1,0},{0,0,1}};
        System.out.println(sol.minFlips(grid));

    }
}
