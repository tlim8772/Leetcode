#include <bits/stdc++.h>
using namespace std;

// dp
// 1st, we get the sorted list of divisors of n
// let dp(n, idx, k): minimum max divisor to make n, starting at index idx, and can choose k integers left
// also we must build the routing table to build the solution
// dp works, but need to do a lot of constant factor optimisations
// mainly, we want to reduce the space of divisors considered


// if ans == -1, means this state is invalid (but is processed already)
// if ans == -999999999, means this state is not processed yet
struct Res {
    int ans = 999999999;
    int divisor = -1; // if -1 means dont take sortedDivisor[idx]
    int next = -1;
};

// have to distinguish between 3 special states
// when state is unvisited and
// when the state is invalid (i.e cannot be reduced to 1)
// or when state is valid but no more numbers to take (i.e when n == 1 and k == 0)

Res unvisited = {
    .ans = 999999999, 
};

Res invalid = {
    .ans = 100000, 
};

Res sentinel = {
    .ans = 1,
};


class Solution {
public:
    int N, DIV, K;
    vector<Res> store;
    vector<int> sortedDivisors;


    inline int coor(int n, int idx, int k) {
        return n * DIV * K + idx * K + k;
    }

    vector<int> getSortedDivisors(int n, int k) {
        int lim = (int) ceil(sqrt(n));
        vector<int> out;
        for (int i = 1; i <= n; i++) {
            if (n % i == 0) {
                out.push_back(i);
                if (i >= lim) break;
            }

        }

        sort(out.begin(), out.end());
        return out;
    }

    // special case when k = 2
    vector<int> solveK2(int n) {
        vector<int> res;
        int x = sortedDivisors.back();
        
        return {n / x, x};
    }

    // invariant: n >= 1
    // we do not store results for idx == DIV or k == 0
    Res dp(int n, int idx, int k) {
        if (n == 1) {
            if (k == 0) {
                return sentinel;
            } else {
                return invalid;
            }
        }

        // here n > 1, and we have no more divisors to choose from or run out of space 
        if (idx == DIV || k == 0) {
            return invalid;
        } 

        if (n < sortedDivisors[idx]) {
            return invalid;
        }
        
        int pos = coor(n, idx, k);
        if (store[pos].ans != 999999999) {
            return store[pos];
        }

        Res take = (n % sortedDivisors[idx] == 0) ? dp(n / sortedDivisors[idx], idx, k - 1) : invalid;
        Res notake = dp(n, idx + 1, k);

        Res myRes;
        if (take.ans <= notake.ans) {
            myRes.ans = max(sortedDivisors[idx], take.ans);
            myRes.divisor = sortedDivisors[idx];
            myRes.next = (k - 1 == 0) ? -1 : coor(n / sortedDivisors[idx], idx, k - 1);
        } else {
            myRes.ans = notake.ans;
            myRes.next = (idx + 1 == DIV) ? -1 : coor(n, idx + 1, k);
        }
        store[pos] = myRes;
        return myRes;
    }


    vector<int> minDifference(int n, int k) {
        sortedDivisors = getSortedDivisors(n, k);
        if (k == 2) return solveK2(n);

        N = n + 1, DIV = sortedDivisors.size(), K = k + 1;
        store = vector<Res>(N * DIV * K, unvisited);

        int best = 999999999;
        int start = -1;
        int pos = -1;
        for (int i = 0; i < sortedDivisors.size(); i++) {
            Res res = dp(n / sortedDivisors[i], i, k - 1);
            
            // need to check if res.ans is < 1st divisor chosen, this is possible
            if (res.ans != 100000 && res.ans >= sortedDivisors[i] && res.ans - sortedDivisors[i] < best) {
                //cout << sortedDivisors[i] << " " << res.ans << endl;
                
                best = res.ans - sortedDivisors[i];
                start = sortedDivisors[i];
                pos = coor(n / sortedDivisors[i], i, k - 1);
            }
        }

        //cout << best << endl;
        //cout << pos << endl;
        vector<int> out = {start};
        int curr = pos;
        while (curr != -1) {
            const Res& res = store[curr];
            //cout << store[curr].take << " " << store[curr].divisor << " " << store[curr].next <<  endl;
            if (res.divisor > 0) {
                out.push_back(res.divisor);
            }
            curr = res.next;
        }

        return out;

    }
};

int main() {
    Solution sol;

    int n = 83160;
    int k = 5;

    vector<int> ans = sol.minDifference(n, k);
    for (int x : ans) {
        cout << x << " ";
    }
    cout << endl;
}