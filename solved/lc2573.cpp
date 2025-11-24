#include <bits/stdc++.h>
using namespace std;

// check if matrix is valid, 3 conditions
// 1: matrix is symmetric
// 2: lcp[i][j] <= max(n - i, n - j)
// 3: if lcp[i][j] = K > 0 then lcp[i + 1][j + 1] = K - 1, lcp[i + 2][j + 2] = K - 2 ...
// until we reach 0, then can increase

// use lcp to find which indices must have the same character
// for each connected component, the CC whose smallest index is the smallest gets 'a' and so on
// each CC must be a clique with nC2 edges

// in fact we can view the longest common prefix matrix as an adjaceny matrix
// if lcp[i][j] > 0 , edge between i,j

// when we check lcp[i][j], using condition 3, we check lcp[i + k][j + k]
// later after generating the string, we only need to check the prefix match for coor (i,j)
// and can skip the 'diagonal' so time complexity is O(n^2)

struct UnionFind {
    int len;
    vector<int> parent, weight, smallest;
    unordered_map<int, char> rootChar;

    UnionFind(int n): len(n), parent(n, 0), weight(n, 1), smallest(n, 0) {
        for (int i = 0; i < n; i++) {
            parent[i] = smallest[i] = i;
        }
    }

    int find(int v) {
        return (parent[v] == v) ? v : parent[v] = find(parent[v]);
    }

    void join(int u, int v) {
        int pu = find(u), pv = find(v);
        if (pu == pv) return;

        int wpu = weight[pu], wpv = weight[pv];
       
     
        if (wpu < wpv) {
            parent[pu] = pv;
            weight[pv] += weight[pu];
            smallest[pv] = min(smallest[pv], smallest[pu]);
        } else {
            parent[pv] = pu;
            weight[pu] += weight[pv];
            smallest[pu] = min(smallest[pu], smallest[pv]);
        }
    }

    bool sortRoots() {
        vector<pair<int, int>> pairs;
        for (int i = 0; i < len; i++) {
            if (i != parent[i]) continue;
            pairs.push_back({i, smallest[i]});
        }

        if (pairs.size() > 26) return false;
        sort(pairs.begin(), pairs.end(), 
            [] (pair<int, int> p1, pair<int, int> p2) -> bool {return p1.second < p2.second;});
        for (int i = 0; i < pairs.size(); i++) {
            rootChar[pairs[i].first] = 'a' + i;
        }

        return true;
        
    }
};

class Solution {
public:
    bool checks(vector<vector<int>>& m) {
        int len = m.size();

        // check symmetric
        for (int i = 0; i < len; i++) {
            for (int j = i + 1; j < len; j++) {
                if (m[i][j] != m[j][i]) return false;
            }
        }

        // check lcp[i][j] <= max(n - i, n - j)
        for (int i = 0; i < len; i++) {
            for (int j = i; j < len; j++) {
                if (i == j && m[i][j] != len - i) return false;
                if (m[i][j] > min(len - i, len - j)) return false;
            }
        }
        //cout << "hello" << endl;
        // check lcp[i][j], lcp[i + 1][j + 1]
        vector<vector<bool>> visited = vector(len, vector(len, false));
        for (int i = 0; i < len; i++) {
            for (int j = i + 1; j < len; j++) {
                if (visited[i][j]) continue;
                visited[i][j] = true;
                
                if (m[i][j] == 0) continue;
                int l = m[i][j];

                // must check for the 0 too
                for (int k = 0; k <= l; k++) {
                    if (i + k >= len || j + k >= len) break;
                    if (m[i + k][j + k] != l - k) return false;
                    visited[i + k][j + k] = true;
                }
            }
        }

        return true;
    }

    string getString(vector<vector<int>>& m) {
        int len = m.size();
        UnionFind uf(len);
        string s(len, 'a');

        for (int i = 0; i < len; i++) {
            for (int j = i + 1; j < len; j++) {
                if (m[i][j] > 0) uf.join(i, j);
            }
        }

        bool result = uf.sortRoots();
        if (!result) return "";

        for (int i = 0; i < len; i++) {
            s[i] = uf.rootChar[uf.find(i)];
        }

        return s;
        
    }

    // matching prefix must be exactly length k
    bool checkPrefix(string& s, int i, int j, int k) {
        for (int l = 0; l < k; l++) {
            if (s[i + l] != s[j + l]) return false;
        }

        if (max(i + k, j + k) < s.size()) {
            if (s[i + k] == s[j + k]) return false;
        }

        return true;
    }

    bool checkString(vector<vector<int>>& m, string& s) {
        int len = m.size();
        vector<vector<bool>> visited = vector(len, vector(len, false));
        for (int i = 0; i < len; i++) {
            for (int j = i + 1; j < len; j++) {
                if (visited[i][j]) continue;
                visited[i][j] = true;

                bool match = checkPrefix(s, i, j, m[i][j]);
                if (!match) return false;

                for (int k = 0; k < m[i][j]; k++) {
                    visited[i + k][j + k] = true;
                }
            }
        }

        return true;
    }

    string findTheString(vector<vector<int>>& lcp) {
        bool check = checks(lcp);
        //cout << check << endl;
        if (!check) return "";

        string s = getString(lcp);
        bool check2 = checkString(lcp, s);
        cout << check2 << endl;
        if (!check2) return "";
        
        
        return s;
    }
};

int main() {
    Solution sol;

    vector<vector<int>> lcp = 
    {{3,0,1},{0,2,1},{1,1,1}};

    string s = sol.findTheString(lcp);
    cout << s << endl;
}