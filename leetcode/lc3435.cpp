#include <bits/stdc++.h>
using namespace std;

// see each length 2 strings as edges
// only 16 unique lower case characters. In the supersequence, only max 2 and at least 1
// why 2? because we can do this abccba. Notice regardless of what the edge are, we have x before y and y before x
// where x, y are any 2 chars present
// since we have 16 unique chars only, we can enumerate all possibilities
// Now, for a set, how to check if there exist a supersquence. 
// We remove all chars with cnt of 2. For the remaining chars of cnt 1, we check whether it is a DAG
// 1st, for the char with cnt 2, e.g a,b,c we write abc ... cba, then if there is a DAG, we slot the topo sort
// in the middle
// notice it satisfy all the edges (and possibly more). For the 2 cnt chars, we have x before y and y before x, regardless
// whether y is a 1 cnt or 2 cnt char
// for the 1 cnt char, if y is a 2 cnt, we have x before y and y before x
// if y is a 1 cnt, the DAG ensures that the correct edge exists

// impt: for char in words of 2 same chars e.g aa, bb they need to have cnt of 2

// impt: No need to consider transitivity
// eg a->b->c, there is no need for a to come before c if b is removed
// consider bacb and bcab. So this mean we can simply remove all 2 cnt chars, and their (out/in)going edges

class Solution {
public:
    int distinctCnt;
    vector<int> charToIdx; // the compressed index for each char a to z
    vector<bool> sameCharInWord;
    
    vector<vector<int>> adj;
    
    int shortestConfigSize = 999999;
    unordered_set<int> possibleConfigs;

    // since only <= 16 unique chars, we need to do compression
    void process(const vector<string>& words) {
        // compress the present chars
        set<char> charSet;
        for (const string& s : words) {
            for (char c : s) {
                charSet.insert(c);
            }
        }
        distinctCnt = charSet.size();

        charToIdx = vector(26, -1);
        int cnt = 0;
        for (char c : charSet) {
            charToIdx[c - 'a'] = cnt;
            cnt ++;
        }

        // process the adjList and sameCharInWord
        sameCharInWord = vector(26, false);
        adj = vector(26, vector<int>());
        for (const string& s : words) {
            int idx0 = charToIdx[s[0] - 'a'];
            int idx1 = charToIdx[s[1] - 'a'];

            if (idx0 == idx1) {
                sameCharInWord[idx0] = true;
            } else {
                adj[idx0].push_back(idx1);
            }
        }

    }

    bool canTopoSort(int curr, int config, vector<bool>& visited, vector<bool>& processed) {
        if (processed[curr]) return true;
        else if (visited[curr]) return false;

        visited[curr] = true;
        for (int next : adj[curr]) {
            if ((config >> next) & 1) continue; // if bit is 1, it is a 2 cnt
            bool res = canTopoSort(next, config, visited, processed);
            if (!res) return false;
        }

        processed[curr] = true;
        return true;
    }

    int getConfigSize(int config) {
        int cnt = 0;
        for (int i = 0; i < distinctCnt; i ++) {
            cnt += ((config >> i) & 1) + 1;
        }
        return cnt;
    }

    void processConfigs() {
        vector<bool> visited(26, false);
        vector<bool> processed(26, false);

        for (int config = 0; config < (1 << distinctCnt); config ++) {
            bool canWork = true;

            // check if sameCharInWork char have cnt of 2
            for (int i = 0; i < distinctCnt; i ++) {
                if (sameCharInWord[i] && ((config >> i) & 1) == 0) {
                    canWork = false;
                    break;
                }
            }

            if (!canWork) continue;

            for (int i = 0; i < distinctCnt; i ++) {
               if ((config >> i) & 1) continue;
                
                bool ans = canTopoSort(i, config, visited, processed);
                canWork = canWork && ans;
                if (!canWork) break;
            }

            if (canWork) {
                shortestConfigSize = min(shortestConfigSize, getConfigSize(config));
                possibleConfigs.insert(config);
            }

            visited.assign(26, false);
            processed.assign(26, false);
        }
    }

    vector<int> convert(int config) {
        vector<int> out(26, 0);
        
        for (int i = 0; i < 26; i ++) {
            if (charToIdx[i] == -1) continue;

            int idx = charToIdx[i];
            out[i] = ((config >> idx) & 1) + 1;
        }
        
        return out;
    }

    vector<vector<int>> supersequences(vector<string>& words) {
        process(words);
        processConfigs();

        vector<vector<int>> out;
        for (int config : possibleConfigs) {
            if (getConfigSize(config) == shortestConfigSize) {
                out.push_back(convert(config));
            }
        }

        return out;
    }
};

template <typename T>
void print(const vector<T>& arr) {
    for (T t : arr) {
        cout << t << " ";
    }
    cout << endl;
}

int main() {
    Solution sol;

    vector<string> words = {"xx"};

    vector<vector<int>> ans = sol.supersequences(words);

    for (const vector<int>& arr : ans) {
        print(arr);
    }

}
