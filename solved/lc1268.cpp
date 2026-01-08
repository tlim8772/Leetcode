#include <bits/stdc++.h>
using namespace std;

// sort products in increasing order.
// each trie node store the smallest 3 products whose words contain the path from root to this node
// as its prefix.

// when we search the word, we can immediately get the top 3 (or less) for each prefix

struct Node {
    set<int> words;
    array<Node*, 26> nexts{};
};

struct Trie {
    vector<Node> store;
    Node* root;

    Trie(int totalLen) {
        store.reserve(2 * totalLen);
        root = makeNode();
    }

    Node* makeNode() {
        store.emplace_back();
        return &store.back();
    }

    void insert(const string& word, int pos, int idx = 0, Node* curr = nullptr) {
        if (idx == 0) curr = root;

        auto& [words, nexts] = *curr;
        words.insert(pos);
        if (words.size() > 3) words.erase(--words.end());

        if (idx == word.size()) return;
        
        Node*& next = nexts[word[idx] - 'a'];
        if (next == nullptr) next = makeNode();
        insert(word, pos, idx + 1, next);
    }

    void search(const string& searchWord, vector<vector<int>>& result, int idx = 0, Node* curr = nullptr) {
        if (idx == 0) curr = root;

        auto& [words, nexts] = *curr;
        if (idx > 0) result.emplace_back(words.begin(), words.end());
        
        if (idx == searchWord.size()) return;
        Node* next = nexts[searchWord[idx] - 'a'];
        if (next == nullptr) {
            for (int i = idx; i < searchWord.size(); i++) result.emplace_back();
            return;
        }
        
        search(searchWord, result, idx + 1, next);
    }
};

class Solution {
public:
    vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
        int totalLen = 0;
        for (auto& s : products) totalLen += s.size();

        Trie trie{totalLen};
        sort(products.begin(), products.end());
        for (int i = 0; i < products.size(); i++) {
            trie.insert(products[i], i);
        }

        vector<vector<int>> result;
        trie.search(searchWord, result);

        vector<vector<string>> out;
        for (auto& arr : result) {
            vector<string> res;
            for (int x : arr) {
                res.push_back(products[x]);
            }
            out.push_back(res);
        }
        return out;
    }
};

int main() {
    Solution sol;
    
    vector<string> products = {"mobile","mouse","moneypot","monitor","mousepad"};
    string searchWord = "mouse";

    vector<vector<string>> out = sol.suggestedProducts(products, searchWord);
    for (auto& arr : out) {
        for (auto& s : arr) {
            cout << s << " ";
        }
        cout << endl;
    }
}