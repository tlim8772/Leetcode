#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


struct Pair {
    int depth, node;
};

class Solution {
public:
    vector<Pair> parse(const string& traversal) {
        vector<Pair> out;
        int ptr = 0;

        while (ptr < traversal.size()) {
            Pair p = {0, 0};
            while (ptr < traversal.size() && traversal[ptr] == '-') {
                p.depth ++;
                ptr ++;
            }

            int s = ptr;
            while (ptr < traversal.size() && traversal[ptr] != '-') {
                ptr ++;
            }
            p.node = stoi(traversal.substr(s, ptr - s));
            
            out.push_back(p);
        }

        return out;
    }

    pair<TreeNode*, int> helper(int idx, const vector<Pair>& traversal) {
        if (idx == traversal.size()) {
            return {nullptr, idx};
        }

        TreeNode* t = new TreeNode(traversal[idx].node);
        int depth = traversal[idx].depth;

        // leaf node
        if (idx == traversal.size() - 1 || traversal[idx + 1].depth != depth + 1) {
            return {t, idx + 1};
        } 

        pair<TreeNode*, int> leftres = helper(idx + 1, traversal);
        int start = get<1>(leftres);

        pair<TreeNode*, int> rightres = {nullptr, start};
        if (start != traversal.size() && traversal[start].depth == depth + 1) {
            rightres = helper(start, traversal);
        }
        
        t->left = get<0>(leftres);
        t->right = get<0>(rightres);
        
        return {t, get<1>(rightres)};
    }
    

    TreeNode* recoverFromPreorder(string traversal) {
        vector<Pair> parsed = parse(traversal);
        pair<TreeNode*, int> res = helper(0, parsed);
        return get<0>(res);
    }
};

void debug(TreeNode *t, int depth) {
    if (t == nullptr) return;
    cout << string(depth, ' ') << t->val << endl;
    debug(t->left, depth + 1);
    debug(t->right, depth + 1);
}

int main() {
    Solution sol;
    string s = "1-2--3---4-5--6---7";

    //vector<Pair> arr = sol.parse(s);
    //for (Pair& p : arr) cout << p.depth << " " << p.node << endl;

    TreeNode *t = sol.recoverFromPreorder(s);
    debug(t, 0);
    //cout << t->right->val << endl;
    
}