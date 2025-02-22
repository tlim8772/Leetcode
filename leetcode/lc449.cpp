#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    TreeNode(int x, TreeNode* l, TreeNode* r): val(x), left(l), right(r) {}
};


//   2
//  1 3
// 
// string structure <left node><right node>,<len of left node>,<len of right node>,val
// no comma between left_node_string and right_node_string
class Codec {
public:
    // returns the len of the encode string, not including the provided string to append to.
    int helper_serialise(string& store, TreeNode* node) {
        int original_len = store.size();
        if (node == NULL) return 0;

        int left = helper_serialise(store, node->left);
        int right = helper_serialise(store, node->right);
        store += "," + to_string(left) + "," + to_string(right) + "," + to_string(node->val);
        return store.size() - original_len;
    }

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string str = "";
        helper_serialise(str, root);
        return str;
    }

    TreeNode* helper_deserialise(string& store, int s, int e) {
        //cout << store.substr(s, e - s + 1);
        int val, left_len, right_len;

        int p1 = e;
        int p2 = e;
        
        while (store[p2] != ',') p2 --;
        //cout << "val: " << store.substr(p2 + 1, p1 - p2) << endl;
        val = stoi(store.substr(p2 + 1, p1 - p2));

        p1 = p2 - 1;
        p2 = p1;
        while (store[p2] != ',') p2 --;
        //cout << "right_len" << endl;
        right_len = stoi(store.substr(p2 + 1, p1 - p2));

        p1 = p2 - 1;
        p2 = p1;
        while (store[p2] != ',') p2 --;
        //cout << "left_len" << endl;
        left_len = stoi(store.substr(p2 + 1, p1 - p2));

        TreeNode* node = new TreeNode(val);
        node->left = (left_len == 0) ? NULL : helper_deserialise(store, s, s + left_len - 1);
        node->right = (right_len == 0) ? NULL : helper_deserialise(store, s + left_len, s + left_len + right_len - 1);

        return node;
    }
    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if (data.size() == 0) return NULL;
        return helper_deserialise(data, 0, data.size() - 1);
    }
};

TreeNode* generate(int s, int e) {
    if (s == e) return new TreeNode(s);
    if (s > e || e < s) return NULL;

    int m = (s + e) >> 1;
    TreeNode *l = generate(s, m - 1);
    TreeNode *r = generate(m + 1, e);
    return new TreeNode(m, l, r);

}

string test(TreeNode* t) {
    if (t == NULL) return "NULL";

    return test(t->left) +","+ to_string(t->val) +","+ test(t->right);
}


int main() {
    Codec codec;
    TreeNode* root = new TreeNode(2, new TreeNode(1, new TreeNode(0), NULL), new TreeNode(3));
   
    string s = codec.serialize(root);
    cout << s << endl;
    TreeNode* t = codec.deserialize(s);
    cout << test(t) << endl;
}