#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// use a sparse table to get range max and min
// max(arr[l,r]) - min(arr[l,r]) only increases or stay the same as the subarray increases from left or right
// so we start from arr[l, r], the next subarray must be arr[l,r-1] or arr[l + 1, r]
// so we put (l,r) into a priority queue, everytime we pop (l,r) we add (l + 1, r) or (l, r - 1)
// we can reach a (l, r) tuple multiple times so must store a set

template <std::default_initializable T>
struct SparseTable {
    int MAX;
    vector<vector<T>> table;
    function<T(const T&, const T&)> func;

    SparseTable(const vector<T>& arr, function<T(const T&, const T&)> f): func(f) {
        MAX = (int) floor(log2(arr.size())) + 1;
        table = vector(arr.size(), vector<T>(MAX, T()));
        build(arr);
    }

    void build(const vector<T>& arr) {
        for (int i = 0; i < arr.size(); i++) {
            table[i][0] = arr[i];
        }

        for (int p = 1; p < MAX; p++) {
            int d = 1 << (p - 1);
            for (int i = 0; i < arr.size(); i++) {
                table[i][p] = (i + d >= arr.size()) 
                    ? table[i][p - 1]
                    : func(table[i][p - 1], table[i + d][p - 1]);
            }
        }
    }

    T rangeQuery(int l, int r) {
        int maxPow2 = floor(log2(r - l + 1));
        return func(table[l][maxPow2], table[r - (1 << maxPow2) + 1][maxPow2]);
    }
};

class Solution {
public:
    int N;

    inline ll coor(ll l, ll r) {
        return l * N + r;
    }

    long long maxTotalValue(vector<int>& nums, int k) {
        N = nums.size();

        SparseTable<int> stmin(nums, [](int x, int y) {return min(x, y);});
        SparseTable<int> stmax(nums, [](int x, int y) {return max(x, y);});

        unordered_map<ll, bool> visited;

        auto cmp = [](const array<int,3>& a1, const array<int,3>& a2) { return a1[0] < a2[0]; };
        priority_queue<array<int,3>, vector<array<int,3>>, decltype(cmp)> pq(cmp);
        
        int mi = stmin.rangeQuery(0, nums.size() - 1), ma = stmax.rangeQuery(0, nums.size() - 1);
        visited[coor(0, nums.size() - 1)] = true;
        pq.push(array<int,3>{ma - mi, 0, (int) nums.size() - 1});
      
        
        int kLeft = k;
        long long sum = 0;

        while (kLeft > 0 && !pq.empty()) {
            const auto [res, l, r] = pq.top(); pq.pop();
            kLeft--;
            sum += res;
            
            // if l < r, then (l, r - 1) and (l + 1, r) exists
            if (!visited.contains(coor(l, r - 1)) && l < r) {
                int mi = stmin.rangeQuery(l, r - 1), ma = stmax.rangeQuery(l, r - 1);
                
                visited[coor(l, r - 1)] = true;
                pq.push({ma - mi, l, r - 1});
            }

            if (!visited.contains(coor(l + 1, r)) && l < r) {
                int mi2 = stmin.rangeQuery(l + 1, r), ma2 = stmax.rangeQuery(l + 1, r);
                
                visited[coor(l + 1, r)] = true;
                pq.push({ma2 - mi2, l + 1, r});
            }
        }

        return sum;
    }
};

int main() {
    /*vector<int> nums = {3,1,2,5,7,1,9,0};
    function<int(int,int)> f = [](int x, int y) {return min(x, y);};
    SparseTable<int> st(nums, f);
    cout << st.rangeQuery(0,6) << endl;

    SparseTable<int> stmax(nums, [](int x, int y) {return max(x, y);});
    for (int i = 0; i < nums.size(); i++) {
        cout << stmax.rangeQuery(0, i) << endl;
    }*/

    Solution sol;
    vector<int> nums = {4,2,5,1};
    int k = 10;
    cout << sol.maxTotalValue(nums, k) << endl;
}