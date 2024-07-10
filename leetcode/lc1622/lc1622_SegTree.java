import java.util.*;

class Solution {
    long[] tree;
    // multAccu[p] stores multipler that ends exactly at the [s, e] that corresponds to p, but we
    // do not multiply tree[p] by multAccu[p] when finding range sum beacuse tree[p] already accounts for the multAccu[p]
    long[] multAccu;
    int size;
    long MOD = 1000000007;

    public Solution(int n) {
        tree = new long[4 * n];
        multAccu = new long[4 * n];
        Arrays.fill(multAccu, 1L);
        size = n;
    }

    long[] modInverse(long[] arr) {
        if (arr[1] == 0) {
            return new long[] {arr[0], arr[1], 1, 0};
        } 
        long[] res = modInverse(new long[] {arr[1], arr[0] % arr[1], 0, 0});
        arr[2] = res[3];
        arr[3] = res[2] - res[3] * (arr[0] / arr[1]);
        return arr;
    }

    // we want to find x such that ax = y modm
    long modReverse(long a, long y) {
        long[] ans = modInverse(new long[] {a, MOD, 0, 0});
        long x = (ans[2] % MOD + MOD) % MOD;
        return mult(x, y);
    }

    long add(long a, long b) {
        return (a + b) % MOD;
    }

    long mult(long a, long b) {
        return ((a % MOD) * (b % MOD)) % MOD;
    }


    // we do not include the multipler from previous multRange, this is the requirement from the question

    long addElem(int p, int s, int e, int i, long val, long mu) {
        int m = (s + e) / 2;
        if (s == e) {
            long res = add(tree[p], val);
            tree[p] = modReverse(mu, res);  // mu * tree[p] = res mod MOD
            return tree[p];
        } else if (i <= m) {
            long mu1 = mult(mu, multAccu[p]);
            long l = addElem(2 * p + 1, s, m, i, val, mu1);
            long r = mult(tree[2 * p + 2], mu1);
            long res = add(l, r);
            tree[p] = modReverse(mu, res);
            return tree[p];
        } else {
            long mu1 = mult(mu, multAccu[p]);
            long l = mult(tree[2 * p + 1], mu1);
            long r = addElem(2 * p + 2, m + 1, e, i, val, mu1);
            long res = add(l, r);
            tree[p] = modReverse(mu, res);
            return tree[p];
        }
       
    }

    // mult all sum from event 0 to event i
    /*long multAll(int p, int s, int e, int i, long val, long mu) {
        int m = (s + e) / 2;
        if (s == e) {
            multAccu[p] = mult(multAccu[p], mu);
            long res = mult(mult(tree[p], mu), val);
            tree[p] = modReverse(mu, res);
            return tree[p];
        }  else if (i == e) {
            multAccu[p] = mult(multAccu[p], mu);
            long res = mult(mult(tree[p], mu), val);
            tree[p] = modReverse(mu, res);
            return tree[p];      
        } else if (i <= m) {
            long mu1 = mult(mu, multAccu[p]);
            long l = multAll(2 * p + 1, s, m, i, val, mu1);
            long r = mult(tree[2 * p + 2], mu1);
            long res = add(l, r);
            tree[p] = modReverse(mu, res);
            return tree[p];
        } else {
            long mu1 = mult(mu, multAccu[p]);
            long l = multAll(2 * p + 1, s, m, m, val, mu1);
            long r = multAll(2 * p + 2, m + 1, e, i, val, mu1);
            long res = add(l, r);
            tree[p] = modReverse(mu, res);
            return tree[p];
        }
    }*/

