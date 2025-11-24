#include <bits/stdc++.h>
using namespace std;
using Tuple = tuple<int, int, int, int>;

// since s1 is repeated, we want to store matches of s1 starting at all possible indexes of s1

const Tuple INVALID_TUPLE = {-1, -1, -1, -1};

void printTuple(Tuple t) {
    const auto& [a, b, c, d] = t;
    cout << a << " " << b << " " << c << " " << d << endl;

}

class Solution {
public:
    string s1;
    int n1;

    string s2;
    int n2;

    vector<vector<int>> charMap = vector(26, vector<int>());

    vector<Tuple> matchResults;
    vector<int> idxWithMatch;

    // find smallest elem in arr > key
    int binarySearch(vector<int>& arr, int key) {
        int s = 0, e = arr.size() - 1;
        while (s < e) {
            int m = (s + e) >> 1;
            if (arr[m] > key) e = m;
            else s = m + 1;
        }
        return (arr[s] > key) ? arr[s] : -1;
    }

    void collect() {
        for (int i = 0; i < s1.size(); i ++) {
            charMap[s1[i] - 'a'].push_back(i);
        }
    }

    // check if s2 can be contained in as many multiples of s1
    bool canMatch() {
        for (char c : s2) {
            if (charMap[c - 'a'].size() == 0) return false;
        }
        return true;
    }

    Tuple match(int idx) {
        if (s1[idx] != s2[0]) return INVALID_TUPLE;

        int s = idx;
        int e = s; // contains latest indexed matched
        int s1_cnt = 1;
        int s2_ptr = 1;
        int s2_cnt = 0;

        while (1) {
            if (s2_ptr == s2.size()) {
                s2_cnt ++;
                if (e < s1.size() - 1 && s1_cnt == 1) {
                    s2_ptr = 0;
                } else {
                    return {s, e, s1_cnt, s2_cnt};
                }
            }

            char c = s2[s2_ptr];
            e = binarySearch(charMap[c - 'a'], e);
            if (e == -1) {
                s1_cnt ++;
                e = charMap[c - 'a'][0];
            }
            s2_ptr ++;
        }
    }

    int countFinalMatch(int idx) {
        int s1_ptr = idx;
        int s2_ptr = 0;
        int cnt = 0;

        while (s1_ptr < s1.size()) {
            if (s1[s1_ptr] == s2[s2_ptr]) {
                s2_ptr ++;
                if (s2_ptr == s2.size()) {
                    cnt ++;
                    s2_ptr = 0;
                }
            }
            s1_ptr ++;
        }

        return cnt;
    }
    

    void processMatches() {
        matchResults = vector(s1.size(), INVALID_TUPLE);
        for (int i = 0; i < s1.size(); i ++) {
            matchResults[i] = match(i);
            if (get<0>(matchResults[i]) != -1) idxWithMatch.push_back(i);
        }
    }

    int countMatches() {
        if (n1 == 1) {
            return countFinalMatch(0);
        }

        int s1_ptr = -1; // contains the last idx matched
        int s1_cnt = 0;
        int match_cnt = 0;

        while (s1_cnt < n1) {
            if (s1_cnt == n1 - 1) {
                match_cnt += countFinalMatch(s1_ptr + 1);
                break;
            }

            int matchIdx = binarySearch(idxWithMatch, s1_ptr);
            if (matchIdx == -1) {
                s1_ptr = idxWithMatch[0] - 1;
                s1_cnt ++;
                continue;
            }
            
            Tuple& t = matchResults[matchIdx];
            s1_ptr = get<1>(t);
            s1_cnt += get<2>(t) - 1;
            match_cnt += (s1_cnt >= n1) ? 0 : get<3>(t);
        }

        return match_cnt;
    }

    int getMaxRepetitions(string s1, int n1, string s2, int n2) {
        this->s1 = s1;
        this->n1 = n1;
        this->s2 = s2;
        this->n2 = n2;
        
        collect();

        if (!canMatch()) return 0;

        processMatches();

        int cnt = countMatches();
        return cnt / n2;
    }

};

/*int main() {
    Solution sol;
    sol.s1 = "aabbcc";
    sol.s2 = "aabb";
    sol.n1 = 1;

    sol.collect();
    sol.processMatches();
    for (Tuple& t : sol.matchResults) {
        printTuple(t);
    }

    cout << sol.countMatches() << endl;

}*/

int main() {
    Solution sol;
    string s1 = "acb";
    int n1 = 4;
    string s2 = "ab";
    int n2 = 2;

    cout << sol.getMaxRepetitions(s1, n1, s2, n2) << endl;
}