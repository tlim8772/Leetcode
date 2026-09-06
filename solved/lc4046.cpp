#include <bits/stdc++.h>
using namespace std;

// use dijkstra.
// state is (r, c, prev_dir, turns_left).

// custom pq that lets you update the priority.
template <typename S, typename Hash>
struct updateable_priority_queue {
    vector<pair<int, S>> store;
    unordered_map<S, int, Hash> s_to_idx;

    int left(int p) { return (p << 1) + 1; }

    int right(int p) { return (p << 1) + 2; }

    int get_parent(int p) { return (p - 1) >> 1; }

    int bubble_up(int p) {
        if (p == 0) return -1;

        int par = get_parent(p);
        if (store[p].first >= store[par].first) return -1;

        s_to_idx[store[p].second] = par;
        s_to_idx[store[par].second] = p;
        swap(store[p], store[par]);
        return par;
    }

    int bubble_down(int p) {
        int l = left(p), r = right(p);
        // it is a complete binary tree, so we cannot have empty left and non-empty right.
        if (l >= store.size()) return -1;

        int min_prior = store[l].first;
        if (r < store.size()) {
            min_prior = min(min_prior, store[r].first);
        }
        if (store[p].first <= min_prior) return -1;
        
        // only go right when right exists and priority right < priority left
        if (r < store.size() && store[r].first < store[l].first) {
            s_to_idx[store[p].second] = r;
            s_to_idx[store[r].second] = p;
            swap(store[p], store[r]);
            return r;
        } else {
            s_to_idx[store[p].second] = l;
            s_to_idx[store[l].second] = p;
            swap(store[p], store[l]);
            return l;
        }
    }

    bool empty() {
        return store.size() == 0;
    }

    pair<int, S> pop() {
        if (store.size() == 0) throw std::out_of_range("priority queue is empty");

        auto s = store[0];
        s_to_idx.erase(s.second);
        if (store.size() == 1) {
            store.pop_back();
            return s;
        }

        store[0] = store.back();
        s_to_idx[store[0].second] = 0;
        store.pop_back();

        int p = 0;
        while (p != -1) p = bubble_down(p);

        return s;
    }

    optional<int> get_prior(S s) {
        auto it = s_to_idx.find(s);
        if (it == s_to_idx.end()) return nullopt;
        return store[it->second].first;
    }

    void add(int prior, S s) {
        auto it = s_to_idx.find(s);
        if (it != s_to_idx.end()) {
            int i = it->second;
            int prev = store[i].first;
            store[i].first = prior;

            if (prior < prev) {
                int p = i;
                while (p != -1) p = bubble_up(p);
            } else if (prior > prev) {
                int p = i;
                while (p != -1) p = bubble_down(p);
            }
        } else {
            s_to_idx[s] = store.size();
            store.emplace_back(prior, s);
            
            int p = store.size() - 1;
            while (p != -1) p = bubble_up(p);
        }
    }
};

struct state {
    // 0 <= r, c < 75
    // 0 <= prev_dir < 5
    // 0 <= turns_left <= 75
    int r, c, prev_dir, turns_left;

    bool operator==(const state& other) const noexcept {
        return r == other.r &&
               c == other.c &&
               prev_dir == other.prev_dir &&
               turns_left == other.turns_left;
    }
};

struct state_hash {
    std::size_t operator()(const state& s) const noexcept {
        std::size_t hash = s.r;
        hash = hash * 75 + s.c;
        hash = hash * 5 + s.prev_dir;
        hash = hash * 76 + s.turns_left;
        return hash;
    }
};

int get_dir_id(int dr, int dc) {
    // 1, 2, 3, 4 corresponds to up right down left.
    // 0 means no direction at all.
    if (dr == -1 && dc == 0) return 1;
    if (dr == 0 && dc == 1) return 2;
    if (dr == 1 && dc == 0) return 3;
    if (dr == 0 && dc == -1) return 4;
    throw invalid_argument("invalid direction vectors.");
}

int store[75][75][5][76];

void init(int R, int C, int k) {
    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            for (int p = 0; p < 5; p++) {
                for (int t = 0; t <= k; t++) {
                    store[r][c][p][t] = -1;
                }
            }
        }
    }
}
class Solution {
public:
    int minCost(vector<vector<int>>& grid, int k) {
        const int R = grid.size(), C = grid[0].size();
        const vector<pair<int,int>> dirs = {{-1,0}, {0,1}, {1,0}, {0,-1}};
        
        updateable_priority_queue<state, state_hash> pq;

        auto valid = [R, C] (int r, int c) {
            return r >= 0 && r < R && c >= 0 && c < C;
        };

        init(R, C, k);

        pq.add(grid[0][0], state{0, 0, 0, k});

        while (!pq.empty()) {
            auto [d, cur_state] = pq.pop();
            auto [r, c, prev_dir, turns_left] = cur_state;
            
            int& res = store[r][c][prev_dir][turns_left];
            if (res != -1) continue;
            res = d;

           
            if (r == R - 1 && c == C - 1) return d;

            for (auto [dr, dc] : dirs) {
                int nr = r + dr, nc = c + dc;
                if (!valid(nr, nc)) continue;

                int dir_id = get_dir_id(dr, dc);
                int turn_cost = prev_dir != 0 && prev_dir != dir_id;
                if (turn_cost > turns_left) continue;
                
                int new_d = d + grid[nr][nc];
                state new_state = {nr, nc, dir_id, turns_left - turn_cost};

                // this is imprtant.
                // if we have computed this state, it wont be in the pq,
                // so it will be inserted again if we don't have this line.
                if (store[nr][nc][dir_id][turns_left - turn_cost] != -1) continue;

                auto prev_prior = pq.get_prior(new_state);
                if (prev_prior && prev_prior.value() < new_d) continue;

                pq.add(d + grid[nr][nc], state{nr, nc, dir_id, turns_left - turn_cost});
            }
        }

        return -1;
    }
};

int main() {
    Solution sol;
    
    vector<vector<int>> grid = {{4,1,9}, {3,2,5}, {4,8,6}};
    int k = 2;

    int ans = sol.minCost(grid, k);
    cout << ans << endl;
}