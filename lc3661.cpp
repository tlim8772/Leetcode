#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// annoying dp
// just need to note that robots range cannot contain another robota
// robot can either shoot left or right
// if robot shoot right, when recursing on the next robot, some of the walls to its left 
// may have been cleared

class Solution {
public:
    int NUM_WALLS;
    unordered_map<int, int> store;

    inline ll coor(int idx, int offset) {
        return (ll) idx * NUM_WALLS + offset;
    }

    // returns the index to the first elem >= key, or arr.len if does not exist
    int ceiling(int key, const vector<int>& arr) {
        if (arr.size() == 0) return 0;

        int s = 0, e = arr.size() - 1;
        while (s < e) {
            int m = (s + e) >> 1;
            if (arr[m] >= key) {
                e = m;
            } else {
                s = m + 1;
            }
        }
        return (arr[s] >= key) ? s : arr.size();
    }

    // returns the index to the last elem <= key or - 1 if does not exist
    int flooring(int key, const vector<int>& arr) {
        if (arr.size() == 0) return -1;

        int s = 0, e = arr.size() - 1;
        while (s < e) {
            int m = (s + e + 1) >> 1;
            if (arr[m] <= key) {
                s = m;
            } else {
                e = m - 1;
            }
        }
        return (arr[s] <= key) ? s : -1;
    }


    vector<pair<int,int>> getSortedRobotsWithDist(const vector<int>& robots, const vector<int>& distance) {
        vector<pair<int,int>> robotsWithDist;
        for (int i = 0; i < robots.size(); i++) {
            robotsWithDist.emplace_back(robots[i], distance[i]);
        }
        sort(robotsWithDist.begin(), robotsWithDist.end(), [](const pair<int,int>& p1, const pair<int,int>& p2) { return p1.first < p2.first; });
        return robotsWithDist;
    } 

    // {robot pos, robot left lim, robot right lim}
    vector<array<int,3>> getSortedRobotsWithLeftRight(const vector<pair<int,int>>& robotsWithDist) {
        vector<array<int,3>> out;
        for (int i = 0; i < robotsWithDist.size(); i++) {
            int leftLim = (i == 0) ? -2e9 : robotsWithDist[i - 1].first + 1;
            int rightLim = (i == robotsWithDist.size() - 1) ? 2e9 : robotsWithDist[i + 1].first - 1;

            const auto& [pos, dist] = robotsWithDist[i];
            int left = max(leftLim, pos - dist);
            int right = min(rightLim, pos + dist);

            out.push_back({pos, left, right});
        }
        return out;
    }

    // remove walls directly on some robot as they will be removed regardless of whether the robot 
    // shoots left or right
    vector<int> getSortedWallsNotDirectlyOnRobot(const vector<int>& robots, const vector<int>& walls) {
        set<int> robotSet(robots.begin(), robots.end());
        vector<int> out;
        for (int wall : walls) {
            if (robotSet.contains(wall)) continue;
            out.push_back(wall);
        }
        sort(out.begin(), out.end());
        return out;
    }

    // {l1, r1, l2, r2}
    // if the range is invalid then r < l
    // if robot shoot right cannot hit any wall, l2 is the next offset
    vector<array<int,4>> getRobotWithLeftRightWall(const vector<array<int,3>>& robotsWithLeftRight, const vector<int>& walls) {
        vector<array<int,4>> out;
        for (const array<int,3>& r : robotsWithLeftRight) {
            out.push_back({
                ceiling(r[1], walls),
                flooring(r[0], walls),
                ceiling(r[0], walls),
                flooring(r[2], walls)
            });
        }
        return out;
    }

