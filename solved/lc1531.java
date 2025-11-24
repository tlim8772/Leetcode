package leetcode;
//import java.util.*;

class Solution {
// state (Char, count, index, k)
// i.e shortest string compressed, starting from index, with k deletions left, but confirmed have at lest count Char in front

    Integer[][][][] dp;

    public int helper(int Char, int count, int index, int k, String s) {
        if (index == s.length()) {
            return (count == 0) ? 0 
                                : (count == 1)
                                ? 1
                                : 1 + String.valueOf(count).length();
        } else if (k == 0) {
            int curr = s.charAt(index) - 'a';
            if (curr == Char) {
                int ans = helper(Char, count + 1, index + 1, k, s);
                dp[Char][count][index][k] = ans;
                return ans;
            } else {
                int frontLen = (count == 0) ? 0
                                            : (count == 1)
                                            ? 1
                                            : 1 + String.valueOf(count).length();
                int noDelete = frontLen + helper(curr, 1, index + 1, k, s);
                dp[Char][count][index][k] = noDelete;
                return noDelete;
            }
        } 
        
        else if (dp[Char][count][index][k] != null) {
            return dp[Char][count][index][k];
        } else {
            int curr = s.charAt(index) - 'a';
            if (curr == Char) {
                int noDelete = helper(Char, count + 1, index + 1, k, s);
                int delete = helper(Char, count, index + 1, k - 1, s);
                int ans = Math.min(noDelete, delete);
                dp[Char][count][index][k] = ans;
                return ans;
            } else {
                int frontLen = (count == 0) ? 0
                                            : (count == 1)
                                            ? 1
                                            : 1 + String.valueOf(count).length();
                int noDelete = frontLen + helper(curr, 1, index + 1, k, s);
                int delete = helper(Char, count, index + 1, k - 1, s);
                int ans = Math.min(noDelete, delete);
                dp[Char][count][index][k] = ans;
                return ans;
            }
        }
    }

     public int getLengthOfOptimalCompression(String s, int k) {
        dp = new Integer[26][s.length() + 1][s.length()][k + 1];
        return helper(0, 0, 0, k, s);
    }

    /*public static void main(String[] args) {
        Solution sol = new Solution();
        String s = "jubwijbiqebeiwuviefeidhwedeucbuhbwcuediuediwuiebcwhbeihbewihdbewhdbewhcbdehcbwhdbchbeixduewbcduhbdewdiewnwcwedhbvddfwdfwfvvfdfwdf";
        //System.out.println(s.length());
        long start = System.nanoTime();
        sol.getLengthOfOptimalCompression(s, 100);
        long end = System.nanoTime();
        System.out.println((end - start) / 1000000.0);
        
        //System.out.println(sol.getLengthOfOptimalCompression(s, 112));
    }*/

}