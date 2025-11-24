#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// simple
// for each limit store all values with that limit
// take the top limit elements (eg. if limit = 5, take the top 5 elems)

struct Cmp {
    bool operator()(int a, int b) const {
        return a > b;
    }
};

class Solution {
public:
    long long maxTotal(vector<int>& value, vector<int>& limit) {
        vector<multiset<int, Cmp>> sets(value.size() + 1, multiset<int, Cmp>());

        for (int i = 0; i < value.size(); i++) {
            sets[limit[i]].insert(value[i]);
        }

        ll sum = 0;
        for (int i = 1; i <= value.size(); i++) {
            multiset<int, Cmp>& currSet = sets[i];

            int taken = 0;
            auto it = currSet.begin();
            while (it != currSet.end() && taken < i) {
                sum = sum + *it;
                it++;
                taken++;
            }
        }

        return sum;
    }
};

int main() {
    Solution sol;

    vector<int> value = {9268,39208,96286,48894,65613,29498,66878,22285,97780,46954,73678,91583,11483,87773,24175,63358,16139,77565,55083,2437,14879,45136,33030,90989,53546,19388,66195,74918,96077,1604,60554,26202,99442,73700,54894,48119,74846,49970,66215,68225,68347,78926,36346,43946,78879,78608,55494,71705,26202,61428,21870,91975,93664,92120,77296,14254,87086,3697,29840,6391,21010,83359,42784,12564,67117};
    vector<int> limit = {21,50,38,52,20,47,6,48,16,56,14,35,11,64,28,32,16,19,45,57,47,12,7,25,23,58,23,44,13,62,1,53,21,56,34,52,42,46,8,47,12,3,47,53,52,28,59,18,53,10,31,8,29,37,26,62,29,52,50,47,46,32,51,6,53};

    cout << sol.maxTotal(value, limit) << endl;
}

