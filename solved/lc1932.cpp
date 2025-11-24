#include <bits/stdc++.h>
using namespace std;

// cannot have multiple leaves with the same val. Because the merging op preserves the parent of the leave
// if can merge, the same value has 2 different parents

// if a root val has a matching leaf, then must merge, otherwise we have 2 nodes with the same value in
// the hypotheised BST

// so it means, the merging is like a tree structure, the root can only match with 1 leave, a valid BST
// means a tree like merging
 
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};




class Solution {
public:
    unordered_map<int, TreeNode*> leftLeaves;
    unordered_map<int, TreeNode*> rightLeaves;
    set<int> values;

    bool process(vector<TreeNode*>& trees) {
        for (TreeNode* root : trees) {
            TreeNode* l = root->left;
            if (root->left != nullptr && !leftLeaves.contains(l->val) && !rightLeaves.contains(l->val)) {
                leftLeaves[l->val] = root;
            } else if (root->left != nullptr) {
                return false;
            }

            TreeNode* r = root->right;
            if (root->right != nullptr && !leftLeaves.contains(r->val) && !rightLeaves.contains(r->val)) {
                rightLeaves[r->val] = root;
            } else if (root->right != nullptr) {
                return false;
            }

            values.insert(root->val);
            if (root->left != nullptr) values.insert(root->left->val);
            if (root->right != nullptr) values.insert(root->right->val);
        }
        return true;
    }

    int getLeftmost(TreeNode* t) {
        return (t->left == nullptr) ? t->val : getLeftmost(t->left);
    }

    int getRightmost(TreeNode* t) {
        return (t->right == nullptr) ? t->val : getRightmost(t->right);
    }

    // check if t is a BST, and all its values are in (s, e)
    bool check(TreeNode* t, int s, int e) {
        if (t == nullptr) return true;
        if (t->val <= s || t->val >= e) return false;

        return check(t->left, s, t->val) && check(t->right, t->val, e);
    
    }

    int size(TreeNode* t) {
        return (t == nullptr) ? 0 : 1 + size(t->left) + size(t->right);
    }

    // return true if TreeNode is the root, i.e has no leaves matching the value of the root
    // or successfully merged
    // false otherwise
    bool merge(TreeNode* root) {
        char side = 'x';
        TreeNode* p;
        if (leftLeaves.contains(root->val)) {
            side = 'l';
            p = leftLeaves[root->val];
        } else if (rightLeaves.contains(root->val)) {
            side = 'r';
            p = rightLeaves[root->val];
        } else {
            return true;
        }

        if (side == 'l') {
            p->left = root;
        } else {
            p->right = root;
        }

        return true;
    }

  
    TreeNode* canMerge(vector<TreeNode*>& trees) {
        bool res = process(trees);
        if (!res) return nullptr;

        int pcnt = 0;
        TreeNode* top = nullptr;
        for (TreeNode* t : trees) {
            if (!leftLeaves.contains(t->val) && !rightLeaves.contains(t->val)) {
                pcnt++;
                top = t;
            } else {
                bool res2 = merge(t);
                if (!res2) return nullptr;
            }
        }

        if (pcnt > 1 || pcnt < 1) {
            return nullptr;
        } else {
            bool valid = check(top, 0, 999999999);
            int num = size(top);

            if (valid && num == values.size()) {
                return top;
            } else {
                return nullptr;
            }
            
        }
    }
};