    // for every elem in [l, r] multiply by val
    long multRange(int p, int s, int e, int l, int r, long val, long mu) {
        int m = (s + e) / 2;
        if (s == e || (s == l && e == r)) {
            long res = mult(mult(tree[p], mu), val);
            tree[p] = modReverse(mu, res);
            multAccu[p] = mult(multAccu[p], val);
            return tree[p];
        } else if (r <= m) {
            long mu1 = mult(mu, multAccu[p]);
            long lres = multRange(2 * p + 1, s, m, l, r, val, mu1);
            long rres = mult(tree[2 * p + 2], mu1);
            long res = add(lres, rres);
            tree[p] = modReverse(mu, res);
            return tree[p];
        } else if (l > m) {
            long mu1 = mult(mu, multAccu[p]);
            long lres = mult(tree[2 * p + 1], mu1);
            long rres = multRange(2 * p + 2, m + 1, e, l, r, val, mu1);
            long res = add(lres, rres);
            tree[p] = modReverse(mu, res);
            return tree[p];
        } else {
            long mu1 = mult(mu, multAccu[p]);
            long lres = multRange(2 * p + 1, s, m, l, m, val, mu1);
            long rres = multRange(2 * p + 2, m + 1, e, m + 1, r, val, mu1);
            long res = add(lres, rres);
            tree[p] = modReverse(mu, res);
            return tree[p];
        }
    }

    // gets the sum of all sum and mult from event i to event END
    long getSum(int p, int s, int e, int i, long mu) {
        int m = (s + e) / 2;
        if (s == e) {
            return mult(tree[p], mu);
        } else if (s == i) {
            return mult(tree[p], mu);
        } else if (i <= m) {
            long mu1 = mult(mu, multAccu[p]);
            long l = getSum(2 * p + 1, s, m, i, mu1);
            long r = mult(tree[2 * p + 2], mu1);
            return add(l, r);
        } else {
            long mu1 = mult(mu, multAccu[p]);
            long r = getSum(2 * p + 2, m + 1, e, i, mu1);
            return r;
        }
    }

    long getSum(int p, int s, int e, int l, int r, long mu) {
         int m = (s + e) / 2;
        if (s == e) {
            return mult(tree[p], mu);
        } else if (s == l && e == r) {
            return mult(tree[p], mu);
        } else if (r <= m) {
            return getSum(2 * p + 1, s, m, l, r, mult(mu, multAccu[p]));
        } else if (l > m) {
            return getSum(2 * p + 2, m + 1, e, l, r, mult(mu, multAccu[p]));
        } else {
            long lres = getSum(2 * p + 1, s, m, l, m, mult(mu, multAccu[p]));
            long rres = getSum(2 * p + 2, m + 1, e, m, r, mult(mu, multAccu[p]));
            return add(lres, rres);
        }
    }

    
    // get mult of all mults from event i to event END
    long getMult(int p, int s, int e, int i, long mu) {
        int m = (s + e) / 2;
        if (s == e) {
            return mult(mu, multAccu[p]); // we need to multiply by the val in multAccu leaf, this is because the sum may be updated correctly with mu, 
                                          // but we need the multAccu at the leaf for the correct multiplier, as we are still multiplying tree[p] the leaf, with val
        } else if (i <= m) {
            return getMult(2 * p + 1, s, m, i, mult(mu, multAccu[p]));
        } else {
            return getMult(2 * p + 2, m + 1, e, i, mult(mu, multAccu[p]));
        }
    }

    public void testSum(int limit, int start) {
        Solution st = new Solution(limit);
        for (int i = 0; i < limit; i ++) {
            st.addElem(0, 0, st.size - 1, i, 100000000, 1);
        }
        long sum = 0;
        for (int i = start; i < limit; i ++) {
            sum = add(sum, 100000000);
        }
        assert st.getSum(0, 0, st.size - 1, start, st.size - 1, 1) == sum;
    }


    public static void main(String[] args) {
        Solution st = new Solution(25);
        //st.testSum(100000, 6771);
        //st.addElem(0, 0, st.size - 1, 0, 5, 1);
        //st.addElem(0, 0, st.size - 1, 1, 8, 1);
        
        st.multRange(0, 0, st.size - 1, 0, 2, 6, 1);
       
        
        //System.out.println(st.getSum(0, 0, st.size - 1, 3, 3, 1));
        System.out.println(st.getMult(0, 0, st.size - 1, 2, 1));
        System.out.println(Arrays.toString(st.multAccu));
    }
}
