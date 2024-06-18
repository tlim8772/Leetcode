#include <iostream>
#include <queue>
#include <vector>
#include <functional>
using namespace std;


class Solution {
// due to cycling i.e x -> y -> x needs 2 cost, we have to consider parity in the state too, i,e time taken is odd or even

// suppose we are at a node at time 3, adjacent node is 6, we can cycle and reach that node at 6, if time is 2, not 3, can only 
// reach that node at 7
public:
    vector<vector<vector<int>>>* dp;

    // a functor is a class that overloads the () operator
    class Compare {
    public:
        bool operator()(vector<int>& a, vector<int>& b) {
            return a[2] > b[2];
        }
    };

    bool valid(int x, int y, vector<vector<int>>& matrix) {
        return (x < 0 || x >= matrix.size() || y < 0 || y >= matrix[0].size()) ? false : true;
    }

    bool checkStart(vector<vector<int>>& grid) {
        if (grid[0][1] <= 1) {
            return true;
        } else if (grid[1][0] <= 1) {
            return true;
        } 
        return false;
    }

    bool checkNotFilled(int r, int c, int parity) {
        return (*dp)[parity][r][c] == -1;
    }

    int minimumTime(vector<vector<int>>& grid) {
        dp = new vector(2, vector(grid.size(), vector(grid[0].size(), -1)));
        priority_queue<vector<int>, vector<vector<int>>, Compare> pq;
        pq.push({0, 0, 0});
        bool canCycle = checkStart(grid);
        while (!pq.empty()) {
            const vector<int>& node = pq.top();
            //cout << node[0] << " " << node[1] << " " << node[2] << endl;
            //pq.pop();
            int parity = node[2] % 2;
            int r = node[0];
            int c = node[1];
            int time = node[2];
            // cannot pop first, node is kinda a pointer to the 'top' element, if pop, element pointed too changes
            pq.pop();
            //cout << node[0] << " " << node[1] << " " << node[2] << endl;
            if ((*dp)[parity][r][c] == -1) {
                (*dp)[parity][r][c] = time;
                if (r == grid.size() - 1 && c == grid[0].size() - 1) {
                    break;
                }
                if (time == 0 && !canCycle) {
                    if (valid(r - 1, c, grid) && grid[r - 1][c] <= time + 1 && checkNotFilled(r - 1, c, parity)) {
                        pq.push({r - 1, c, time + 1});
                    } 
                    if (valid(r, c + 1, grid) && grid[r][c + 1] <= time + 1 && checkNotFilled(r, c + 1, parity)) {
                        pq.push({r, c + 1, time + 1});
                    } 
                    if (valid(r + 1, c, grid) && grid[r + 1][c] <= time + 1 && checkNotFilled(r + 1, c, parity)) {
                        pq.push({r + 1, c, time + 1});
                    } 
                    if (valid(r, c - 1, grid) && grid[r][c - 1] <= time + 1 && checkNotFilled(r, c - 1, parity)) {
                        pq.push({r , c - 1, time + 1});
                    }
                } else {
                    if (valid(r - 1, c, grid) && checkNotFilled(r - 1, c, parity)) {
                        if (grid[r - 1][c] <= time + 1) {
                            pq.push({r - 1, c, time + 1});
                        } else if (grid[r - 1][c] % 2 != parity) {
                            pq.push({r - 1, c, grid[r - 1][c]});
                        } else {
                            pq.push({r - 1, c, grid[r - 1][c] + 1});
                        }
                    } 
                    
                    if (valid(r, c + 1, grid) && checkNotFilled(r, c + 1, parity)) {
                        if (grid[r][c + 1] <= time + 1) {
                            pq.push({r, c + 1, time + 1});
                        } else if (grid[r][c + 1] % 2 != parity) {
                            pq.push({r, c + 1 , grid[r][c + 1]});
                        } else {
                            pq.push({r, c + 1, grid[r][c + 1] + 1});
                        }
                    } 
                    
                    if (valid(r + 1, c, grid) && checkNotFilled(r + 1, c, parity)) {
                        if (grid[r + 1][c] <= time + 1) {
                            pq.push({r + 1, c, time + 1});
                        } else if (grid[r + 1][c] % 2 != parity) {
                            pq.push({r + 1, c, grid[r + 1][c]});
                        } else {
                            pq.push({r + 1, c, grid[r + 1][c] + 1});
                        }
                    }

                    if (valid(r, c - 1, grid) && checkNotFilled(r, c - 1, parity)) {
                        if (grid[r][c - 1] <= time + 1) {
                            pq.push({r, c - 1, time + 1});
                        } else if (grid[r][c - 1] % 2 != parity) {
                            pq.push({r, c - 1, grid[r][c - 1]});
                        } else {
                            pq.push({r, c - 1, grid[r][c - 1] + 1});
                        }
                    }
                }
            }
        }
        int a = (*dp)[0][grid.size() - 1][grid[0].size() - 1];
        int b = (*dp)[1][grid.size() - 1][grid[0].size() - 1];
        if (a == -1 && b == -1) {
            return -1;
        } else if (a == -1) {
            return b;
        } else if (b == -1) {
            return a;
        } else {
            return min(a, b);
        }

    }
};

int main() {
    vector<vector<int>> x = {{0,1,99},{3,99,99},{4,5,6}};
    Solution s;
    cout << s.minimumTime(x) << endl;
    return 0;
}