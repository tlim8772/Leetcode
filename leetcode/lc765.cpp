#include <bits/stdc++.h>
using namespace std;

// suppose the initial setup is {0,2,1,3}
// in the final arrangement, seat[0], seat[1] is 1 couple .. seat[2*i], seat[2*i+1] is another
// for each couple seat, draw and edge to another couple seat, if the couple seat in, seperated in these 2 seats
// the graph is such that each vertex is degree 2 or 0, such a graph is composed of cycles and isolated vertex
// if the cycle has n vertices, it takes n - 1 swaps minimum. Prove using induction


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


class Solution {
public:
    vector<int> where;
    UnionFind uf;
    
    int minSwapsCouples(vector<int>& row) {
        where = vector(row.size(), 0);
        for (int i = 0; i < row.size(); i ++) {
            where[row[i]] = i;
        }
        
        uf = UnionFind(row.size() / 2);
        for (int i = 0; i < row.size(); i += 2) {
            int p1 = row[i];
            int p1p = (p1 % 2 == 0) ? p1 + 1 : p1 - 1;
            int p1ps = where[p1p];
            uf.join(i / 2, p1ps / 2);

            int p2 = row[i + 1];
            int p2p = (p2 % 2 == 0) ? p2 + 1 : p2 - 1;
            int p2ps = where[p2p];
            uf.join(i / 2, p2ps / 2);
        }

        int cnt = 0;
        for (int i = 0; i < row.size() / 2; i ++) {
            if (uf.parents[i] == i) cnt += uf.weights[i] - 1;
        }
        return cnt;

    }
};

int main() {
    Solution sol;
    vector<int> s = {3,2,0,1};
    cout << sol.minSwapsCouples(s) << endl;
}

