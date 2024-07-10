import java.util.*;

class Solution {
    SegTree st;
    int[] arr;

    boolean isValid(int i) {
        return (i >= 0 && i <= arr.length - 1);
    }

    boolean isPeak(int i) {
        if (i <= 0 || i >= arr.length - 1) return false;
        else if (arr[i] > Math.max(arr[i - 1], arr[i + 1])) return true;
        else return false;
    }

    int helperQuery(int l, int r) {
        int ans = st.rangeSum(0, 0, st.n - 1, l, r);
        if (l != 0 && l != arr.length - 1 && arr[l] > Math.max(arr[l - 1], arr[l + 1])) ans --;
        if (l != r && r != 0 && r != arr.length - 1 && arr[r] > Math.max(arr[r - 1], arr[r + 1])) ans --;
        return ans;
    }

    void helperUpdate(int i, int v) {
        arr[i] = v;
        if (isValid(i)) st.pointUpdate(0, 0, st.n - 1, i, isPeak(i) ? 1 : 0);
        if (isValid(i - 1)) st.pointUpdate(0, 0, st.n - 1, i - 1, isPeak(i - 1) ? 1 : 0);
        if (isValid(i + 1)) st.pointUpdate(0, 0, st.n - 1, i + 1, isPeak(i + 1) ? 1 : 0);
    }

    int[] process(int[] nums) {
        int[] out = new int[nums.length];
        for (int i = 0; i < nums.length; i ++) {
            out[i] = (isPeak(i)) ? 1 : 0;
        }
        return out;
    }



    public List<Integer> countOfPeaks(int[] nums, int[][] queries) {
        ArrayList<Integer> out = new ArrayList<>();
        arr = nums;
        int[] array = process(nums);
        st = new SegTree(array);
        for (int[] q : queries) {
            if (q[0] == 1) {
                out.add(helperQuery(q[1], q[2]));
            } else {
                helperUpdate(q[1], q[2]);
            }
        }
        return out;
    }

    public static void main(String[] args) {
        int[] nums = {5, 4, 8, 6};
        int[][] queries = {{1,2,2}};
        Solution sol = new Solution();
        System.out.println(Arrays.toString(sol.countOfPeaks(nums, queries).toArray()));
    }
}

class SegTree {
    int[] tree;
    int n;

    SegTree(int[] arr) {
        this.n = arr.length;
        tree = new int[4 * n];
        buildTree(0, 0, n - 1, arr);
    }

    void buildTree(int p, int s, int e, int[] nums) {
        if (s == e) {
            tree[p] = nums[s];
        } else {
            int m = (s + e) / 2;
            buildTree(2 * p + 1, s, m, nums);
            buildTree(2 * p + 2, m + 1, e, nums);
            tree[p] = tree[2 * p + 1] + tree[2 * p + 2];
        }
    }

    void pointUpdate(int p, int s, int e, int i, int v) {
        int m = (s + e) / 2;
        if (s == e) {
            tree[p] = v;
        } else if (i <= m) {
            pointUpdate(2 * p + 1, s, m, i, v);
            tree[p] = tree[2 * p + 1] + tree[2 * p + 2];
        } else {
            pointUpdate(2 * p + 2, m + 1, e, i, v);
            tree[p] = tree[2 * p + 1] + tree[2 * p + 2];
        }
    }

    int rangeSum(int p, int s, int e, int l, int r) {
        int m = (s + e) / 2;
        if (s == e || (s == l && e == r)) {
            return tree[p];
        } else if (r <= m) {
            return rangeSum(2 * p + 1, s, m, l, r);
        } else if (l > m) {
            return rangeSum(2 * p + 2, m + 1, e, l, r);
        } else {
            return rangeSum(2 * p + 1, s, m, l, m) + rangeSum(2 * p + 2, m + 1, e, m + 1, r);
        }
    }
}

