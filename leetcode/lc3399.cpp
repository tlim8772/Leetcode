#include <bits/stdc++.h>
using namespace std;

// we collect the longest possible consective same char
// them we insert dividers
// eg 00000000, becomes 00100100
// now if we need to invert the last char, we flip the 2nd last bit instead
// what we want is the 1st and last char to be the same
// the mininum flips to break up a contigous range is the same if we want the 1st and last bit to be the same
// and mininum flips is just len / (space between + 1)

class Solution {
public:

    // returns true if number of flips to ensure gap is 1 is <= numOps
    bool ansIs1(string& s, int numOps) {
        int p0 = 0, p1 = 1;
        int c0 = 0, c1 = 0;
        for (char c : s) {
            int curr = c - '0';
            if (curr != p0) c0 ++;
            if (curr != p1) c1 ++;
            p0 = !p0;
            p1 = !p1;
        }
        return min(c0, c1) <= numOps;
    }

    bool binarySearch(string& str, int numOps, int target) {
        int p = 0;
        int c = 0;
        while (p < str.size()) {
            int s = p;
            while (p < str.size() && str[p] == str[s]) p++;
            

            int len = p - s;
            c += (len / (target + 1));

        }
        
        return (c <= numOps) ? true : false;
    }
    
    int minLength(string s, int numOps) {
        bool ans1 = ansIs1(s, numOps);
        if (ans1) return 1;
        int start = 2, end = s.size();
        while (start < end) {
            int mid = (start + end) >> 1;
            if (binarySearch(s, numOps, mid)) end = mid;
            else start = mid + 1;
        }
        return start;


    }
};

int main() {
    Solution sol;
    string s = "0110";
    int numOps = 1;
    cout << sol.minLength(s, numOps) << endl;
}