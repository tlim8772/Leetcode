import java.util.*;

// bottom up dp, and exploit monoticity
// let dp[i][k] be the longest subsequence using the elem at index i, with at most k changes in elems selected
// now dp[i][k] >= dp[i][k - 1] >= dp[i][k - 2] ... >= dp[i][0]
// let next be the first index to the right s.t nums[i] = nums[next]
// dp[i][k] = max(dp[next][k], max(dp[j][k - 1])) where j > i and nums[j] != nums[i]
// we only need to consider the first index to the right s.t nums[i] = nums[next], because if we choose the 2nd next index, can simply add 1, since elems are the same

// now actually we do not have to split into changes to prevent considering dp[j][k - 1] where nums[j] = nums[i]
// suppose dp[j][k - 1] where nums[j] = nums[i] is the max, overshadowing the correct dp[j][k - 1] where nums[j] != nums[i]
// then by monocity, dp[next][k] >= dp[next][k - 1] >= dp[j][k - 1], hence correct next choice dp[next][k] will win
// so dp[i][k] = max(dp[next][k], max(dp[j][k - 1]) where j > i)

// we store the suffix max from i + 1 to len(arr) - 1 to compute max in O(1)
// TC is O(kn)


public class lc3177 {
    int[][] maxdp;
    int[][] dp;
    int limitK;

    void compress(int[] nums) {
        int cnt = 0;
        HashMap<Integer, Integer> seen = new HashMap<>();
        for (int i = 0; i < nums.length; i ++) {
            if (seen.get(nums[i]) == null) {
                seen.put(nums[i], cnt);
                cnt ++;
            }
            nums[i] = seen.get(nums[i]);  
        }
    }

    int[] firstNext(int[] nums) {
        int[] out = new int[nums.length];
        int[] map = new int[nums.length];
        Arrays.fill(map, -1);
        for (int i = nums.length - 1; i >= 0; i --) {
            out[i] = map[nums[i]];
            map[nums[i]] = i;
        }
        return out;
    }

    void helper(int[] compressNums, int[] next) {
        int len = compressNums.length;
        
        // when i is the last index
        for (int k = 0; k <= limitK; k ++) {
            dp[len - 1][k] = 1;
            maxdp[len - 1][k] = 1;
        }


        for (int i = len - 2; i >= 0; i --) {
            int[] maxCurr = new int[limitK + 1];
            dp[i][0] = (next[i] == -1) ? 1 : 1 + dp[next[i]][0];
            maxCurr[0] = dp[i][0];
            for (int k = 1; k <= limitK; k ++) {
                int nextNode = next[i];
                int takeSame = (nextNode == -1) ? 0 : dp[nextNode][k];
                int takeDiff = maxdp[i + 1][k - 1];
                dp[i][k] = 1 + Math.max(takeSame, takeDiff);
                maxCurr[k] = dp[i][k];
            }
            for (int k = 0; k < limitK; k ++) {
                maxdp[i][k] = Math.max(maxCurr[k], maxdp[i + 1][k]);
            }
        }
    }

    public int maximumLength(int[] nums, int k) {
        limitK = k;
        dp = new int[nums.length][k + 1];
        maxdp = new int[nums.length][k + 1];
        compress(nums);
        int[] nextNodes = firstNext(nums);
        helper(nums, nextNodes);
        int max = -1;
        for (int i = 0; i < nums.length; i ++) {
            max = Math.max(max, dp[i][k]);
        }
        return max;
    }

    public static void main(String[] args) {
        lc3177 sol = new lc3177();
        int[] nums = {1,2,3,4,5,1};
        int ans = sol.maximumLength(nums, 2);
        System.out.println(ans);
    }

}