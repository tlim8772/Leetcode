#include <bits/stdc++.h>
using namespace std;

// use trie and backtracking to solve

struct Trie {
    bool end = false;
    array<Trie*, 26> next = {nullptr};

    static void insert(Trie *root, const string& s) {
        Trie *curr = root;
        int p = 0;

        while (p < s.size()) {
            int c = s[p] - 'a';
            if (curr->next[c] == nullptr) {
                Trie *n = new Trie();
                curr->next[c] = n;
                curr = n;
            } else {
                curr = curr->next[c];
            }
            
            p++;
        }

        // now curr is pointing to the node that represents the entire word
        curr->end = true;
    }

    static bool exist(Trie *root, const string& s) {
        Trie *curr = root;
        int p = 0;
        
        while (p < s.size()) {
            int c = s[p] - 'a';
            if (curr->next[c] == nullptr) {
                return false;
            } else {
                curr = curr->next[c];
            }
            p++;
        }

        return curr->end;

    }
};

class Solution {
    int R = -1, C = -1;
    vector<array<int, 2>> dirs = {{-1,0},{0,1},{1,0},{0,-1}};

    Trie *root = new Trie();

    vector<vector<bool>> visited;
    unordered_set<string> store;
    string stack;

    bool isValid(int r, int c) {
        return r >= 0 && r < R && c >= 0 && c < C;
    }

    void helper(int r, int c, const vector<vector<char>> &grid, Trie *curr) {
        visited[r][c] = true;

        int cha = grid[r][c] - 'a';
        if (curr->next[cha] != nullptr) {
            stack.push_back(grid[r][c]);
            Trie *n = curr->next[cha];

            if (n->end) {
                store.insert(stack);
            }

            for (array<int, 2>& d : dirs) {
                int nr = r + d[0], nc = c + d[1];
                if (!isValid(nr, nc) || visited[nr][nc]) continue;

                helper(nr, nc, grid, n);
            }
            
            stack.pop_back();
        }
        
        visited[r][c] = false;
    }



public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        for (string& s : words) {
            Trie::insert(root, s);
        }

        R = board.size(), C = board[0].size();
        visited = vector(R, vector(C, false));

        for (int r = 0; r < R; r++) {
            for (int c = 0; c < C; c++) {
                helper(r, c, board, root);
            }
        }

        vector<string> out(store.begin(), store.end());
        return out;

    }
};

int main() {
    Solution sol;

    vector<vector<char>> board = {{'a','b'},{'c','d'}};
    vector<string> words = {"abcb"};

    vector<string> res = sol.findWords(board, words);
    for (string s : res) {
        cout << s << endl;
    }
}