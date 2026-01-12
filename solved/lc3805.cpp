#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// we calculate the (+ve) gap between 2 consecutive characters.
// i.e [f u s i o n] => [15, 24, 16, ..., ...]
// if 2 strings have the same gap array, then they are caesar equivalent.
// so use unordered_map<gap_array, int>.

// got this hash from ChatGpt
struct ArrayHash {
    size_t operator()(const vector<int>& a) const noexcept {
        uint64_t h = 0x9e3779b97f4a7c15ULL;

        for (int x : a) {
            uint64_t v = static_cast<uint64_t>(x);
            h ^= v + 0x9e3779b97f4a7c15ULL + (h << 6) + (h >> 2);
        }

        // final avalanche
        h ^= h >> 30;
        h *= 0xbf58476d1ce4e5b9ULL;
        h ^= h >> 27;
        h *= 0x94d049bb133111ebULL;
        h ^= h >> 31;

        return static_cast<size_t>(h);
    }
};

class Solution {
public:
    vector<int> makeGap(const string& s) {
        vector<int> out(s.size() - 1, 0);
        for (int i = 1; i < s.size(); i++) {
            out[i - 1] = (s[i] - s[i - 1] + 26) % 26;
        }
        return out;
    }
    
    long long countPairs(vector<string>& words) {
        unordered_map<vector<int>, int, ArrayHash> store;
        ll cnt = 0;
        for (string& s : words) {
            auto arr = makeGap(s);
            cnt += store[arr]++;          
        }
        return cnt;
    }
};

int main() {
    Solution sol;

    vector<string> words = {"ab", "aa", "za", "aa"};
    cout << sol.countPairs(words) << endl;
}