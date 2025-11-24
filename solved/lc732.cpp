#include <bits/stdc++.h>
using namespace std;

// segtree that supports 
// insert a range [s, e]
// given the global range [S, E] find x s.t x is inside the most number of ranges

struct Node {
    // how many ranges that are exactly the [s,e] of this node
    int ranges = 0; 
    
    // max number of ranges covering a point in [s,e] of this node. the ranges must be s <= l <= r <= e
    int ma = 0; 
    
    Node *left = nullptr, *right = nullptr;

    static int getMax(Node *ptr) {
        return (ptr == nullptr) ? 0 : ptr->ma;
    }

    ~Node() {
        // delete nullptr is safe
        delete left;
        delete right;
    }
};

struct SegTree {
    int S = 0, E = 1e9;
    Node *root = nullptr;

    // invariant: s <= l <= r <= e
    Node *insert(Node *ptr, int s, int e, int l, int r) {
        int m = s + ((e - s) >> 1);
        if (ptr == nullptr) {
            ptr = new Node();
        }

        if (s == e || (s == l && e == r)) {
            ptr->ranges++;
        } else if (r <= m) {
            ptr->left = insert(ptr->left, s, m, l, r);
        } else if (l > m) {
            ptr->right = insert(ptr->right, m + 1, e, l, r);
        } else {
            ptr->left = insert(ptr->left, s, m, l, m);
            ptr->right = insert(ptr->right, m + 1, e, m + 1, r);
        }

        ptr->ma = ptr->ranges + max(Node::getMax(ptr->left), Node::getMax(ptr->right));

        if (s == S && e == E) {
            this->root = ptr;
        }
        
        return ptr;
    }

    ~SegTree() {
        delete root;
    }
};

class MyCalendarThree {
public:
    SegTree st;

    MyCalendarThree() {
        
    }
    
    int book(int startTime, int endTime) {
        st.insert(st.root, st.S, st.E, startTime, endTime - 1);
        return st.root->ma;
    }
};

int main() {
    MyCalendarThree cal;

    cout << cal.book(26, 35) << endl;
    cout << cal.book(26, 32) << endl;
    cout << cal.book(25, 32) << endl;
    cout << cal.book(18, 26) << endl;
}
