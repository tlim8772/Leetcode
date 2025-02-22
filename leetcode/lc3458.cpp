#include <array>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
using Pair = array<int, 2>;

// only have 26 such special substrings, as we only have 26 chars, and a special substring must start
// at the 1st occurrence of a char. It may not end at the last occurrence of that char
// for each char, find (1st greedy approach) shortest substring starting from 1st occurrence of that char
// once we have <= 26 valid ranges, it becomes: can we select k disjoint ranges
// greedy approach, choose the range with the leftmost end point, recurse

class Solution {
public:
    vector<Pair> firstLast{26, {999999, -1}};
    vector<Pair> validRanges;


    void getInfo(const string& s) {
        for (int i = 0; i < s.size(); i ++) {
            Pair& p = firstLast[s[i] - 'a'];
            p[0] = min(p[0], i);
            p[1] = max(p[1], i);
        }
    }

    void getRanges(const string& s) {
        getInfo(s);
        
        for (int i = 0; i < 26; i ++) {
            if (firstLast[i][1] == -1) continue;

            int end = firstLast[i][1];
            int start = firstLast[i][0];
            
            int ptr = start;
            int invalid = false;
            while (ptr < s.size() && ptr <= end) {
                // if a char inside the interval we are checking has an occurrence that it outside start, it is invalid
                if (firstLast[s[ptr] - 'a'][0] < start) {
                    invalid = true;
                    break;
                }

                
                end = max(end, firstLast[s[ptr] - 'a'][1]);
                ptr ++;
            }
            if (invalid) continue;
            
            if (start == 0 && end == s.size() - 1) continue;

            validRanges.push_back({start, end});
        }

        
        
    }

    int getMaxDisjointRanges(vector<Pair>& ranges) {
        // sort ranges in increasing start point
        sort(ranges.begin(), ranges.end(), [] (const Pair& p1, const Pair& p2) -> bool { return p1[1] < p2[1]; });

        int count = 0;
        int limit = -1;

        for (auto it = ranges.begin(); it != ranges.end(); it ++) {
            if ((*it)[0] <= limit) continue;
            count ++;
            cout << (*it)[0] << " " << (*it)[1] << endl;
            limit = (*it)[1];
        }

        return count;
    }


    bool maxSubstringLength(string s, int k) {

        
        getRanges(s);
        for (int i = 0; i < 26; i ++) {
            cout << firstLast[i][0] << " " << firstLast[i][1] << endl;
        }
        cout << endl;
        int best = getMaxDisjointRanges(validRanges);

       
        return best >= k;
    }





};

int main() {
    string s = "gaixgqpgdrhhxuurgrriwovkbjjbffnlnjcnyzbmblymcmvnftlpaiqepgxgip erurhgduaqpqxqgaxdexur";
    cout << s[20] << " " << s[21] << " " << s[23] << " " << s[37] << " " << s[49] << " " << s[55] << endl;
    int k = 6;
    Solution sol;
    cout << sol.maxSubstringLength(s, k);
}