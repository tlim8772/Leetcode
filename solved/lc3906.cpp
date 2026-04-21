#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// digit dp.
// convert the num to a 16 digit string.
// convert the "DDDRRR" to the 7 coors we take, then flatten the coors.
// dp(is_same, idx1, idx2, last)
// is_same: whether we have been following the prefix of the given num
// idx1: idx for number
// idx2: idx for coors we are taking
// last: last digit we got, to ensure non decreasing.

// truth is we do not need i2, as we can get i2 by checking i1.

vector<pair<int,int>> convert_str_to_coor(string s) {
    auto out = vector<pair<int,int>>();
    out.emplace_back(0, 0);
    int r = 0, c = 0;

    for (auto cha : s) {
        (cha == 'D') ? r++ : c++;
        out.emplace_back(r, c);
    }

    return out;
}

vector<int> convert_coors_to_flat(const vector<pair<int,int>>& coors) {
    auto out = vector<int>();
    for (auto [r, c] : coors) out.push_back(r * 4 + c);
    return out;
}

struct Hash {
    // 0 <= i1 <= 15
    // 0 <= i2 <= 6
    // 0 <= last <= 9
    size_t operator()(tuple<bool, int, int> tup) const {
        auto [a, i1, last] = tup;
        return a + (i1 << 1) + (last << 5);
    }
};

struct Helper {
    ll store[2][17][10];

    void init() {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 17; j++) {
                for (int k = 0; k < 10; k++) {
                    store[i][j][k] = -1;
                }
            }
        }
    }

    // must -1 from result, because we consider the number 0 to be valid, 
    // even though in the question 0 is already an invalid input.
    ll dp(bool is_same, int i1, int i2, int last, const string& num, const vector<int>& pos) {
        if (i1 == 16) return 1;

        ll& ans = store[is_same][i1][last];
        if (ans != -1) return ans;

        bool is_on_path = i2 < 7 && pos[i2] == i1;
        int upper = (is_same) ? num[i1] - '0' : 9;
        int lower = (is_on_path) ? last : 0;
        ans = 0;

        for (int d = lower; d <= upper; d++) {
            ans += dp(
                is_same && d == upper, 
                i1 + 1, 
                i2 + is_on_path, 
                is_on_path ? d : last,
                num, 
                pos
            );
        }
        
        return ans;  
    }

    ll operator()(bool is_same, int i1, int i2, int last, const string& num, const vector<int>& pos) {
        init();
        return dp(is_same, i1, i2, last, num, pos);
    }
};

class Solution {
public:
    long long countGoodIntegersOnPath(long long l, long long r, string directions) {
        auto pos = convert_coors_to_flat(convert_str_to_coor(directions));

        auto r_str = to_string(r);
        if (r_str.size() < 16) r_str = string(16 - r_str.size(), '0') + r_str;
        //cout << r_str << endl;
        ll r_ans = Helper()(true, 0, 0, 0, r_str, pos);

        if (l == 0) return r_ans - 1;

        auto l_str = to_string(l - 1);
        if (l_str.size() < 16) l_str = string(16 - l_str.size(), '0') + l_str;
        ll l_ans = Helper()(true, 0, 0, 0, l_str, pos);

        return r_ans - l_ans;     
    }
};

int main() {
    Solution sol;

    ll l = 1, r = 987654;
    string dirs = "DDDRRR";
    ll ans = sol.countGoodIntegersOnPath(l, r, dirs);
    cout << ans << endl;
}
