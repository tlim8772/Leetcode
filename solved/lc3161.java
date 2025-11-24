package leetcode;

import java.util.*;

public class lc3161 {
    SegTree st;
    TreeSet<Integer> barriers;

    public void insertBarrier(int i) {
        int lB = barriers.floor(i);
        int rB = barriers.ceiling(i);
        if (i == lB || i == rB) {
            return;
        } else {
            int diff = rB - i;
            st.rangeAdd(0, 0, st.size - 1, lB, i - 1, -diff, 0);
        }
        barriers.add(i);
    }

    public void process() {
        barriers = new TreeSet<>();
        barriers.add(0); 
        barriers.add(50000);
        int[] arr = new int[50001];
        for (int i = 0; i < arr.length; i ++) {
            arr[i] = 50000 - i;
        }
        st = new SegTree(arr);
    }

   
    public List<Boolean> getResults(int[][] queries) {
        ArrayList<Boolean> res = new ArrayList<>();
        process();
        for (int[] q : queries) {
            if (q[0] == 1) {
                insertBarrier(q[1]);
                
            } else {
                if (q[1] < q[2]) {
                    res.add(false);
                } else {
                    int maxlen = st.rangeMax(0, 0, st.size - 1, 0, q[1] - q[2], 0);
                    res.add(maxlen >= q[2]);
                }
            }
        }
        return res;
    }

    public static void main(String[] args) {
        int[][] queries = {{1,7},{2,7,6},{1,2},{2,7,5},{2,7,6}};
        List<Boolean> ans = new lc3161().getResults(queries);
        System.out.println(Arrays.toString(ans.toArray()));
    }
}


class SegTree {
    int[] tree;
    int[] accu;
    int size;

    public SegTree(int[] arr) {
        int size = arr.length;
        this.size = size;
        tree = new int[4 * size];
        accu = new int[4 * size];
        buildTree(0, 0, size - 1, arr);
 
    }

    public int buildTree(int p, int s, int e, int[] arr) {
        int m = (s + e) / 2;
        if (s == e) {
            tree[p] = arr[s];
        } else {
            int l = buildTree(2 * p + 1, s, m, arr);
            int r = buildTree(2 * p + 2, m + 1, e, arr);
            tree[p] = Math.max(l, r);
        }
        return tree[p];
    }

    public int rangeAdd(int p, int s, int e, int l, int r, int val, int acc) {
        int m = (s + e) / 2;
        if (s == e || (s == l && e == r)) {
            int actual = tree[p] + acc + val;
            tree[p] = actual - acc;
            accu[p] += val;
            return actual;
        } else if (r <= m) {
            int lres = rangeAdd(2 * p + 1, s, m, l, r, val, acc + accu[p]);
            int rres = acc + accu[p] + tree[2 * p + 2];
            int actual = Math.max(lres, rres);
            tree[p] = actual - acc;
            return actual;
        } else if (l > m) {
            int lres = acc + accu[p] + tree[2 * p + 1];
            int rres = rangeAdd(2 * p + 2, m + 1, e, l, r, val, acc + accu[p]);
            int actual = Math.max(lres, rres);
            tree[p] = actual - acc;
            return actual;
        } else {
            int lres = rangeAdd(2 * p + 1, s, m, l, m, val, acc + accu[p]);
            int rres = rangeAdd(2 * p + 2, m + 1, e, m + 1, r, val, acc + accu[p]);
            int actual = Math.max(lres, rres);
            tree[p] = actual - acc;
            return actual;
        }
    }

    int rangeMax(int p, int s, int e, int l, int r, int acc) {
        int m = (s + e) / 2;
        if (s == e || (s == l && e == r)) {
            return tree[p] + acc;
        } else if (r <= m) {
            return rangeMax(2 * p + 1, s, m, l, r, acc + accu[p]);
        } else if (l > m) {
            return rangeMax(2 * p + 2, m + 1, e, l, r, acc + accu[p]);
        } else {
            int lmax = rangeMax(2 * p + 1, s, m, l, m, acc + accu[p]);
            int rmax = rangeMax(2 * p + 2, m + 1, e, m + 1, r, acc + accu[p]);
            return Math.max(lmax, rmax);
        }
    }
}