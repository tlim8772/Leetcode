#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// trie + represent subtree as a hash
// do string hashing
// basically we have to find a way to hash the subtree of a node (not including the root of the subtree)
// if 2 trees have the same structure, the hash value should be the same

struct Hasher {
    const ll P = 29, M = 1e9 + 7;
    vector<ll> powMod;

    Hasher() {
        powMod.push_back(1);
        for (int i = 1; i <= 300000; i++) {
            powMod.push_back((powMod.back() * P) % M);
        }
    }

    ll hashString(string s) {
        ll ans = 0;
        for (int i = 0; i < s.size(); i++) {
            int val = (s[i] == '/') ? 27 : s[i] - 'a' + 1;
            ans += val * powMod[i];
            ans %= M;
        }
        return ans;
    }

    ll multiply(ll hash, int len) {
        return (hash * powMod[len]) % M;
    }

    ll add(ll hash1, ll val) {
        return (hash1 + val) % M;
    }
};

Hasher hasher;

struct Node {
    ll hash = 0, nextsHash = 0;
    int len = 0;
    string myString;
    map<string, Node*> nexts;

    Node() {}

    Node(const string& s): myString(s), len(s.size()) {}
};

struct Trie {
    vector<unique_ptr<Node>> store;

    Node* makeNode(const string& s) {
        store.emplace_back(new Node(s));
        return store.back().get();
    }

    Node* root = makeNode("/");
    unordered_map<ll, int> hashNodes;

    void insert(const vector<string>& path, int i, Node* curr) {
        if (i == path.size()) return;
        
        const string& s = path[i];
        Node*& ref = curr->nexts[s];
        if (ref == nullptr) ref = makeNode(s);
    
        insert(path, i + 1, ref);
    }

    void dfsLen(Node* curr) {
        int currlen = 0;
        for (auto& [k, v] : curr->nexts) {
            dfsLen(v);
            currlen += v->len;
        }
        curr->len = currlen + curr->myString.size();
    }

    void calculateHash(Node* curr) {
        ll currlen = 0, hash = 0;
        for (auto& [s, next] : curr->nexts) {
            calculateHash(next);
            hash = hasher.add(hash, hasher.multiply(next->hash, currlen));
            currlen += next->len;
            hash = hasher.add(hash, hasher.multiply(hasher.hashString("/"), currlen));
            currlen += 1;
        }
        hashNodes[hash] += 1;
        curr->nextsHash = hash;
        curr->hash = hasher.add(hash, hasher.multiply(hasher.hashString(curr->myString), currlen));
        
    }

    void collectRemaining(vector<string>& stack, vector<vector<string>>& store, Node* curr) {
        if (curr != root && curr->nexts.size() > 0 && hashNodes[curr->nextsHash] > 1) return;
        if (curr != root) stack.push_back(curr->myString);
            if (curr != root) store.push_back(stack);
            for (auto& [s, next] : curr->nexts) collectRemaining(stack, store, next);
        if (curr != root) stack.pop_back();
    }

    
};

class Solution {
public:
    vector<vector<string>> deleteDuplicateFolder(vector<vector<string>>& paths) {
        Trie trie;
        
        for (const vector<string>& path : paths) {
            trie.insert(path, 0, trie.root);
        }
        trie.dfsLen(trie.root);
        
        trie.calculateHash(trie.root);
    
        vector<string> stack;
        vector<vector<string>> store;
        trie.collectRemaining(stack, store, trie.root);

        return store;
    }
};

int main() {
    Solution sol;
    vector<vector<string>> paths = {{"a"}, {"c"}, {"d"}, {"a","b"}, {"c","b"}, {"d", "a"}};
    vector<vector<string>> ans = sol.deleteDuplicateFolder(paths);
    for (vector<string> p : ans) {
        for (string s : p) {
            cout << s << " ";
        }
        cout << endl;
    }

    //cout << hasher.hashString("ab") << endl;
}