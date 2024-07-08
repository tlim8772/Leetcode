#include <vector>
#include <iostream>
using namespace std;

// act greedily, starting from 1st letter, find the lexicohraphical smallest char you can place
class Solution {
public:
    int cyclicDistance(char c1, char c2) {
        int x1 = c1 - 'a';
        int x2 = c2 - 'a';
        return min(abs(x2 - x1), 26 - max(x1, x2) + min(x1, x2));
    }

    string getSmallestString(string s, int k) {
        string out = s;
        for (int i = 0; i < s.size(); i ++) {
            for (int j = 0; j < 26; j ++) {
                int cost = cyclicDistance(s[i], j + 'a');
                if (cost <= k) {
                    out[i] = j + 'a';
                    k -= cost;
                    break;
                }
            }
        }
        return out;
    }
};

int main() {
    cout << Solution().getSmallestString("zbbz", 3);
}
