#include <bits/stdc++.h>
using namespace std;

// key insight is that in the optimal courses taken, 
// we can reorder the courses such that last days is increasing
// Pf by induction. Suppose the course with tha latest end day is not at the last position, can simply swap
// places with the course at the last position

// this means we can sort the courses in increasing last day, and consider them in that order

// sort in increasing last days (i.e increasing deadline)
// invariant: at iteration i (from 0 to n - 1)
// we have the max num of tasks from sorted coures[0 to i]
// and also the minimum total days among all possile configuration with maximum number of courses
// and after that, maximise the value of the longest course 
// when we consider course i + 1
// if can safely add i + 1, good, invariant is still maintain for iteration i + 1 (because if lesser, then we can reduce the
// total days for courses 0 to i)

// if cannot, check longest course taken so far, if is longer the duraton of course[i + 1] then replace with course i + 1
// when swapping, suppose it is not the shortest total time, then we can reduce the total time for iteration i, contradiction
// suppose longest course is not optimal, clearly that solution must contain course i + 1, if not previous result is not optimal
// in that case the longest course is in 0 ... i , which means previous result is not optimal

// interesting greedy, in the sense that we cannot know the optimal choice, until we know the optimal choice of the preceding prefix
// in the sense it is dp, but with better decision making
class Solution {
public:
    int scheduleCourse(vector<vector<int>>& courses) {
        priority_queue<int, vector<int>, less<int>> pq;
        sort(courses.begin(), courses.end(), [](vector<int>& a, vector<int>& b) {return a[1] < b[1];});

      
        int total = 0;
        for (vector<int>& c : courses) {
            if (c[0] > c[1]) continue;

            if (total + c[0] <= c[1]) {
                total += c[0];
                pq.push(c[0]);
            } else {
                int longest = pq.top();
                if (longest > c[0]) {
                    total = total - longest + c[0];
                    pq.pop();
                    pq.push(c[0]);
                }
            }
        }
        return pq.size();


    }
};

int main() {
    vector<vector<int>> cs = {{100,200}, {200,1300}, {1000,1250}, {2000,3200}};
    Solution sol;
    cout << sol.scheduleCourse(cs);

}