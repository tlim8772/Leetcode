#include <bits/stdc++.h>
using namespace std;

// there is a bounding circle iff the robot positions form a cycle
// if there is net displacement, then robot cannot be bounded

// but it can be the cyle takes going through the instructions
// multiple times
// eg GL
// so we check the direction we are facing after executing all the instructions
// if it is different then ans is also true, regardless of the displacement
// think about it

class Solution {
public:
    bool isRobotBounded(string instructions) {
        // clockwise direction, north east south west
        vector<pair<int,int>> dirs = {{0,1},{1,0},{0,-1},{-1,0}};
        int currDir = 0;
        
        pair<int,int> displacement = {0,0};

        for (char c : instructions) {
            if (c == 'G') {
                displacement.first += dirs[currDir].first;
                displacement.second += dirs[currDir].second;
                cout << displacement.first << " " << displacement.second << endl;
            } else if (c =='L') {
                currDir = (currDir - 1 + 4) % 4;
            } else {
                currDir = (currDir + 1) % 4;
            }
        }

        if ((displacement.first == 0 && displacement.second == 0) || currDir != 0) {
            return true;
        } else {
            return false;
        }


    }
};