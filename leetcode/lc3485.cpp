#include <bits/stdc++.h>
using namespace std;

// trie question
// in each trie node store the len of prefix the node represents, and cnt: number of words containing this prefix
// also store bestK: longest len with at least k words starting with this prefix

struct Trie {
    int end = 0; // how many words end here
    int cnt = 0; // how many words contain this prefix
    int len = 0;
    int bestK = 0; // longest len with at least k words starting with this prefix
    
    vector<Trie*> next{26, nullptr};

    Trie() {}

    Trie(int len): len(len) {}

    void updateBestK(int k) {
        int best = (cnt >= k) ? len : 0;
        for (Trie *c : next) {
            if (c == nullptr) continue;
            best = max(best, c->bestK);
        }
        bestK = best;
    }

    void updateCnt() {
        int store = end;
        for (Trie *c : next) {
            if (c == nullptr) continue;
            store += c->cnt;
        }
        cnt = store;
    }

    void insert(const string& s, int ptr, int k) {
        if (ptr == s.size()) {
            this->end ++;
            this->updateCnt();
            this->updateBestK(k);
            return;
        }

        if (this->next.at(s[ptr] - 'a') == nullptr) {
            this->next[s[ptr] - 'a'] = new Trie(ptr + 1);
        }
        
        this->next[s[ptr] - 'a']->insert(s, ptr + 1, k);
        this->updateCnt();
        this->updateBestK(k);
    }

    // must ensure string is already inside
    // we do not delete nodes, just update the cnt 
    void remove(const string& s, int ptr, int k) {
        if (ptr == s.size()) {
            this->end --;
            this->updateCnt();
            this->updateBestK(k);
            return;
        }

        this->next[s[ptr] - 'a']->remove(s, ptr + 1, k);
        this->updateCnt();
        this->updateBestK(k);
    }
};

class Solution {
public: 
    vector<int> longestCommonPrefix(vector<string>& words, int k) {
        Trie* root = new Trie();
        vector<int> ans(words.size(), 0);

        for (string& s : words) {
            root->insert(s, 0, k);
        }

        //cout << root->next['r' - 'a']->next['u' - 'a']->next['n' - 'a']->bestK;

        for (int i = 0; i < words.size(); i ++) {
            root->remove(words[i], 0, k);
            ans[i] = root->bestK;
            root->insert(words[i], 0, k);
        }

        return ans;
    }

};

int main() {
    Solution sol;

    vector<string> words = {"ccd","adc","dba","bff","cbfae","fcae","cbbc"};
    int k = 3;

    vector<int> ans = sol.longestCommonPrefix(words, k);
    for (int x : ans) cout << x << endl;
}