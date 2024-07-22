#include <vector>
#include <iostream>
#include <unordered_set>
using namespace std;

// nothing special really, no fancy algos
// 1st, for all colors, we find the boundary, i.e the leftmost, rightmost, upmost, downmost coordinates
// this forms the dimesions (and coordinates) of the rectangle printed
// we start from back, we find a possible color that cound have been printed (coor of color, and colors used after form
// a valid rectangle) add that color to used, then repeat.
// if can repeat until 0, return true;
// if not at some point we cannot find a proper rectangle, return false


class Solution {
public:
    vector<bool> used;
    vector<vector<int>> dims; // {left, right, up, down}
    vector<vector<int>> grid;
    unordered_set<int> colors;

    bool checkIfRectangle(int color, vector<int>& dim) {
        int left, right, up, down;
        left = dim[0]; right = dim[1]; up = dim[2]; down = dim[3];

        for (int r = left; r <= right; r ++) {
            for (int c = up; c <= down; c ++) {
                if (grid[r][c] != color && !used[grid[r][c]]) return false;
            }
        }
        return true;
    }

    void process() {
        for (int r = 0; r < grid.size(); r ++) {
            for (int c = 0; c < grid[0].size(); c ++) {
                colors.insert(grid[r][c]);
            }
        }

        for (auto it = colors.begin(); it != colors.end(); it ++) {
            int color = *it;
            vector<int>& dim = dims[color];
            
            for (int r = 0; r < grid.size(); r ++) {
                for (int c = 0; c < grid[0].size(); c ++) {
                    if (grid[r][c] == color) {
                        dim[0] = min(dim[0], r);
                        dim[1] = max(dim[1], r);
                        dim[2] = min(dim[2], c);
                        dim[3] = max(dim[3], c);
                    }
                }
            }
        }
    }


    // remove the used color from colors
    bool canPrint() {
        int size = colors.size();
        while (size > 0) {
            bool canFind = false;

            // no color in colors has been used
            for (auto it = colors.begin(); it != colors.end(); it ++) {
                int color = *it;
                bool poss = checkIfRectangle(color, dims[color]);
                if (poss) {
                    canFind = true;
                    size --;
                    used[color] = true;
                    colors.erase(color);
                    break;
                }
            }
            if (!canFind) return false;
        } 
        return true;
    }

    bool isPrintable(vector<vector<int>>& targetGrid) {
        used = vector(61, false);
        grid = targetGrid;
        dims = vector(61, vector({9999, -9999, 9999, -9999}));
        process();
        return canPrint();
    }

};

int main() {
    vector<vector<int>> grid = {{1, 1, 1, 1}, {1, 2, 2, 1}, {1, 2, 2, 1}, {1, 1, 1, 1}};
    Solution sol;
    cout << sol.isPrintable(grid);
}