    // offset is the index of the eftmost wall that has not been broken
    // the position of this wall can be < pos of current robot
    // but also can be > pos of current robot
    // INVARIANT
    // if offset is to the right of the robot, it is the 1st wall to the right of this robot
    // i.e offset == l2
    // if offset is to the left, there cannot be another robot in betwee offset and this robot
    int dp(int idx, int offset, const vector<array<int,4>>& robotsWithLeftRightWall) {
        if (idx == robotsWithLeftRightWall.size() || offset == NUM_WALLS) {
            return 0;
        } 

        ll pos = coor(idx, offset);
        if (store.contains(pos)) {
            return store[pos];
        }

        const auto [l1, r1, l2, r2] = robotsWithLeftRightWall[idx];

        int leftWalls = 0, leftAns = 0;
        if (l1 <= r1) {
            if (offset <= r1) {
                leftWalls = r1 - max(offset, l1) + 1;
            }
        }
        leftAns = leftWalls + dp(idx + 1, max(offset, l2), robotsWithLeftRightWall);

        int rightWalls = 0;
        if (l2 <= r2) {
            rightWalls = r2 - l2 + 1;
        }
        int rightAns = rightWalls + dp(idx + 1, r2 < l2 ? l2 : r2 + 1, robotsWithLeftRightWall);

        return store[pos] = max(leftAns, rightAns);
    }

    

   

    

    int maxWalls(vector<int>& robots, vector<int>& distance, vector<int>& walls) {
        vector<pair<int,int>> robotsWithDist = getSortedRobotsWithDist(robots, distance);
        vector<array<int,3>> robotsWithLeftRight = getSortedRobotsWithLeftRight(robotsWithDist);
        vector<int> wallsNotDirectlyOnRobot = getSortedWallsNotDirectlyOnRobot(robots, walls);
        vector<array<int,4>> robotsWithLeftRightWall = getRobotWithLeftRightWall(robotsWithLeftRight, wallsNotDirectlyOnRobot);
        NUM_WALLS = wallsNotDirectlyOnRobot.size();
        
        /*for (int w : wallsNotDirectlyOnRobot) {
            cout << w << " ";
        }
        cout << endl;
        
        for (array<int,4> arr : robotsWithLeftRightWall) {
            cout << arr[0] << " " << arr[1] << " " << arr[2] << " " << arr[3] << endl;
        }*/

        int res = dp(0, 0, robotsWithLeftRightWall);
        int ans = walls.size() - wallsNotDirectlyOnRobot.size() + res;
        //cout << ans << endl;

        return ans;

        
    }
};


int main() {
    Solution sol;

    vector<int> robots = {14,59,57,85,58,5,55,28,19,56,33,11,40,51,71,78,70,1,87,92,39,72,83,53,65,62,94,75,10,3,8,31,22,18,7,50,68,25,44,76,60,88,41,90,42,95,36,69,24,20,89,67,29,21,45,13,16,4,47,2,66,30,17,73,15,61,38,34,49,84,63,46,43,77,82,86,23,48,74,27,54,91,9,79,26,93,81,12,35,37,64,6,52,32,80};
    vector<int> distances = {10,2,9,3,3,3,6,1,8,6,6,7,7,10,5,3,4,4,3,1,9,6,5,9,8,3,1,1,7,6,2,7,4,3,7,1,8,1,2,2,4,6,3,7,4,4,5,7,2,7,1,3,9,1,2,8,9,2,10,9,5,6,4,10,9,9,8,4,8,1,4,6,3,1,1,4,4,7,9,10,6,8,10,5,4,1,7,2,5,8,2,3,10,1,6};
    vector<int> walls = {21,20,74,19,13,45,70,38,56,4,81,75,62,57,33,63,30,44,65,85,73,53,47,14,36,29,67,40,77,69,84,89,55,5,35,24,83,8,79,88,48,2,58,6,26,43,7,42,87,34,1,61,32,68,18,82,23,49,64,50,54,52,25,51,72,3,12,76,60,80,71,86,66,28,11,22,16,37,10,46,15,78,27,41,59,39,17,31,9};

    sol.maxWalls(robots, distances, walls);
}