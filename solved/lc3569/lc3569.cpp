#include <bits/stdc++.h>
using namespace std;

// prefix[i] = # of distinct primes in [0..i-1]
// suffix[i] = # of distinct primes in [i..n-1]
// when removing a prime in index i, prefix is only affected if idx i is the 1st occurrence of the prime
// suffix is only affected with idx i is the last occurrence of the prime (from left to right)
// for prefix, the interval affected is [i + 1, next index of prime]
// for suffix, interval affected is [prev index of prime, i]

// similarily when adding a prime
// prefix i is affected with new prime is the 1st occurrence
// suffix is affected if it is the last occurence

// use lazy segment tree to add range and query range max

struct SegTree {
    int len;
    vector<int> tree;
    vector<int> accu;

    SegTree(const vector<int>& arr): len(arr.size()), tree(4 * len, 0), accu(4 * len, 0) {
        build(0, 0, len - 1, arr);
    }

    inline int LEFT(int p) { return (p << 1) + 1; }

    inline int RIGHT(int p) { return (p << 1) + 2; }
 
    void build(int p, int s, int e, const vector<int>& arr) {
        if (s == e) {
            tree[p] = arr[s];
            return;
        }

        int m = (s + e) >> 1;
        build(LEFT(p), s, m, arr);
        build(RIGHT(p), m + 1, e, arr);
        tree[p] = max(tree[LEFT(p)], tree[RIGHT(p)]);
    }

    int addRange(int p, int s, int e, int acc, int l, int r, int val) {
        if (s == e || (s == l && e == r)) {
            tree[p] += val;
            accu[p] += val;
            return acc + tree[p];
        }

        int m = (s + e) >> 1;
        int newAcc = acc + accu[p];
        int left = 0, right = 0;
        if (r <= m) {
            left = addRange(LEFT(p), s, m, newAcc, l, r, val);
            right = newAcc + tree[RIGHT(p)];
        } else if (l > m) {
            left = newAcc + tree[LEFT(p)];
            right = addRange(RIGHT(p), m + 1, e, newAcc, l, r, val);
        } else {
            left = addRange(LEFT(p), s, m, newAcc, l, m, val);
            right = addRange(RIGHT(p), m + 1, e, newAcc, m + 1, r, val);
        }
        int res = max(left, right);
        tree[p] = res - acc;
        return res;
    }

    int queryMax(int p, int s, int e, int acc, int l, int r) {
        if (s == e || (s == l && e == r)) {
            return tree[p] + acc;
        }

        int m = (s + e) >> 1;
        int newAcc = acc + accu[p];
        if (r <= m) {
            return queryMax(LEFT(p), s, m, newAcc, l, r);
        } else if (l > m) {
            return queryMax(RIGHT(p), m + 1, e, newAcc, l, r);
        } else {
            int left = queryMax(LEFT(p), s, m, newAcc, l, m);
            int right = queryMax(RIGHT(p), m + 1, e, newAcc, m + 1, r);
            return max(left, right);
        }
    }
};

vector<bool> sieveOfEras(int n) {
    vector<bool> out(n + 1, true);
    out[0] = out[1] = false;

    for (int p = 2; p * p <= n; p++) {
        if (!out[p]) continue;

        for (int i = p * p; i <= n; i += p) {
            out[i] = false;
        }
    }

    return out;
}

int getPrev(const set<int>& s, int k) {
    auto ptr = s.lower_bound(k);
    if (ptr == s.begin()) {
        return -1;
    } else {
        return *(prev(ptr));
    }
}

int getNext(const set<int>& s, int k) {
    auto ptr = s.upper_bound(k);
    if (ptr == s.end()) {
        return -1;
    } else {
        return *ptr;
    }
}

class Solution {
public:
    vector<bool> isPrime;
    unordered_map<int, set<int>> stores;

    void collectPrimesPos(vector<int>& nums) {
        for (int i = 0; i < nums.size(); i++) {
            if (isPrime[nums[i]]) {
                stores[nums[i]].insert(i);
            }
        }
    }

