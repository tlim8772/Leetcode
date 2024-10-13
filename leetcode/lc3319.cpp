#include <bits/stdc++.h>
using namespace std;

// just recursion

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
    vector<int> sizes;

    vector<int> helper(TreeNode *node) {
        if (node == nullptr) {
            return {true, 0};
        } else {
            vector<int> l = helper(node->left);
            vector<int> r = helper(node->right); 
            if (l[0] && r[0] && l[1] == r[1]) {
                sizes.push_back(1 + (l[1] << 1));
            }
            return {l[0] && r[0] && l[1] == r[1], l[1] + r[1] + 1};
        }
    }
    int kthLargestPerfectSubtree(TreeNode* root, int k) {
        helper(root);
        sort(sizes.begin(), sizes.end(), [] (int x, int y) {return x > y;});
        return (sizes.size() < k) ? -1 : sizes[k - 1];
    }
};

int main() {
    return 1;
}