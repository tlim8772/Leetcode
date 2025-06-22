#include <bits/stdc++.h>
using namespace std;
const double ZERO_FLOAT = -0.000001;

// state is (bitmask of people on left/right side, boat on left/right side, index of condition)
// only 1 person must return with boat, we can take any, not neccesarily the fastest person
// for bitmask, 0 means on left side, 1 means on right side
// invariant of bm is that irrelevants bits is always 0
// use dijkstra on the state graph


// generate all combinations with <= lim items
void combinations(int idx, int lim, const vector<int>& arr, vector<int>& stack, vector<vector<int>>& store) {
    if (idx == arr.size() || stack.size() == lim) return;
    
    stack.push_back(arr[idx]);
    store.push_back(stack);
    combinations(idx + 1, lim, arr, stack, store);

    stack.pop_back();
    combinations(idx + 1, lim, arr, stack, store);

}

struct State {
    int bm;
    int boat;
    int idx; // idx of the multiplier
};

class Solution {
public:
    int n, k, m;
    vector<int> times;
    vector<double> mults;

    int clip(int bm) {
        return bm & ((1 << n) - 1);
    }

    inline int coor(const State& s) {
        return s.bm * 2 * m + s.boat * m + s.idx;
    }

    // when boat is on right side
    vector<pair<State, double>> sendBack(const State& s) {
        vector<pair<State, double>> out;

        
        for (int i = 0; i < n; i++) {
            if (((s.bm >> i) & 1) == 0) continue;

            double len = times[i] * mults[s.idx];
            int newIdx = (s.idx + (int) floor(len)) % m;
            int newBm = s.bm & ~(1 << i);
            int newBoat = 0;

            out.push_back(pair{State{newBm, newBoat, newIdx}, len});
        }

        return out;
    }

   

    vector<pair<State, double>> sendForward(const State& s) {
        vector<pair<State, double>> out;

        vector<int> onLeft;
        for (int i = 0; i < n; i++) {
            if ((s.bm >> i) == 1) continue;
            onLeft.push_back(i);
        }

        vector<int> stack;
        vector<vector<int>> store;
        combinations(0, min(k, (int) onLeft.size()), onLeft, stack, store);

        for (const vector<int>& arr : store) {
            int worstPersonTime = 0;
            for (int x : arr) {
                worstPersonTime = max(worstPersonTime, times[x]);
            }

            int newBm = s.bm;
            for (int x : arr) {
                newBm |= (1 << x);
            }

            double len = worstPersonTime * mults[s.idx];
            int newIdx = (s.idx + (int) floor(len)) % m;

            State newState = State{newBm, 1, newIdx};
            
            out.push_back(pair{newState, len});

        }

        return out;
    }


    double dijkstra() {
        auto cmp = [] (const pair<State, double>& p1, const pair<State, double>& p2) { return p1.second > p2.second; };
        priority_queue<pair<State, double>, vector<pair<State, double>>, decltype(cmp)> pq(cmp);

        vector<double> dists = vector<double>((1 << n) * 2 * m, -1.0);

        pq.push(pair{State{0,0,0}, 0.0});

        while (!pq.empty()) {
            auto p = pq.top(); pq.pop();
            int pos = coor(p.first);
            if (dists[pos] >= ZERO_FLOAT) continue; 

            dists[pos] = p.second;
            if (p.first.bm == ((1 << n) - 1)) {
                return p.second;
            }
            
            vector<pair<State, double>> nextStates;
            if (p.first.boat == 0) {
                nextStates = sendForward(p.first);
            } else {
                nextStates = sendBack(p.first);
            }

            for (const auto& next : nextStates) {
                int myPos = coor(next.first);
                if (dists[myPos] >= ZERO_FLOAT) continue;

                pq.push({next.first, p.second + next.second});
            }

        }

        return -1.0;
        

    }

    double minTime(int n, int k, int m, vector<int>& time, vector<double>& mul) {
        this->n = n, this->k = k, this->m = m;
        times = time;
        mults = mul;

        double ans = dijkstra();
        return ans;
    }



    
};

int main() {
    Solution sol;

    int n = 12;
    int k = 5;
    int m = 4;
    vector<int> time = {1,2,3,4,5,6,7,8,9,10,11,12};
    vector<double> mul = {1,2,3,4};

    cout << sol.minTime(n, k, m, time, mul) << endl;
}