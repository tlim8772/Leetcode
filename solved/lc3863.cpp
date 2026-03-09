#include <bits/stdc++.h>
using namespace std;

// if string is sorted in non descending, return 0.
// else if string len == 2 return -1
// else if smallest letter at pos 0 or largest at pos n - 1, return 1
// else minimum sorts is 2. we need 1 sort to bring smallest elem to pos 0, and 1 sort to bring 
// smallest elem to pos n - 1.
// else sort s[0:n-1] and s[1:n], if string is not sorted then return 3.
// max sorts needed is 3

class Solution {
public:
    int minOperations(string s) {
        if (s.size() == 1) return 0;

        if (is_sorted(s.begin(), s.end())) return 0;

        if (s.size() == 2) return -1;

        char smallest = *min_element(s.begin(), s.end());
        char largest = *max_element(s.begin(), s.end());
        if (s[0] == smallest || s.back() == largest) return 1;
        
        string temp = s;
        
        sort(s.begin(), s.end() - 1);
        // if s[0] == smallest 1 more sort is needed.
        // else (only) smallest elem is at s[n - 1], we need 2 sorts to bring it to pos 0.
        if (s[0] == smallest) return 2;

        sort(temp.begin() + 1, temp.end());
        // 2nd case.
        // if s[n - 1] == largest 1 more sort is needed.
        // else (only) largest elem is at s[0], we need 2 sorts to bring it to pos 0.
        if (temp.back() == largest) return 2;

        return 3;
    }
};

int main() {
    Solution sol;
    string s = "oool";
    cout << sol.minOperations(s) << endl;
}