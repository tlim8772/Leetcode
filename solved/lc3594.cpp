#include <bits/stdc++.h>
using namespace std;
const double ZERO_FLOAT = -0.000001;

// state is (bitmask of people on left/right side, boat on left/right side, index of condition)
// only 1 person must return with boat, we can take any, not neccesarily the fastest person
// for bitmask, 0 means on left side, 1 means on right side
// invariant of bm is that irrelevants bits is always 0
// use dijkstra on the state graph

// MUST DO const factor optimisation
// instead of creating a vector to store the next states and then pushing into priority queue
// just push directly to priority queue


struct State {
    int bm; // 0 means on left side, 1 means on right side
    int boat; // 0 means on left, 1, means on right
    int idx; // idx of the multiplier
};

struct Comp {
    bool operator()(const pair<State, double>& p1, const pair<State, double>& p2) {
        return p1.second > p2.second;
    }
};

using PQ = priority_queue<pair<State, double>, vector<pair<State, double>>, Comp>; 

class Solution {
public:
    int n, k, m;
    vector<int> times;
    vector<double> mults;

    inline int coor(const State& s) {
        return s.bm * 2 * m + s.boat * m + s.idx;
    }

    void sendBack(State s, double cost, const vector<double>& dists, PQ& pq) {
        for (int i = 0; i < n; i++) {
            if (((s.bm >> i) & 1) == 0) continue;

            double time = times[i] * mults[s.idx];
            int newIdx = (s.idx + (int) floor(time)) % m;
            int newBm = s.bm & ~(1 << i);
            State next = {newBm, 0, newIdx};
            
            int pos = coor(next);
            if (dists[pos] < -0.1) {
                pq.push(pair{next, cost + time});
            }

           

        }
    }

    // tries all possible groups to send to the right side
    void helper(int pos, 
                int left, 
                int bm, 
                int maxTime,
                const int idx,
                const double cost, 
                const vector<double>& dists, 
                PQ& pq) 
    {
        if (pos >= n || left == 0) {
            return;
        } 

        if (((bm >> pos) & 1) == 0) {
            // we take this person
            double time = max(maxTime, times[pos]) * mults[idx];
            int newIdx = (idx + (int) floor(time)) % m;
            int newBm = bm | (1 << pos);
            State next = {newBm, 1, newIdx};

            int thisPos = coor(next);
            if (dists[thisPos] < -0.1) {
                pq.push(pair{next, cost + time});
            }

            helper(pos + 1, left - 1, newBm, max(maxTime, times[pos]), idx, cost, dists, pq);
        }
        

        // dont take
        helper(pos + 1, left, bm, maxTime, idx, cost, dists, pq);
        
    }

    double dijkstra() {
        PQ pq;
        vector<double> dists((1 << n) * 2 * m, -1.0);

        pq.push(pair{State{0, 0, 0}, 0.0});

        while (!pq.empty()) {
            auto [state, cost] = pq.top(); 
            
            pq.pop();
            
            int pos = coor(state);
            if (dists[pos] > -0.1) continue;

            dists[pos] = cost;
            // everyone reach right side, can return immediately
            if (state.bm == (1 << n) - 1) { 
                return cost;
            }

            if (state.boat == 1) {
                sendBack(state, cost, dists, pq);
            } else {
                helper(0, k, state.bm, 0, state.idx, cost, dists, pq);
            }
        }

        return -1.0;
    }

    
    double minTime(int n, int k, int m, vector<int>& time, vector<double>& mul) {
        this->n = n, this->k = k, this->m = m;
        times = time, mults = mul;

        double ans = dijkstra();
        return ans;
    }



    
};

int main() {
    Solution sol;

    int n = 2;
    int k = 1;
    int m = 2;
    vector<int> time = {10,10};
    vector<double> mul = {2.0,2.0};

    cout << sol.minTime(n, k, m, time, mul) << endl;
}