#include <bits/stdc++.h>
using namespace std;

// use 2 sets
// set1 contains the used seats
// set2 contains the intervals.
// when we remove a seat, we must remove its intervals 2, use set1 to find left, right and
// hence find the interval that must be removed.
// after we must insert the new interval i.e Interval{left, right}

struct Interval {
    int s, e, pos, gap;

    Interval(): s(-1), e(-1), pos(-1), gap(-1) {}

    Interval(int s, int e, int n): s(s), e(e) {
        if (s == -1 && e == n) {
            pos = 0;
            gap = (int) 1e9 + 1;
        } else if (s == -1) {
            pos = 0;
            gap = e;
        } else if (e == n) {
            pos = n - 1;
            gap = n - 1 - s;
        } else {
            pos = (e + s) >> 1;
            gap = (e - s) >> 1;
        }
    }

    static bool isValidRange(int s, int e, int n) {
        if (e - s <= 1) return false;
        return true;
    }
};

struct CmpInterval {
    bool operator()(const Interval& i1, const Interval& i2) const {
        if (i1.gap != i2.gap) {
            return i1.gap > i2.gap;
        }

        if (i1.pos != i2.pos) {
            return i1.pos < i2.pos;
        }

        if (i1.s != i2.s) {
            return i1.s < i2.s;
        }

        if (i1.e != i2.e) {
            return i1.e < i2.e;
        }

        return false;
    }
};

class ExamRoom {
public:
    int n;
    set<Interval, CmpInterval> pq;
    set<int> used;

    ExamRoom(int n): n(n) {
        pq.insert(Interval{-1, n, n});
    }

    bool validInterval(const Interval& i) {
        return (i.s == -1 || used.contains(i.s)) && (i.e == n || used.contains(i.e));
    }
    
    int seat() {
        Interval i = *pq.begin();
        pq.erase(pq.begin());

        //cout << i.s << " " << i.e << " " << i.pos << " " << i.gap << endl;

        int seat = i.pos;
        if (Interval::isValidRange(i.s, i.pos, n)) pq.insert(Interval{i.s, i.pos, n});
        if (Interval::isValidRange(i.pos, i.e, n)) pq.insert(Interval{i.pos, i.e, n});
        used.insert(seat);

        return seat;
    }
    
    void leave(int p) {
        used.erase(p);
        auto lb = used.lower_bound(p), ub = used.upper_bound(p);

        int s = (lb == used.begin()) ? -1 : *(--lb);
        int e = (ub == used.end()) ? n : *ub;
        pq.erase(Interval{s, p, n});
        pq.erase(Interval(p, e, n));
        pq.insert(Interval{s, e, n});

        
    }
};

int main() {
    ExamRoom er{10};

    cout << er.seat() << endl;
    cout << er.seat() << endl;
    cout << er.seat() << endl;
    er.leave(0);
    er.leave(4);
    //er.leave(9);
    cout << er.seat() << endl;
    cout << er.seat() << endl;
    cout << er.seat() << endl;
    cout << er.seat() << endl;

}

