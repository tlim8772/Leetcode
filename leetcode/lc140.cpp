#include <vector>
#include <unordered_map>
#include <iostream>
#include <string>
using namespace std;

template <typename T>
void print(vector<T> arr) {
    for (T t: arr) {
        cout << t << endl;
    }
    //cout << endl;
}

class Solution {
public:
    vector<string> store;
    vector<string> stack;
    unordered_map<string, bool> dict;
    int maxlen = 0;

    void storeRes() {
        string ans = "";
        for (int i = 0; i < stack.size(); i ++) {
            ans.append(stack[i]);
            if (i != stack.size() - 1) ans.append(" ");
        }
        store.push_back(ans);
    }

    void helper(int index, string& s) {
        if (index == s.size()) {
            storeRes();
            return;
        }
        else {
            string sub = "";
            for (int i = 0; i < min(maxlen, (int) s.size() - index); i ++) {
                sub.append(1, s[index + i]);
                if (dict.find(sub) != dict.end()) {
                    stack.push_back(sub);
                    helper(index + i + 1, s);
                    stack.pop_back();
                }
            }
        }
    }

    vector<string> wordBreak(string s, vector<string>& wordDict) {
        for (string& s : wordDict) {
            maxlen = max(maxlen, (int) s.size());
            dict[s] = true;
        }
        helper(0, s);
        return store;
    }

   
};

int main() {
    Solution sol;
    vector<string> wordDict = {"apple","pen","applepen","pine","pineapple"};
    string word ="pineapplepenapple";
    print(sol.wordBreak(word, wordDict));
}