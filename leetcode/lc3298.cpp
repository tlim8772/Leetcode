#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> targetCount = vector(26, 0);

    bool check(vector<int>& arr) {
        return accumulate(arr.begin(), arr.end(), true, [](bool a, int cnt) {return a && cnt <= 0;});
    }

    long long validSubstringCount(string word1, string word2) {
        for (char c : word2) {
            targetCount[c - 'a'] ++;
        }
        int left = 0;
        long long ans = 0;

        int s = 0;
        int e = 0;
        while (s < word1.size()) {
            if (check(targetCount)) {
                ans += word1.size() - e + 1;
                targetCount[word1[s] - 'a'] ++;
                s ++;
                continue;
            }
            
           

            while (e < word1.size()) {
                targetCount[word1[e] - 'a'] --;
                e ++;
                if (check(targetCount)) {
                    ans += word1.size() - e + 1;
                    targetCount[word1[s] - 'a'] ++;
                    break;
                }
            }
            s ++;

        }
        return ans;
    }
};

int main() {
    string word1 = "abcabc";
    string word2 = "aaabc";
    vector<int> arr = {0,0,0};
    cout << Solution().check(arr) << endl;
    cout << Solution().validSubstringCount(word1, word2) << endl;
}