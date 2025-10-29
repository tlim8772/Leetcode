#include <bits/stdc++.h>
using namespace std;

// a trie is a tree, so no need for dp.
// just traverse the trie, but with 2 wildcard, where we can check all edges instead of the edge matching s[i].

struct Node {
    array<Node*, 26> nexts{};
};

struct Trie {
    vector<unique_ptr<Node>> store;

    Node* makeNode() {
        store.emplace_back(new Node());
        return store.back().get();
    }

    Node *root = makeNode();

    void insert(const string& s, int i = 0, Node *curr = nullptr) {
        if (i == s.size()) return;
        if (i == 0) curr = root;
        Node *&ref = curr->nexts[s[i] - 'a'];
        if (ref == nullptr) ref = makeNode();
        insert(s, i + 1, ref);
    }

    bool query(const string& s, int i = 0, int wildcards = 2, Node *curr = nullptr) {
        if (i == 0) curr = root;
        if (i == s.size()) return true;
        
        array<Node*, 26> nexts = curr->nexts;
        for (int k = 0; k < 26; k++) {
            if (nexts[k] == nullptr) continue;
            
            bool same = (k == s[i] - 'a') ? query(s, i + 1, wildcards, nexts[k]) : false;
            if (same) return true;
            
            bool nosame = (k != s[i] - 'a' && wildcards > 0) ? query(s, i + 1, wildcards - 1, nexts[k]) : false;
            if (nosame) return true;
        }
        return false;
    }
};

class Solution {
public:
    vector<string> twoEditWords(vector<string>& queries, vector<string>& dictionary) {
        Trie trie;
        for (auto& s : dictionary) {
            trie.insert(s);
        }

        vector<string> out;
        for (auto& s : queries) {
            bool ans = trie.query(s);
            if (ans) out.push_back(s);
        }

        return out;
    }
};

int main() {
    Solution sol;
    vector<string> 
        queries = {"word","note","ants","wood"}, 
        dictionary = {"wood","joke","moat"},
        out = sol.twoEditWords(queries, dictionary);

    for (auto& s : out) {
        cout << s << endl;
    }
    
}

