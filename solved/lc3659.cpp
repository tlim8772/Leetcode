#include <bits/stdc++.h>
using namespace std;

// question is misleading, we want to parititon elements into groups
// s.t each group has k elements whic are all distinct
// simulate the partitioning process
// for each group, we take the elements with the highest count and has not been taken by this group

// don't have rigorous proof to show nums is partitionable accoding to question requirements 
// iff this algo succeeds

// greedy proof why for each group, take the elem with highest count and has not been taken yet, call it x
// suppose we do not and still get optimal solution, call elem taken y
// then there exist a group where elem with x and no y (otherwise freq[y] > freq[x])
// we swap the x and y

class Solution {
public:
    bool partitionArray(vector<int>& nums, int k) {
        if (nums.size() % k != 0) return false;

        unordered_map<int,int> store;
        for (int num : nums) store[num]++;
        if (store.size() < k) return false;

        auto cmp = [](const pair<int,int>& p1, const pair<int,int>& p2) { return p1.second < p2.second; };
        priority_queue<pair<int,int>, vector<pair<int,int>>, decltype(cmp)> pq(store.begin(), store.end(), cmp);

        int N = nums.size(), numGroups = N / k;
        for (int i = 0; i < numGroups; i++) {
            vector<pair<int,int>> items;
            for (int j = 0; j < k; j++) {
                if (pq.empty()) return false;

                pair<int,int> p = pq.top(); pq.pop();
                if (p.second > 1) {
                    p.second--;
                    items.push_back(p);
                }
            }

            for (const pair<int,int> item : items) {
                pq.push(item);
            }
        }

        return true;

    }
};

int main() {
    Solution sol;

    vector<int> nums = {1,2,2,3};
    int k = 3;
    cout << sol.partitionArray(nums, k) << endl;
}

