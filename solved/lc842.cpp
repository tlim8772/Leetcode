#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// simple backtracking

class Solution {
public:
    vector<ll> store;
    ll LIMIT = 1LL << 31;

    bool helper(string& num, int idx) {
        if (idx == num.size()) {
            return store.size() >= 3;
        } else if (store.size() < 2) {
            if (num[idx] == '0') {
                
                store.push_back(0);
                bool ans = helper(num, idx + 1);
                if (ans) return true;
                else {
                    store.pop_back();
                    return false;
                }
            } else {
                ll cnt = 0;
                
                while (idx < num.size() && cnt <= LIMIT) {
                    cnt *= 10;
                    cnt += num[idx] - '0';
                    idx ++;
                    
                    if (cnt > LIMIT) break;
                   
                    store.push_back(cnt);
                    bool ans = helper(num, idx);
                    if (ans) return true;
                    else store.pop_back();
                }
                
                return false;
            }
           
        } else {
            ll target = store[store.size() - 1] + store[store.size() - 2];
            if (target >= LIMIT) return false;
            if (num[idx] == '0') {
                if (target != 0) return false;
                
                store.push_back(0);
                bool ans = helper(num, idx + 1);
                if (ans) return true;
                store.pop_back();
                return false;
            } else if (target == 0) {
                return false;
            } else {
                ll cnt = 0;
                while (idx < num.size() && cnt < target) {
                    cnt *= 10;
                    cnt += num[idx] - '0';
                    idx ++;
                }
                if (cnt == target) {
                    
                    store.push_back(cnt);
                    bool ans = helper(num, idx);
                    if (ans) return true;
                    else store.pop_back();
                }
                return false;
            }
            
           
        }
    }
    vector<int> splitIntoFibonacci(string num) {
        helper(num, 0);
        for (ll x : store) cout << x << endl;


        vector<int> out;
        if (store.size() >= 3) out.insert(out.end(), store.begin(), store.end());
        return out;

    }
};

int main() {
    Solution sol;
    string s = "00246";
    vector<int>&& ans = sol.splitIntoFibonacci(s);
    //for (int x : ans) cout << x << endl;
}