    vector<int> getInitVals(vector<int>& nums) {
        vector<int> prefixInitVals(nums.size(), 0);
        unordered_set<int> prefixStore;
        // off by 1 because prefix[i] is number of distinct primes in [0..i-1]
        for (int i = 1; i < nums.size(); i++) {
            if (!isPrime[nums[i - 1]] || prefixStore.contains(nums[i - 1])) {
                prefixInitVals[i] = prefixInitVals[i - 1];
            } else {
                prefixInitVals[i] = prefixInitVals[i - 1] + 1;
                prefixStore.insert(nums[i - 1]);
            }
        }

       
        vector<int> suffixInitVals(nums.size(), 0);
        unordered_set<int> suffixStore;
        if (isPrime[nums.back()]) {
            suffixInitVals[nums.size() - 1] = 1;
            suffixStore.insert(nums.back());
        }
        for (int i = nums.size() - 2; i >= 0; i--) {
            if (!isPrime[nums[i]] || suffixStore.contains(nums[i])) {
                suffixInitVals[i] = suffixInitVals[i + 1];
            } else {
                suffixInitVals[i] = suffixInitVals[i + 1] + 1;
                suffixStore.insert(nums[i]);
            }
        }

        vector<int> initVals(nums.size(), 0);
        for (int i = 0; i < nums.size(); i++) {
            initVals[i] = prefixInitVals[i] + suffixInitVals[i];
        }

        return initVals;
    }
        

    vector<int> maximumCount(vector<int>& nums, vector<vector<int>>& queries) {
        isPrime = sieveOfEras(100000);
        collectPrimesPos(nums);

        vector<int> init = getInitVals(nums);
        SegTree st(init);

        vector<int> out;
        for (int i = 0; i < queries.size(); i++) {
            vector<int>& q = queries[i];

            int x = nums[q[0]];
            set<int>& store = stores[x];
            if (isPrime[x]) {
                if (store.size() == 1) {
                    // case 1: elem is 1st and last
                    int pl = q[0] + 1, pr = nums.size() - 1;
                    if (pl < nums.size()) {
                        st.addRange(0, 0, st.len - 1, 0, pl, pr, -1);
                    } 

                    int sr = q[0];
                    int sl = 0;
                    st.addRange(0, 0, st.len - 1, 0, sl, sr, -1);


                } else if (getPrev(store, q[0]) == -1) {
                    // case 2: x is the 1st occurrence
                    int pr = *store.upper_bound(q[0]);
                    int pl = q[0] + 1;
                    
                    if (pl < nums.size()) {
                        st.addRange(0, 0, st.len - 1, 0, pl, pr, -1);
                    }
                } else if (getNext(store, q[0]) == -1) {
                    // case 3: x is the last occurrence
                    int sr = q[0];
                    int sl = getPrev(store, q[0]) + 1;
                    
                    st.addRange(0, 0, st.len - 1, 0, sl, sr, -1);

                }

                store.erase(q[0]);
            }

            if (isPrime[q[1]]) {
                
                set<int>& store = stores[q[1]];

                if (store.size() == 0) {
                    // case 1: 1st and only prime to occur
                    int pl = q[0] + 1, pr = nums.size() - 1;
                    if (pl < nums.size()) {
                        st.addRange(0, 0, st.len - 1, 0, pl, pr, 1);
                    }

                    int sr = q[0], sl = 0;
                    st.addRange(0, 0, st.len - 1, 0, sl, sr, 1);
                } else if (getPrev(store, q[0]) == -1) {
                    // case 2: 1st occurrence
                    int pl = q[0] + 1, pr = *store.upper_bound(q[0]);
                    if (pl < nums.size()) {
                        st.addRange(0, 0, st.len - 1, 0, pl, pr, 1);
                    }

                } else if (getNext(store, q[0]) == -1) {
                    // case 3: last occurrence
                    int sr = q[0], sl = getPrev(store, q[0]) + 1;
                    st.addRange(0, 0, st.len - 1, 0, sl, sr, 1);
                }
                
                store.insert(q[0]);

            }
            nums[q[0]] = q[1];
            int ans = st.tree[0];
            out.push_back(ans);
        }
        return out;
        
    }
};

int main() {
    Solution sol;

    vector<int> nums = {2,34};
    vector<vector<int>> queries = {{1,2},{1,3}};
    
    vector<int> out = sol.maximumCount(nums, queries);
    for (int x : out) cout << x << " ";
    cout << endl;
}