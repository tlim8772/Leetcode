#include <bits/stdc++.h>
using namespace std;

// just use a set to get the left interval and right interval.
// if they can merge when adding a new number merge them and remove the 2 old intervals.

class SummaryRanges {
public:
    function<bool(const pair<int,int>&, const pair<int,int>&)> cmp = [] (auto p1, auto p2) { return p1.first < p2.first; };
    set<pair<int,int>, decltype(cmp)> store{cmp};
    unordered_set<int> used;
    
    SummaryRanges() {}
    
    void addNum(int value) {
        if (used.contains(value)) return;
        used.insert(value);

        pair<int,int> key = {value, value};
        int s = value, e = value;
        
        auto lb = store.lower_bound(key);
        if (lb != store.begin() && (--lb)->second == value - 1) {
            s = lb->first;
            store.erase(lb);
        }

        auto ub = store.upper_bound(key);
        if (ub != store.end() && ub->first == value + 1) {
            e = ub->second;
            store.erase(ub);
        }

        store.insert({s, e});
    }
    
    vector<vector<int>> getIntervals() {
        vector<vector<int>> out;
        out.reserve(store.size());
        for (auto [s, e] : store) out.push_back({s, e});
        return out;
    }
};

string pretty_print(vector<vector<int>> arr) {
    string out;
    for (auto& v : arr) {
        string s = "[";
        for (int x : v) {
            s += to_string(x);
            s += ' ';
        }
        s.pop_back();
        s += ']';
        
        out += s + " ";
    }
    return out;
}

int main() {
    SummaryRanges sol;

    sol.addNum(1);
    sol.addNum(7);
    cout << pretty_print(sol.getIntervals()) << endl;
    sol.addNum(2);
    cout << pretty_print(sol.getIntervals()) << endl;

}
