#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Pair {
    int val, idx;
};

class Solution {
public:
    map<int, vector<Pair>> store;
    vector<bool> insidePQ;
    vector<bool> removed;
    priority_queue<Pair, vector<Pair>, function<bool(Pair&, Pair&)>> pq{[] (Pair& p1, Pair& p2) {return p1.val < p2.val;}};

    int K, k = 0;
    ll sum = 0;

    vector<ll> ans;

    void process(vector<int>& nums1, vector<int>& nums2) {
        for (int i = 0; i < nums1.size(); i ++) {
            store[nums1[i]].push_back({nums1[i], i});

            pq.push({nums2[i], i});
        }

        while (!pq.empty() && k < K) {
            Pair p = pq.top(); pq.pop();
          
            insidePQ[p.idx] = true;
            sum += p.val;
            k ++;
        }
       
    }

    void getAns(vector<int>& nums2) {
        for (auto it = store.rbegin(); it != store.rend(); it ++) {
            int val = it->first;
            vector<Pair>& idxs = it->second;
            //cout << val << endl;

            for (Pair& p : idxs) {
                removed[p.idx] = true;
                if (insidePQ[p.idx]) {
                    k --;
                    sum -= nums2[p.idx];
                }
            }
            

            while (!pq.empty() && k < K) {
                Pair p = pq.top(); pq.pop();
                if (removed[p.idx]) continue;

                insidePQ[p.idx] = true;
                sum += p.val;
                if (val == 5) cout << p.val << endl;
                k ++;
            }

            for (Pair& p : idxs) {
                ans[p.idx] = sum;
            }
        }
    }



    vector<long long> findMaxSum(vector<int>& nums1, vector<int>& nums2, int k) {
        insidePQ = vector(nums1.size(), false);
        removed = vector(nums1.size(), false);
        ans = vector<ll>(nums1.size(), 0);
        K = k;

        process(nums1, nums2);
        getAns(nums2);
        return ans;
    }
};

int main() {
    Solution sol;

    vector<int> nums1 = {2,2,2,2,2};
    vector<int> nums2 = {10,20,30,40,50};
    int k = 2;

    vector<ll> ans = sol.findMaxSum(nums1, nums2, k);
    for (ll a : ans) cout << a << " ";
    cout << endl;
}