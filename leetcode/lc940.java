import java.util.*;

// basically if we have a5 b4 c3 b4 a2 c1
// when we count distinct subseqeunce at index 3, b3, we only take 5 'b' to 8 'b', because of the b4 earlier
// if we take, let say 3 'b' from the earlier b4, we can already achive the same subsequence

// so store for a5 b4 c3 b4 a2 c1 = [[0, 1, 5], [1, 1, 4], [2, 1, 3], [1, 5, 8], [0, 6, 7], [2, 4, 4]]
// notice for a2 we include the previous a5
// dp[i] = # of distinct subsequeces using at least 1 + num of prev same characters  from store[i] onwards
public class lc940 {
    long MOD = 1000000007;
    ArrayList<ArrayList<Integer>> store;
    long[] dp;

    void process(String s) {
        int[] prefixSum = new int[26];
        store = new ArrayList<>();
        char c = s.charAt(0);
        int count = 0;
        for (int i = 0; i < s.length(); i ++) {
            if (s.charAt(i) != c) {
                ArrayList<Integer> temp = new ArrayList<>();
                Collections.addAll(temp, c - 'a', prefixSum[c - 'a'] + 1, prefixSum[c - 'a'] + count);
                store.add(temp);
                prefixSum[c - 'a'] += count;
                c = s.charAt(i);
                count = 1;
            } else {
                count += 1;
            }
        }
        ArrayList<Integer> temp = new ArrayList<>();
        Collections.addAll(temp, c - 'a', prefixSum[c - 'a'] + 1, prefixSum[c - 'a'] + count);
        store.add(temp);
    }

    long add(long a, long b) {
        return (a + b) % MOD;
    }

    long mult(long a, long b) {
        a = a % MOD;
        b = b % MOD;
        long res = (a * b) % MOD;
        return res;
    }

    long helper(int i) {
        if (i >= store.size()) {
            return 1;
        } else if (dp[i] != -1) {
            return dp[i];
        } else {
            int c = store.get(i).get(0);
            int count = store.get(i).get(2) - store.get(i).get(1) + 1;
            long sum = 0;
            for (int x = i; x <= store.size(); x ++) {
                if (x == store.size()) {
                    sum = add(sum, 1);
                } else if (store.get(x).get(0) != c) {
                    sum = add(sum, helper(x));
                }
            }
            long res = mult(sum, count);
            dp[i] = res;
            return res;
        }
    }

    public int distinctSubseqII(String s) {
        process(s);
        dp = new long[store.size()];
        Arrays.fill(dp, -1);
        long ans = 0;
        for (int i = 0; i < store.size(); i ++) {
            ans = add(ans, helper(i));
        }
        return (int) ans;
    }




    public static void main(String[] args) {
        lc940 sol = new lc940();
        //String s = "aaaaabbbbcccbbbbac";
        long res = sol.distinctSubseqII("aabbaa");
        System.out.println(res);
    }
    
}