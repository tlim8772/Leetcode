#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Node {
    int l = 0, r = 0, sum = 0, rangeCnt = 0;
};

// update: add or remove a range
// query: return length of union of ranges, overlapping ranges counted once only
// Node sum returns length of union of ranges that are contained in [s, e] only
// NOTE: only can remove ranges we added before
struct SegTree {
    int S, E, root = 0;
    vector<Node> tree; // as again tree[0] is the null node

    SegTree() {}

    SegTree(int S, int E): S(S), E(E), tree(1, Node()) {
        tree.reserve(5000000);
    }

    void reset() {
        root = 0;
        tree.clear();
        tree.push_back(Node());
    }

    inline int getMid(int s, int e) {
        return s + ((e - s) >> 1);
    }

    // insert a ra
    int updateRange(int n, int s, int e, int l, int r, int val) {
        // update n if curr node is null
        if (n == 0) {
            tree.push_back(Node());
            n = tree.size() - 1;
        }

        Node& curr = tree[n];
        
        if (s == l && e == r) {
            curr.rangeCnt += val;
            curr.sum = (curr.rangeCnt > 0) ? (e - s + 1) : tree[curr.l].sum + tree[curr.r].sum;
            return n;
        } else if (s == e) {
            curr.rangeCnt += val;
            curr.sum = (curr.rangeCnt > 0) ? 1 : 0;
            return n;
        } 
        
        int m = getMid(s, e);
        if (r <= m) {
            curr.l = updateRange(curr.l, s, m, l, r, val);
        } else if (l > m) {
            curr.r = updateRange(curr.r, m + 1, e, l, r, val);
        } else {
            curr.l = updateRange(curr.l, s, m, l, m, val);
            curr.r = updateRange(curr.r, m + 1, e, m + 1, r, val);
        }
        
        curr.sum = (curr.rangeCnt > 0) ? (e - s + 1) : tree[curr.l].sum + tree[curr.r].sum;
        return n;
    }

    // val is either 1 to add a range, -1 to remove a range, no other value
    void insert(int l, int r) {
        root = updateRange(root, S, E, l, r, 1);
    }

    void remove(int l, int r) {
        root = updateRange(root, S, E, l, r, -1);
    }

    inline int queryUnion() {
        return tree[root].sum;
    }
};

// y coor are the events, x coor are the ranges
struct Event {
    int time;
    bool side; // true if is start of square, false if end of square
    int s, e;

    bool operator<(const Event& other) {
        return time < other.time;
    }
};


// line sweep + segment tree that can add ranges and find length of union of ranges
// adding area corresponds to the length between 2 events.
// when processing a new event, first find dArea = (new event time - prev event time) * (len of union of x-ranges)
// event is from y coor, start of square (bottom y-coor) is a start event means we add the x-coor range
// bottom of square (top y-core) is end event means we remove the x-coor range
// with line sweep, we process the events accordingly
class Solution {
public:
    int minX = 2 * 1e9, maxX = 0;
    int minY = 2 * 1e9, maxY = 0;
    ll totalA = 0;
    SegTree st;
    vector<Event> events;


    void processEventsAndSegTree(const vector<vector<int>>& squares) {
        for (const vector<int>& s : squares) {
            minX = min(minX, s[0]);
            maxX = max(maxX, s[0] + s[2]);
            minY = min(minY, s[1]);
            maxY = max(maxY, s[1] + s[2]);
            
            int start = s[0], end = s[0] + s[2] - 1;
            events.push_back({s[1], true, start, end}); // remember to -1, as we count len = e - s, not e - s + 1
            events.push_back({s[1] + s[2], false, start, end});
        }

        sort(events.begin(), events.end());

        st = SegTree(minX, maxX);

        //cout << minY << " " << maxY << endl;
    }

    ll totalArea() {
        ll area = 0;

        int stime = events[0].time;
        int ptr = 0;
        while (ptr < events.size() && events[ptr].time == stime) {
            st.insert(events[ptr].s, events[ptr].e); // earliest event have to be start of square events
            ptr ++;
        }

        while (ptr < events.size()) {
            int nstime = events[ptr].time;
            int ylen = nstime - stime;
            int xlen = st.queryUnion();
            
            area += (ll) xlen * ylen;

            stime = nstime;
            while (ptr < events.size() && events[ptr].time == stime) {
                Event& e = events[ptr];
                if (e.side) {
                    st.insert(e.s, e.e);
                } else {
                    st.remove(e.s, e.e);
                }
                ptr ++;
            }
        }

        totalA = area;

        return area;
    }


    // we do not need to binary search. We know the yLimit must lie between 2 events
    // we have the curr area, if adding the new area exceeds target, we know between these 2 events
    // the length of union of x-coor ranges is fixed, we adjust dY = diff / len(union of x range)
    double getY() {
        st.reset();

        double target = (double) totalA / 2;
        double area = 0;

        int stime = events[0].time;
        int ptr = 0;
        
        //if (stime > ylimit) return 0;

        while (events[ptr].time == stime) {
            st.insert(events[ptr].s, events[ptr].e);
            ptr ++;
        }

        while (ptr < events.size()) {
            int nstime = events[ptr].time;
            double ylim = nstime;
            double ylen = ylim - stime;
            int xlen = st.queryUnion();

            double prevA = area;
            area += ylen * xlen;

            stime = nstime;
            
            if (area < target) {
                while (ptr < events.size() && events[ptr].time == stime) {
                    Event& e = events[ptr];
                    if (e.side) {
                        st.insert(e.s, e.e);
                    } else {
                        st.remove(e.s, e.e);
                    }
                    ptr ++;
                }
            } else {
                double diff = target - area;
                double dy = diff / xlen;
                return stime + dy;
            }
            
        }

        return 0;
        
    }
   
    double separateSquares(vector<vector<int>>& squares) {
        processEventsAndSegTree(squares);
        totalArea();
        
        return getY();
    }
};

int main() {
    Solution sol;
    vector<vector<int>> squares = {{0,0,2}, {1,1,1}};
    
    sol.separateSquares(squares);
    cout << sol.separateSquares(squares) << endl;
}