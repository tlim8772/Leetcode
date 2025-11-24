package leetcode;

import java.util.*;

// 1st we compress the string to remove consecutive same characters
// notice that consecutive same characters do not matter

// dp[filler][s][e] means best result for substring position [s, e] and all positions filled with filler
// to transition, consider the 1st character of substring [s, e]
// [si, ei, ci] means color range [si, ei] char ci
// suppose optimal coloring is [s, e1, c1], [s, e2, c2] ... [s, e5, c5], [s1, e6, c6]... 
// notice that only that last range that covers s matters
// meaning we only have to consider 1 operation to color the 1st characters
// we then can color s, only or extend to cover other same characters as str[s] that appear in [s, e], so we can save some operations
// suppoose we color until e1, this means we (at this stage) think that e1 is the furtherst elem s.t no subseqeuent coloring will recolor e1 
// (if so, then there is no point in coloring unitl e1)
// i.e e1 is the last slot to be saved
// i,e we can do 0 3 6(not used) 9, so e1 is 9   (this means index 0, 3, 6, 9 are all of the same character)
// then we simply recurse dp(cur, s + 1, e1 - 1) + dp(filler, e1 + 1, e)

class Solution {
    int[][][] dp;
    ArrayList<ArrayList<Integer>> locations;

    String compressString(String str) {
        StringBuilder sb = new StringBuilder();
        char cur = str.charAt(0);
        for (int i = 1; i < str.length(); i ++) {
            if (str.charAt(i) != cur) {
                sb.append(cur);
                cur = str.charAt(i);
            }
        }
        sb.append(cur);
        return sb.toString();
    }

    void processLocations(String str) {
        locations = new ArrayList<>();
        for (int i = 0; i < 26; i ++) {
            locations.add(new ArrayList<>());
        }
        for (int i = 0; i < str.length(); i ++) {
            locations.get(str.charAt(i) - 'a').add(i);
        }
    }

    // for this, the key always exist. We just want the index, i.e we are at char 'a' at index 11, we want to immediately
    // iterate to subsequent 'a'
    int getIndex(int key, char c) {
        ArrayList<Integer> lst = locations.get(c - 'a');
        int s = 0;
        int e = lst.size();
        while (s < e) {
            int m = (s + e) / 2;
            if (lst.get(m) < key) {
                s = m + 1;
            } else {
                e = m;
            }
        }
        return s;
    }

    void fill(int[][][] arr) {
        for (int i = 0; i < arr.length; i ++) {
            for (int j = 0; j < arr[0].length; j ++) {
                for (int k = 0; k < arr[0][0].length; k ++) {
                    arr[i][j][k] = -1;
                }
            }
        }
    }

    int helper(int filler, int s, int e, String str) {
        if (s > e) {
            return 0;
        } else if (dp[filler][s][e] != -1) {
            return dp[filler][s][e];
        } else {
            char cur = str.charAt(s);
            int best = 100000;
            int index = getIndex(s, cur);
            ArrayList<Integer> lst = locations.get(cur - 'a');
            for (int i = index; i < lst.size(); i ++) {
                int s1 = s + 1;
                int e1 = lst.get(i) - 1;
                int s2 = lst.get(i) + 1;
                int e2 = e;
                int ans = (filler == cur - 'a') ? 0 : 1;
                ans += helper(cur - 'a', s1, e1, str) + helper(filler, s2, e2, str);
                best = Math.min(best, ans);
            }
            dp[filler][s][e] = best;
            return best;
        }
    }

    public int strangePrinter(String s) {
        String str = compressString(s);
        processLocations(str);
        dp = new int[27][str.length()][str.length()];
        fill(dp);
        int ans = helper(26, 0, str.length() - 1, str);
        return ans;

    }




    public static void main(String[] args) {
        Solution sol = new Solution();
        String s = "abcba";
        System.out.println(sol.strangePrinter(s));
        
    }
}