#include <vector>
#include <queue>
#include <iostream>
#include <functional>
using namespace std;

// if an edge a-b is in the shortest path from 0 to n - 1
// then either dist(0, a) + a-b + dist(b, n - 1) = shortest distance
// or dist(0, b) + b-a + dist(a, n - 1) = shortest distance
// so is neccessary condition
// what if now dist(0, a) + a-b + dist(b, n - 1) = shortest distance
// if shortest path from 0 to a uses edge b-a, then we can decrease the shortest distance
// likewise if shortest path from b to n - 1 uses edge a-b

template <typename T>
void print(vector<T> arr) {
    for (T t: arr) {
        cout << t << endl;
    }
    //cout << endl;
}

class Solution {
public:
    vector<vector<vector<int>>> adjList;
    int n;

    vector<int> dijkstra(int src) {
        vector<int> dists(n, -1);
        priority_queue<vector<int>, vector<vector<int>>, function<bool(vector<int>&, vector<int>&)>> pq([](vector<int>& a, vector<int>& b) -> bool {return a[1] > b[1];});
        pq.push({src, 0});
        while (!pq.empty()) {
            vector<int> next = pq.top();
            pq.pop();
            int vtx = next[0];
            int d = next[1];
            if (dists[vtx] == -1) {
                dists[vtx] = d;
                for (vector<int>& nbr : adjList[vtx]) {
                    pq.push({nbr[0], d + nbr[1]});
                }
            }
        }
        return dists;
    }

    vector<bool> findAnswer(int n, vector<vector<int>>& edges) {
        adjList = vector(n, vector<vector<int>>());
        this->n = n;
        for (vector<int>& edge : edges) {
            adjList[edge[0]].push_back({edge[1], edge[2]});
            adjList[edge[1]].push_back({edge[0], edge[2]});
        }
        vector<int>&& from0 = dijkstra(0);
        vector<int>&& from1 = dijkstra(n - 1);
        int shortestDist = from0[n - 1];
        vector<bool> out;

        if (shortestDist == -1) {
            out = vector(edges.size(), false);
            return out;
        }


        for (vector<int>& edge : edges) {
            
            if (from0[edge[0]] != -1 && from1[edge[1]] != -1 && from0[edge[0]] + from1[edge[1]] + edge[2] == shortestDist) {
                out.push_back(true);
            } else if (from0[edge[1]] != -1 && from1[edge[0]] != -1 && from0[edge[1]] + from1[edge[0]] + edge[2] == shortestDist) {
                out.push_back(true);
            } else {
                out.push_back(false);
            }
        }

        return out;
    }
};

int main() {
    vector<vector<int>> edges = {{2,1,6}};
    int n = 3;
    Solution sol;
    print(sol.findAnswer(n, edges));
}