#include <bits/stdc++.h>
using namespace std;

// for each node store the 3 best (highest score) neighbour
// why 3, for edge B-C, the best could be C
// consider the middle edge B-C, then consider A and D, problem is when A == D
// then either take 2nd best of B, best of C or best of B, 2nd best of C
// but when considering 2nd best of B, the 2nd best of B can be C, so need to be careful

class Solution {
public:
        vector<vector<pair<int, int>>> myBest;
        
        void insert(int n, int v, vector<pair<int, int>>& store) {
            store.push_back({n, v});
            sort(store.begin(), store.end(), 
                [](const pair<int, int>& a, const pair<int, int>& b) { return a.second > b.second;});
            
            if (store.size() > 3) store.pop_back();
        }

        void process(vector<int>& scores, vector<vector<int>>& edges) {
            myBest = vector(scores.size(), vector<pair<int, int>>());

            for (vector<int>& e : edges) {
                insert(e[1], scores[e[1]], myBest[e[0]]);
                insert(e[0], scores[e[0]], myBest[e[1]]);
            }
        }

        int maximumScore(vector<int>& scores, vector<vector<int>>& edges) {
            process(scores, edges);

            int best = -1;
            for (vector<int>& e : edges) {
                int b = e[0], c = e[1];
                int sum = scores[b] + scores[c];
                int ans = -1;

                vector<pair<int, int>> &bestB = myBest[b], &bestC = myBest[c];
                int pb = (bestB[0].first == c) ? 1 : 0;
                int pc = (bestC[0].first == b) ? 1 : 0;

                if (pb == bestB.size() || pc == bestC.size()) {
                    continue;
                } else if (bestB[pb].first != bestC[pc].first) {
                    ans = sum + bestB[pb].second + bestC[pc].second;
                    
                } else {
                    int pb2 = pb + 1;
                    if (pb2 < bestB.size() && bestB[pb2].first == c) {
                        pb2++;
                    } 
                    int r1 = (pb2 >= bestB.size()) ? -1 : bestB[pb2].second + bestC[pc].second;

                    int pc2 = pc + 1;
                    if (pc2 < bestC.size() && bestC[pc2].first == b) {
                        pc2++;
                    } 
                    int r2 = (pc2 >= bestC.size()) ? -1 : bestC[pc2].second + bestB[pb].second;

                    if (r1 == -1 && r2 == -1) {
                        continue;
                    } else {
                        ans = sum + max(r1, r2);
                    }
                }
                best = max(best, ans);
            }

            return (best < 0) ? -1 : best;
        }
};

int main() {
    Solution sol;

    vector<int> scores = {5,2,9,8,4};
    vector<vector<int>> edges = {{0,1},{1,2},{2,3},{0,2},{1,3},{2,4}};

    cout << sol.maximumScore(scores, edges) << endl;
}