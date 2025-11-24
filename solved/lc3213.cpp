#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

// use trie and dp, we use trie to avoid having to hash extremely long strings

template <typename T>
void print(vector<T> arr) {
    for (T t: arr) {
        cout << t << endl;
    }
    //cout << endl;
}

class Trie {
public:
    char c;
    bool end = false;
    int cost = 999999999;
    unordered_map<char, Trie*> children;

    Trie(char c) {
        this->c = c;
    }

    // trie is the parent node, index points to the next char we want to go
    void insert(int index, const string& s, int cost) {
        if (index == s.size()) {
            this->end = true;
            this->cost = min(this->cost, cost);
            return;
        }
        
        if (children.find(s[index]) == children.end()) {
            children[s[index]] = new Trie(s[index]);
        }
        children[s[index]]->insert(index + 1, s, cost);  
    }

    bool exist(int index, string& s) {
        if (index == s.size()) return true;
        else if (children.find(s[index]) == children.end()) return false;
        else return children[s[index]]->exist(index + 1, s);
    }
    
};

class Solution {
public:
    vector<int> dp;
    int null = 1000000000;
    Trie *root = new Trie('#');

    int helper(string& s, int index, Trie *trie) {
        if (index == s.size()) return 0;
        else if (dp[index] != null) return dp[index];
        else {
            int best = 999999999;
            for (int i = 0; i < s.size() - index; i ++) {
                auto it = trie->children.find(s[index + i]);
                if (it == trie->children.end()) break;
                else {
                    trie = it->second;
                    if (trie->end) {
                        best = min(best, trie->cost + helper(s, index + i + 1, root));
                    }
                }
            }
            dp[index] = best;
            return best;
        }
    }

    int minimumCost(string target, vector<string>& words, vector<int>& costs) {
        dp = vector(target.size(), null);
        for (int i = 0; i < words.size(); i ++) {
            root->insert(0, words[i], costs[i]);
        }
        int ans = helper(target, 0, root);
        return (ans >= 999999999) ? -1 : ans;
    }
};

int main() {
    Solution sol;
    string target = "abcdef";
    vector<string> words = {"zzzz"};
    vector<int> costs = {100,1,1,10,5};
    
    cout << sol.minimumCost(target, words, costs) << endl;
    //cout << sol.root->exist(0, words[0]);
}