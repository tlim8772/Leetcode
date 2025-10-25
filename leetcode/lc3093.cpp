#include <bits/stdc++.h>
using namespace std;

// simple trie problem.
// for each node store the 'best' result, 
// i.e the smallest (lengtf of string with this suffix, pos of the string in array).

struct Node {
    pair<int,int> best = {999999, 999999};
    array<Node*, 26> nexts;

    Node() {
        nexts.fill(nullptr);
    }
};

struct Trie {
    vector<unique_ptr<Node>> store;
    Node* makeNode() {
        store.emplace_back(new Node());
        return store.back().get();
    }

    Node *root = makeNode();

    void insert(const string& s, int i, int pos, Node* curr) {
        if (i == -1) {
            curr->best = min(curr->best, {s.size(), pos});
            return;
        }
        char c = s[i];
        Node*& ref = curr->nexts[c - 'a'];
        if (ref == nullptr) ref = makeNode();
        insert(s, i - 1, pos, ref);
        
        curr->best = min(curr->best, ref->best);
    }

    int query(const string& s, int i, Node* curr) {
        if (i == -1) return curr->best.second;
        char c = s[i];
        Node *next = curr->nexts[c - 'a'];
        if (next == nullptr) return curr->best.second;
        return query(s, i - 1, next);
    }
};

class Solution {
public:
    vector<int> stringIndices(vector<string>& wordsContainer, vector<string>& wordsQuery) {
        Trie trie;
        for (int i = 0; i < wordsContainer.size(); i++) {
            trie.insert(wordsContainer[i], wordsContainer[i].size() - 1, i, trie.root);
        }

        vector<int> out;
        for (const auto& s : wordsQuery) {
            int ans = trie.query(s, s.size() - 1, trie.root);
            //cout << ans << endl;
            out.push_back(ans);
        }

        return out;
    }
};

int main() {
    Solution sol;
    vector<string> c1 = {"abcdefgh","poiuygh","ghghgh"};
    vector<string> c2 = {"acbfgh"};
    sol.stringIndices(c1, c2);
};

