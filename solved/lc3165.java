package leetcode;

public class lc3165 {
    public int maximumSumSubsequence(int[] nums, int[][] queries) {
        long sum = 0;
        SegTree st = new SegTree(nums);
        for (int[] q : queries) {
            st.pointUpdate(0, 0, st.size - 1, q[0], q[1]);
            int ans = st.getMaxOfTree();
            sum += ans;
            sum %= 1000000007;
        }
        return (int) (sum % 100000007);
    }
}




class SegTree {
    // ct: can take, dt: don't take
    // F: front, B: back
    // each node is an array of [ctF ctB, ctF dtB, dtF ctB, dtF dtB]

    // ctF ctB = max(L(ctF dtB) + R(ctF ctB), L(ctF ctB) + R(dtF ctB)) op 0
    // ctF dtB = max(L(ctF dtB) + R(ctF dtB), L(ctF ctB) + R(dtF dtB)) op 1
    // dtF ctB = max(L(dtF dtB) + R(ctF ctB), L(dtF ctB) + R(dtF ctB)) op 2
    // dtF dtB = max(L(dtF dtB) + R(ctF dtB), L(dtF ctB) + R(dtF dtB)) op 3
    long[][] tree;
    int size;

    SegTree(int[] arr) {
        tree = new long[4 * arr.length][];
        size = arr.length;
        build(0, 0, size - 1, arr);
    }

    long rangeOp(int op, int p) {
        long[] l = tree[2 * p + 1];
        long[] r = tree[2 * p + 2];
        if (op == 0) {
            return Math.max(l[1] + r[0], l[0] + r[2]);
        } else if (op == 1) {
            return Math.max(l[1] + r[1], l[0] + r[3]);
        } else if (op == 2) {
            return Math.max(l[3] + r[0], l[2] + r[2]);
        } else {
            return Math.max(l[3] + r[1], l[2] + r[3]);
        }
    }

    void build(int p, int s, int e, int[] arr) {
        if (s == e) {
            tree[p] = new long[] {arr[s], 0, 0, 0};
        } else {
            int m = (s + e) / 2;
            build(2 * p + 1, s, m, arr);
            build(2 * p + 2, m + 1, e, arr);
            tree[p] = new long[4];
            for (int i = 0; i < 4; i ++) {
                tree[p][i] = rangeOp(i, p);
            }

        }
    }

    void pointUpdate(int p, int s, int e, int i, int val) {
        int m = (s + e) / 2;
        if (s == e) {
            tree[p][0] = val;
        } else if (i <= m) {
            pointUpdate(2 * p + 1, s, m, i, val);
            for (int op = 0; op < 4; op ++) {
                tree[p][op] = rangeOp(op, p);
            }
        } else if (i > m) {
            pointUpdate(2 * p + 2, m + 1, e, i, val);
            for (int op = 0; op < 4; op ++) {
                tree[p][op] = rangeOp(op, p);
            }
        }
    }

    int getMaxOfTree() {
        long max = 0;
        for (int i = 0; i < 4; i ++) {
            max = Math.max(max, tree[0][i]);
        }
        max = max % 1000000007;
        return (int) max;
    }

    public static void main(String[] args) {
        int[] arr = {3, 5, 9};
        SegTree st = new SegTree(arr);
        System.out.println(st.getMaxOfTree());
        st.pointUpdate(0, 0, st.size - 1, 1, 99);
        System.out.println(st.getMaxOfTree());
    }
}





