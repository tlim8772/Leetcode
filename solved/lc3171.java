package leetcode;

class SegTree {
    int INF = 0xffffffff;
    int[] tree;
    int size;

    SegTree(int[] arr) {
        size = arr.length;
        tree = new int[4 * size];
        buildTree(0, 0, size - 1, arr);
    }

    SegTree() {
        size = 0;
    }


    void buildTree(int p, int s, int e, int[] arr) {
        if (s == e) {
            tree[p] = arr[s];
        } else {
            int m = (s + e) / 2;
            buildTree(2 * p + 1, s, m, arr);
            buildTree(2 * p + 2, m + 1, e, arr);
            tree[p] = tree[2 * p + 1] & tree[2 * p + 2];
            
        }
    }

    // returns the smallest larger value (value of arr[i] & arr[i + 1] ... arr[k] is larger than k) and starting
    // at index i
    // if dont have, return -1;
    // accu storees arr[i] & arr[i + 1] .. arr[s - 1] or INF if not possible
    // output is {res, 1 or 0}, the 2nd part tells us whether res is obtained from arr[i] to arr[e], i.e the entire range
    // if cannot find arr[i] s.t arr[i] >= k, return INF, whichis -1 (as it is signed)
    int[] getSmallestLarger(int p, int s, int e, int i, int k, int accu) {
        int m = (s + e) / 2;
        if (s == e) {
            // accu >= k for us to proceed to this function call
            int res = accu & tree[p];
            return (res >= k) ? new int[] {res, 1} : new int[] {accu, 0};
        } else if (i <= s) {
           if ((accu & tree[p]) >= k) {
                return new int[] {accu & tree[p], 1};
            } else {
                int[] lres = getSmallestLarger(2 * p + 1, s, m, i, k, accu);
                return (lres[1] == 1) ? getSmallestLarger(2 * p + 2, m + 1, e, i, k, lres[0]) : lres;
            }
        } else if (i > m) {
            return getSmallestLarger(2 * p + 2, m + 1, e, i, k, accu);
        } else {
            int[] lres = getSmallestLarger(2 * p + 1, s, m, i, k, accu);
            return (lres[1] == 0) ? lres : getSmallestLarger(2 * p + 2, m + 1, e, i, k, lres[0]);
        }
    }

    // if cannot find k such at arr[i] & arr[i + 1] ... arr[k] <= k, returns arr[i] & arr[i + 1] ... arr[n]
    int[] getLargestSmaller(int p, int s, int e, int i, int k, int accu) {
        int m = (s + e) / 2;
        if (s == e) {
            // accu >= k for us to proceed to this function call
            int res = accu & tree[p];
            return (res <= k) ? new int[] {res, 0} : new int[] {res, 1};
        } else if (i <= s) {
            if ((accu & tree[p]) >= k) {
                return new int[] {accu & tree[p], 1};
            } else {
                int[] lres = getLargestSmaller(2 * p + 1, s, m, i, k, accu);
                return (lres[1] == 1) ? getLargestSmaller(2 * p + 2, m + 1, e, i, k, lres[0]) : lres;
            }
        } else if (i > m) {
            return getLargestSmaller(2 * p + 2, m + 1, e, i, k, accu);
        } else {
            int[] lres = getLargestSmaller(2 * p + 1, s, m, i, k, accu);
            return (lres[1] == 0) ? lres : getLargestSmaller(2 * p + 2, m + 1, e, i, k, lres[0]);
        }
    }

    
    public int minimumDifference(int[] nums, int k) {
        SegTree st = new SegTree(nums);
        int minDiff = 2147483647;
        for (int i = 0; i < nums.length; i ++) {
            int smallerLargest = st.getSmallestLarger(0, 0, st.size - 1, i, k, st.INF)[0];
            int largestSmaller = st.getLargestSmaller(0, 0, st.size - 1, i, k, st.INF)[0];
            if (smallerLargest == -1) {
                minDiff = Math.min(minDiff, Math.abs(k - largestSmaller));

            } else {
                minDiff = Math.min(minDiff, Math.min(Math.abs(k - smallerLargest), Math.abs(k - largestSmaller)));
            }
        }
        return minDiff;
    }
    
    
    
    
    
    
    
    public static void main(String[] args) {
        int[] arr = {1, 2, 4, 5};
        SegTree st = new SegTree(arr);
        System.out.println(st.minimumDifference(arr, 3));
        

        
        
    }
}
