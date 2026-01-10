#include <bits/stdc++.h>
using namespace std;

// just use sparse segment tree.
// each node contains # integers covered in its assigned range, and # intervals spanning its range.
// if we modify its child, we recalculate #integers covered.
// if have > 0 covering integers, #of integers is e - s + 1, else is # integers covered in left child + 
// # of integers covered in right child.

struct Node {
    int covered_cnt = 0, interval_cnt = 0;
    Node *l = nullptr, *r = nullptr;

    static int get_covered_cnt(Node* n) {
        return (n == nullptr) ? 0 : n->covered_cnt;
    }

    static int get_interval_cnt(Node* n) {
        return (n == nullptr) ? 0 : n->interval_cnt;
    }
};

struct SegTree {
    vector<Node> alloc;
    int S = 1, E = (int) 1e9;
    Node *root = nullptr;

    SegTree() {
        alloc.reserve(5000000);
    }

    Node* makeNode() {
        alloc.emplace_back();
        return &alloc.back();
    }

    Node* add_range(int l, int r, int p = 0, int s = -1, int e = -1, Node* curr = nullptr) {
        if (p == 0) s = S, e = E, curr = root;
        
        if (curr == nullptr) curr = makeNode();
        
        if (s == l && e == r) {
            curr->covered_cnt = e - s + 1;
            curr->interval_cnt += 1;
            if (p == 0) root = curr;
            return curr;
        }

        int m = (s + e) >> 1;
        Node *&left = curr->l, *&right = curr->r;
        if (r <= m) {
            left = add_range(l, r, (p << 1) + 1, s, m, curr->l);
        } else if (l > m) {
            right = add_range(l, r, (p << 1) + 2, m + 1, e, curr->r);
        } else {
            left = add_range(l, m, (p << 1) + 1, s, m, curr->l);
            right = add_range(m + 1, r, (p << 1) + 2, m + 1, e, curr->r);
        }
        
        if (curr->interval_cnt == 0) {
            curr->covered_cnt = Node::get_covered_cnt(curr->l) + Node::get_covered_cnt(curr->r);
        }

        if (p == 0) root = curr;

        return curr;
    }


};

class CountIntervals {
public:
    SegTree st{};

    CountIntervals() {
        
    }
    
    void add(int left, int right) {
        st.add_range(left, right);
    }
    
    int count() {
        return Node::get_covered_cnt(st.root);
    }
};

int main() {
    CountIntervals sol;
    sol.add(2, 3);
    sol.add(7, 10);
    cout << sol.count() << endl;
    sol.add(5, 8);
    cout << sol.count() << endl;
}
