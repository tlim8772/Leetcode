package leetcode;
//import java.util.*;


    

public class lc1531_v2 {
    
    
    Integer[][] dp;

    public int helper(int index, int k, String s) {
        if (index == s.length()) {
            return 0;
        }  else if (dp[index][k] != null) {
            return dp[index][k];
        } else {
            int delete = (k == 0) ? 9999 : helper(index + 1, k - 1, s);
            int currChar = s.charAt(index) - 'a';
            int min = 9999;
            int count = 0;
            int left = k;
            
            // we may have a3a2, but it does not matter, as if a3a2 is considered, a5 is also considered, and confirm length(a5...) <= length(a3a2...)
            for (int i = index; i < s.length(); i ++) {
                if (s.charAt(i) - 'a' == currChar) {
                    count += 1;
                    int len = (count == 1) ? 1 : 1 + String.valueOf(count).length();
                    int ans = len + helper(i + 1, left, s);
                    min = Math.min(min, ans);
                } else {
                    left -= 1;
                    if (left < 0) {
                        break;
                    }
                }
            }
            int res = Math.min(min, delete);
            dp[index][k] = res;
            return res;
        }
    }

    public int getLengthOfOptimalCompression(String s, int k) {
        dp = new Integer[s.length()][k + 1];
        return helper(0, k, s);
    }

    public static void main(String[] args) {
        lc1531_v2 sol = new lc1531_v2();
        String s = "aabbaa";
        System.out.println(sol.getLengthOfOptimalCompression(s, 1));
    }
 
}