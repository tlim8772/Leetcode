#include <vector>
#include <iostream>
using namespace std;

vector<vector<int>> dirs = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

class Solution {
public:
    bool isValid(int r, int c, vector<vector<int>>& grid) {
        return (r < 0 || c < 0 || r >= grid.size() || c >= grid[0].size()) ? false : true;
    }
    
    
    bool isBorder(int r, int c, vector<vector<int>>& grid) {
        if (r == 0 || c == 0 || r == grid.size() - 1 || c == grid[0].size() - 1) {
            return true;
        } else {
            for (vector<int>& dir : dirs) {
                if (grid[r + dir[0]][c + dir[1]] != grid[r][c]) return true;
            }
            return false;
        }
    }

    vector<vector<int>> store;

    void findBorder(int r, int c, vector<vector<bool>>& visited, vector<vector<int>>& grid) {
        if (!isValid(r, c, grid) || visited[r][c]) return;
        else {
            visited[r][c] = true;
            if (isBorder(r, c, grid)) store.push_back({r, c});
            for (vector<int>& dir : dirs) {
                if (isValid(r + dir[0], c + dir[1], grid) && grid[r + dir[0]][c + dir[1]] == grid[r][c]) {
                    findBorder(r + dir[0], c + dir[1], visited, grid);
                }
            }
        }
    }

    vector<vector<int>> colorBorder(vector<vector<int>>& grid, int row, int col, int color) {
        store = vector<vector<int>>();
        vector<vector<bool>> visited = vector(grid.size(), vector(grid[0].size(), false));
        findBorder(row, col, visited, grid);
        for (vector<int>& coor : store) {
            grid[coor[0]][coor[1]] = color;
        }
        return grid;
    }
};

void print(vector<vector<int>> grid) {
    for (vector<int> g : grid) {
        for (int i : g) {
            cout << i << " ";
        }
        cout << endl;
    }
}

int main() {
    vector<vector<int>> grid = {{1,1},{1,2}};
    int r = 0;
    int c = 0;
    print(Solution().colorBorder(grid, r, c, 3));
}