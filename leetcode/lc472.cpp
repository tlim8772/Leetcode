#include <vector>
#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

template <typename T>
void print(vector<T> arr) {
    for (T t: arr) {
        cout << t << endl;
    }
    //cout << endl;
}

// This solution is perfectly valid too

/*class Solution {
public:
    // max length of any string is 30
    // if dp[string] <= 0, this means, cannot be broken up into smaller words
    unordered_map<string, int> dp;
    unordered_map<string, bool> dict;
    int maxlen = 0;

    int helper(string& s, int index) {
        //if (s.size() == 30 && s[29] == 'z') cout << s << " " << index << endl;
        string sub = s.substr(index, s.size() - index);
        if (index == s.size()) return 0;
        else if (dp.find(sub) != dp.end()) return dp[sub];
        else {
            string temp = "";
            int maxRes = -999999999;
            for (int i = 0; i < min(maxlen, (int) s.size() - index); i ++) {
                temp.append(1, s[index + i]);
                if (dict.find(temp) != dict.end()) {
                    // it can be that subtr from index + i + 1 onwards cannot be broken up
                    maxRes = max(maxRes, 1 + helper(s, index + i + 1));
                }
            }
            dp[sub] = maxRes;
            return maxRes;
        }
    }

    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        vector<string> ans;
        for (string& s : words) {
            maxlen = max(maxlen, (int) s.size());
            dict[s] = true;
        }
        for (string& s : words) {
            int breakUp = helper(s, 0);
            if (breakUp > 1) {
                cout << s << endl;;
                //ans.push_back(s);
            }
        }
        cout << maxlen << endl;
        string str = "aaaaaaaaaaaaaaaaaaaaaaaaa";
        //cout << words[30] << endl;
        cout << helper(str, 0);
        return ans;
    }
}; */

class Solution {
public:
    // max length of any string is 30
    // if dp[string] <= 0, this means, cannot be broken up into smaller words
    //unordered_map<string, int> dp;

    // we get TLE when we used a hash table as dp
    // i,e hash the substring, apparently it takes MUCH longer
    vector<vector<int>> dp;
    unordered_map<string, bool> dict;
    int null = -1500000000;
    int maxlen = 0;

    int helper(string& s, int index, int word) {
        if (index == s.size()) return 0;
        else if (dp[word][index] != null) return dp[word][index];
        else {
            string temp = "";
            int best = -999999999;
            for (int i = 0; i < min(maxlen, (int) s.size() - index); i ++) {
                temp.append(1, s[index + i]);
                if (dict.find(temp) != dict.end()) best = max(best, 1 + helper(s, index + i + 1, word)); // if the entire substring is a word in dict, this line will take this into
                                                                                                         // account
            }
            dp[word][index] = best;
            return best;
        }
    }

    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        vector<string> ans;
        dp = vector(words.size(), vector(30, null));
        for (string& s : words) {
            maxlen = max(maxlen, (int) s.size());
            dict[s] = true;
        }
        for (int i = 0; i < words.size(); i ++) {
            string& s = words[i];
            int breakUp = helper(s, 0, i);
            if (breakUp > 1) ans.push_back(s);
        }
        return ans;
    }
};

int main() {
    vector<string> words = {"a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa","aaaaaaaaaaa","aaaaaaaaaaaa","aaaaaaaaaaaaa","aaaaaaaaaaaaaa","aaaaaaaaaaaaaaa","aaaaaaaaaaaaaaaa","aaaaaaaaaaaaaaaaa","aaaaaaaaaaaaaaaaaa","aaaaaaaaaaaaaaaaaaa","aaaaaaaaaaaaaaaaaaaa","aaaaaaaaaaaaaaaaaaaaa","aaaaaaaaaaaaaaaaaaaaaa","aaaaaaaaaaaaaaaaaaaaaaa","aaaaaaaaaaaaaaaaaaaaaaaa","aaaaaaaaaaaaaaaaaaaaaaaaa","aaaaaaaaaaaaaaaaaaaaaaaaaa","aaaaaaaaaaaaaaaaaaaaaaaaaaa","aaaaaaaaaaaaaaaaaaaaaaaaaaaa","aaaaaaaaaaaaaaaaaaaaaaaaaaaaa","aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"};
    Solution sol;
    print(sol.findAllConcatenatedWordsInADict(words));

}