#include <bits/stdc++.h>
using namespace std;

// 0 is '(', 1 is ')'
// first, we do run length encoding eg "((()))()" becomes [(,3] [),3] [(,1] [),1].
// everytime we insert a pair into stack:
// 1. we first merge the last 2 if they are of the same character.
//    this ensures elements in the stack alternate (i.e '(', ')', '('...).
//
// 2. then we check if we can remove. We pop the last 2 elements, check if they are '(' and ')'.
//    we can batch remove multiples of k.
//    then insert the remainder back into the stack.
//
// 3. we do a final merge as the remaining elements can merge.

class Solution {
public:
    bool canRemove(vector<pair<int,int>>& stac, int k) {
        if (stac.size() < 2 || stac.back().first == '(') return false;
        
        pair<int,int> right = stac.back(); stac.pop_back();
        pair<int,int> left = stac.back(); stac.pop_back();
        
        int numToRemove = min(left.second, right.second) / k;
        //cout << numToRemove << endl;
        right.second -= numToRemove * k;
        left.second -= numToRemove * k;
        
        if (left.second > 0) stac.push_back(left);
        if (right.second > 0) stac.push_back(right);
        
        return (numToRemove > 0);
    }

    bool merge(vector<pair<int,int>>& stac) {
        if (stac.size() < 2) return false;
        
        pair<int,int> right = stac.back(); stac.pop_back();
        pair<int,int> left = stac.back(); stac.pop_back();
        if (right.first != left.first) {
            stac.push_back(left); 
            stac.push_back(right);
            return false;
        }
        
        right.second += left.second;
        stac.push_back(right);
        return true;
    }

    vector<pair<int,int>> collect(const string& s) {
        vector<pair<int,int>> out;
        int p = 0;
        char c = s[0];
        while (p < s.size()) {
            int start = p;
            while (p < s.size() && s[p] == c) p++;
            
            out.push_back(pair{c, p - start});
            
            if (p < s.size()) {
                c = s[p];
            }
        }
        return out;
    }

    string toString(vector<pair<int,int>>& stac) {
        string out = "";
        for_each(stac.begin(), stac.end(), 
            [&out] (pair<int,int>& p) { out += string(p.second, p.first); });
        return out;
    }
    
    string removeSubstring(string s, int k) {
        vector<pair<int,int>> out = collect(s), stac;
        
        for (pair<int,int>& p : out) {
            stac.push_back(p);
            while (merge(stac));

            if (p.first == ')') {
                while (canRemove(stac, k)) {
                    merge(stac);
                }
            }
        }
        return toString(stac);
    }
};

int main() {
    Solution sol;
    string s = ")(()";
    cout << sol.removeSubstring(s, 1) << endl;;

}