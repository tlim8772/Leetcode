#include <bits/stdc++.h>
using namespace std;

// simple union find on the accounts

struct UnionFind {
    vector<int> parents;
    vector<int> weights;

    UnionFind() {}

    UnionFind(int n): parents(n, 0), weights(n, 1) {
        for (int i = 0; i < n; i ++) {
            parents[i] = i;
        }
    }

    int find(int x) {
        if (parents[x] == x) return x;

        int p = find(parents[x]);
        parents[x] = p;
        return p;
    }

    void join(int x, int y) {
        int px = find(x);
        int py = find(y);
        if (px == py) return;

        if (weights[px] < weights[py]) {
            parents[px] = py;
            weights[py] += weights[px];
        } else {
            parents[py] = px;
            weights[px] += weights[py];
        }
    }

};

struct Acct {
    string name;
    unordered_set<string> emails;

    Acct(vector<string>& info) {
        name = info[0];
        emails.insert(info.begin() + 1, info.end());
    }

    bool canMerge(Acct& acct) {
        for (auto it = emails.begin(); it != emails.end(); it = next(it)) {
            if (acct.emails.contains(*it)) return true;
        }
        return false;
    }
};

class Solution {
public:
    UnionFind uf;
    vector<Acct> accts;
    

    vector<vector<string>> process(vector<vector<string>>& accounts) {
        for (vector<string>& acct : accounts) accts.emplace_back(acct);
        uf = UnionFind(accounts.size());
        

        for (int i = 0; i < accounts.size(); i ++) {
            for (int j = i + 1; j < accounts.size(); j ++) {
                if (accts[i].canMerge(accts[j])) uf.join(i, j);
            }
        }

        for (int i = 0; i < accounts.size(); i ++) {
            int p = uf.find(i);
            if (p != i) {
                accts[p].emails.insert(accts[i].emails.begin(), accts[i].emails.end());
            }
        }

        vector<vector<string>> out;
        for (int i = 0; i < accounts.size(); i ++) {
            if (uf.parents[i] != i) continue;
            
            out.emplace_back();
            for (const string& str : accts[i].emails) {
                out.back().push_back(str);
            }
            sort(out.back().begin(), out.back().end());
            out.back().insert(out.back().begin(), accts[i].name);
            
        }
        return out;
    }
    
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        return process(accounts);
    }
};

int main() {
   
}