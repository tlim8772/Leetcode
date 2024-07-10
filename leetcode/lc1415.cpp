#include <bits/stdc++.h> 
#include <string>
using namespace std;

class Solution {
public:   
    vector<string> store;

    void print(vector<char>&& path) {
        string s = "";
        for (int i = 0; i < path.size(); i ++) {
            s.push_back(path[i]);
        }
        //cout << s << endl;
        store.push_back(s);
    }

    void helper(int index, int limit, char prev, vector<char>&& path) {
        if (index == limit) {
            print(forward<vector<char>>(path));
        } else if (prev == 'z') {
            for (int i = 0; i < 3; i ++) {
                path.push_back('a' + i);
                helper(index + 1, limit, 'a' + i, forward<vector<char>>(path));
                path.pop_back();
            }
        } else {
            for (int i = 0; i < 3; i ++) {
                if (prev != 'a' + i) {
                    path.push_back('a' + i);
                    helper(index + 1, limit, 'a' + i, forward<vector<char>>(path));
                    path.pop_back();
                }
            }
        }
    }

    string getHappyString(int n, int k) {
        store = vector<string>();
        //vector<char> path;
        helper(0, n, 'z', vector<char>());
        sort(store.begin(), store.end());
        return (k - 1 >= store.size()) ? "" : store[k - 1];
    }
};

int main() {
    Solution sol;
    cout << sol.getHappyString(1, 3) << endl;
    //sol.print({'b', 'a', 'd'});
}