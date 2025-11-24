#include <vector>
#include <queue>
#include <iostream>
#include <unordered_map>
#include <algorithm>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class TreeNode2 {
public:
    TreeNode2* left;
    TreeNode2* right;
    int sum;
    int weight;

    TreeNode2() {
        left = nullptr;
        right = nullptr;
        sum = 0;
        weight = 0;
    }

    static int getSum(TreeNode2* node) {
        return (node == nullptr) ? 0 : node->sum;
    }

    static int getWeight(TreeNode2* node) {
        return (node == nullptr) ? 0 : node->weight;
    }

    static TreeNode2* build(TreeNode* node) {
        if (node == nullptr) {
            return nullptr;
        } else {
            TreeNode2* left = build(node->left);
            TreeNode2* right = build(node->right);
            TreeNode2* res = new TreeNode2();
            res->left = left;
            res->right = right;
            res->sum = getSum(left) + getSum(right) + node->val;
            res->weight = getWeight(left) + getWeight(right) + 1;
            return res;
        }
    }
};

class Solution {
    int helper(TreeNode2* node) {
        if (node == nullptr) {
            return 0;
        } else if (node->sum < node->weight) {
            // whatever you do, you still gotta add in the needed coins into this node, to distribute to the subtree rooted at this node
            return node->weight - node->sum + helper(node->left) + helper(node->right);
        } else if (node->sum > node->weight) {
            // whatever you do, you gotta transfer ALL the excess coins to the parent node, no choice
            return node->sum - node->weight + helper(node->left) + helper(node->right);
        } else {
            return helper(node->left) + helper(node->right);
        }
    }

     int distributeCoins(TreeNode* root) {
        TreeNode2* root2 = TreeNode2::build(root);
        return helper(root2);
    }
};