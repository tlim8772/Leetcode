#include <bits/stdc++.h>
using namespace std;

// use KMP for string matching, then find all patterns contained in the string
// however, when marking cells that match a pattern, there can be multipple pattern matches
// when finding a cell that is already marked true, we do not continue, otherwise TC is O(n^2)
// e.g consider s = "a*100", pattern = "a*50"

vector<int> kmp(const string& s) {
    vector<int> out(s.size(), 0);
    
    for (int i = 1; i < s.size(); i++) {
        int parLen = out[i - 1];
        while (1) {
            if (parLen == 0) {
                out[i] = (s[0] == s[i]) ? 1 : 0;
                break;
            }
            
            if (s[parLen] == s[i]) {
                out[i] = parLen + 1;
                break;
            } else {
                parLen = out[parLen - 1];
            }
        }
    }

    return out;
}

class Solution {
public:
    int R, C;
    vector<vector<pair<bool, bool>>> res;
    vector<int> KMP;

    void processRow(const vector<vector<char>>& grid, const string& pattern) {
        int curr = 0; // how many chars we have matched
        for (int i = 0; i < R * C; i++) {
            int r = i / C, c = i % C;
            char cha = grid[r][c];


            while (1) {
                if (pattern[curr] == cha) {
                    curr++;
                    break;
                } else {
                    if (curr == 0) {
                        break;
                    } else {
                        curr = KMP[curr - 1];
                    }
                }
            }

            if (curr == pattern.size()) {
                for (int j = i; j > i - curr; j--) {
                    int r2 = j / C, c2 = j % C;
                    if (res[r2][c2].first) break; // we do not want to double count, will lead to O(n^2) time complexity
                    
                    res[r2][c2].first = true;
                }
                
                curr = KMP.back();
            }
        }
    }

    void processCol(const vector<vector<char>>& grid, const string& pattern) {
        int curr = 0;
        for  (int i = 0; i < R * C; i++) {
            int r = i % R, c = i / R;
            char cha = grid[r][c];

            while (1) {
                if (pattern[curr] == cha) {
                    curr++;
                    break;
                } else {
                    if (curr == 0) {
                        break;
                    } else {
                        curr = KMP[curr - 1];
                    }
                }
            }

            if (curr == pattern.size()) {
                for (int j = i; j > i - curr; j--) {
                    int r2 = j % R, c2 = j / R;
                    if (res[r2][c2].second) break;

                    res[r2][c2].second = true;
                }

                curr = KMP.back();
            }
        }
    }
    
    int countCells(vector<vector<char>>& grid, string pattern) {
        R = grid.size(), C = grid[0].size();
        KMP = kmp(pattern);
        res = vector(grid.size(), vector(grid[0].size(), pair<bool, bool>{false, false}));

        processRow(grid, pattern);
        processCol(grid, pattern);

        int cnt = 0;
        for (int r = 0; r < R; r++) {
            for (int c = 0; c < C; c++) {
                if (res[r][c].first && res[r][c].second) cnt++;
            }
        }

        return cnt;
    }
};

int main() {
    Solution sol;
    vector<vector<char>> grid = {{'a', 'a', 'a'}, {'b', 'b', 'a'}};
    string pattern =  "aba";

    cout << sol.countCells(grid, pattern);

    
}