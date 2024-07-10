import java.util.Arrays;

class Solution {
    public boolean[] isArraySpecial(int[] nums, int[][] queries) {
        SegTree st = new SegTree(nums);
        boolean[] out = new boolean[queries.length];
        for (int i = 0; i < queries.length; i ++) {
            int[] q = queries[i];
            out[i] = st.query(0, 0, st.size - 1, q[0], q[1]);
        }
        return out;
    }

    public static void main(String[] args) {
        int[] nums = {4,3,1,6};
        int[][] queries = {{0,2}, {2,3}};
        Solution sol = new Solution();
        System.out.println(Arrays.toString(sol.isArraySpecial(nums, queries)));
    }
}

class SegTree {
    boolean[] tree;
    int[] arr;
    int size;

    SegTree(int[] arr) {
        size = arr.length;
        this.arr = arr;
        tree = new boolean[4 * size];
        buildTree(0, 0, size - 1, arr);
    }

    void buildTree(int p, int s, int e, int[] arr) {
        if (s == e) {
            tree[p] = true;
        } else {
            int m = (s + e) / 2;
            buildTree(2 * p + 1, s, m, arr);
            buildTree(2 * p + 2, m + 1, e, arr);
            // 2 elems of diff parity <=> sum of the 2 elements is odd
            tree[p] = tree[2 * p + 1] && tree[2 * p + 2] && ((arr[m] + arr[m + 1]) % 2 == 1); 
        }
    }

    boolean query(int p, int s, int e, int l, int r) {
        int m = (s + e) / 2;
        if (s == e || (s == l && e == r)) {
            return tree[p];
        } else if (r <= m) {
            return query(2 * p + 1, s, m, l, r);
        } else if (l > m) {
            return query(2 * p + 2, m + 1, e, l, r);
        } else {
            boolean lres = query(2 * p + 1, s, m, l, m);
            boolean rres = query(2 * p + 2, m + 1, e, m + 1, r);
            return lres && rres && ((arr[m] + arr[m + 1]) % 2 == 1);
        }
    }
}

