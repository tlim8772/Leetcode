#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// binary search: Is it possible to select k points such that the min distance betweem any 2 points
// is >= dist

// arrange points in clockwise order. Then we store consectutive distance between point i and point i + 1
// for last point we loop back i.e manhatten distance between last point and 1st point


// Note that we must try all possible starting points, cannot anyhow assume optimal solution always start from a certain point
// To account that we have to loop back at point 0, we store in dists, 2 copies, and prefixDists calculate from the extended
// dists array.

// since k <= 25, we store prefix sums. From point i, we want to binary search to get closest next point j
// such that manhatten distance of point i, j is >= dist
// once we have the last point, we check distance with stating point. if fail, means cannot already, because we always
// take the nearest valid point



template <typename T>
void print(vector<T> arr) {
    for (T t : arr) {
        cout << t << endl;
    }
}

struct Pair {
    int x = 0, y = 0;
};

bool cmpxUp(const Pair p1, const Pair p2) {
    return p1.y < p2.y;
}

bool cmpyRight(const Pair p1, const Pair p2) {
    return p1.x < p2.x;
}

bool cmpxDown(const Pair p1, const Pair p2) {
    return p1.y > p2.y;
}

bool cmpyLeft(const Pair p1, const Pair p2) {
    return p1.x > p2.x;
}

int manDist(const Pair p1, const Pair p2) {
    return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}

int getRightMid(int s, int e) {
    int m = s + ((e - s) >> 1);
    if  (!((e - s + 1) % 2)) m ++;
    return m;
}

class Solution {
public:
    vector<Pair> xUp, yRight, xDown, yLeft;
    vector<Pair> allPoints;
    
    vector<int> dists;
    vector<ll> prefixDists;
    
    // get the points in clockwise order
    void process(int side, vector<vector<int>>& points) {
        for (vector<int>& p : points) {
            if (p[0] == 0) {
                xUp.push_back({p[0], p[1]});
            } else if (p[1] == side) {
                yRight.push_back({p[0], p[1]});
            } else if (p[0] == side) {
                xDown.push_back({p[0], p[1]});
            } else {
                yLeft.push_back({p[0], p[1]});
            }
        }

        sort(xUp.begin(), xUp.end(), cmpxUp);
        sort(yRight.begin(), yRight.end(), cmpyRight);
        sort(xDown.begin(), xDown.end(), cmpxDown);
        sort(yLeft.begin(), yLeft.end(), cmpyLeft);
        
        allPoints.insert(allPoints.end(), xUp.begin(), xUp.end());
        allPoints.insert(allPoints.end(), yRight.begin(), yRight.end());
        allPoints.insert(allPoints.end(), xDown.begin(), xDown.end());
        allPoints.insert(allPoints.end(), yLeft.begin(), yLeft.end());
    }


    void getConsecutiveDist() {
        for (int i = 1; i < allPoints.size(); i ++) {
            dists.push_back(manDist(allPoints[i], allPoints[i - 1]));
        }
        dists.push_back(manDist(allPoints.back(), allPoints[0]));

        // now push a 2nd time, to factor in looping
        int len = dists.size();
        for (int i = 0; i < len; i ++) {
            dists.push_back(dists[i]);
        }
    }

    void getPrefixDists() {
        prefixDists.push_back(dists[0]);
        for (int i = 1; i < dists.size(); i ++) {
            prefixDists.push_back((ll) dists[i] + prefixDists[i - 1]);
        }
    }

    ll getLen(int i, int j) {
        ll ans =  (i == 0) ? prefixDists[j] : prefixDists[j] - prefixDists[i - 1];
        return ans;
    }


    int binSearch(int i, ll minDist) {
        int s = i, e = dists.size() - 1;
        while (s < e) {
            int m = (s + e) >> 1;
            ll len = getLen(i, m);
            if (len < minDist) {
                s = m + 1;
            } else {
                e = m;
            }
        }

        return (getLen(i, s) >= minDist) ? s : -1;
    }

    // we choose index i
    bool check(int start, int k, ll minDist) {
        int curr = start, limit = start + allPoints.size() - 1;
        k --;
        while (k > 0 && curr < limit) {
            int next = binSearch(curr, minDist);
            if (next == -1 || next >= limit) {
                break;
            } else {
                k --;
                curr = next + 1;
            }
        }

        // check if we have chosen k points, and dist between last and start point is valid
        bool valid = k <= 0 && getLen(curr, start + allPoints.size() - 1) >= minDist;
        return valid;
    }

    int getMaxDistance(int k) {
        int s = 1, e = 2 * 1e9;
        while (s < e) {
            int m = getRightMid(s, e);
            
            bool can = false;
            for (int i = 0; i < allPoints.size() && !can; i ++) {
                can = check(i, k, m);
            }

            if (can) {
                s = m;
            } else {
                e = m - 1;
            }
        }
        return s;
    }

    
    int maxDistance(int side, vector<vector<int>>& points, int k) {
        process(side, points);
        getConsecutiveDist();
        getPrefixDists();
        
        //print(dists);
        //print(prefixDists);
        //for (Pair& p : allPoints) cout << p.x << " " << p.y << endl;
        // cout << check(1, 4, 67) << endl;

        int ans = getMaxDistance(k);

        return ans;
    }
};

int main() {
    Solution sol;
    
    int side = 92;
    vector<vector<int>> points = {{0,58},{37,92},{92,44},{73,92},{92,71},{0,75},{73,0},{58,0},{1,0}};
    int k = 4;
    
    cout << sol.maxDistance(side, points, k);
}