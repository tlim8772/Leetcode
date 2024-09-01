package leetcode;

import java.util.*;


class Solution {
    List<List<String>> store = new ArrayList<>();

    public boolean hit(int a, int b, int x, int y) {
        return (a == x || b == y || Math.abs(a - x) == Math.abs(b - y));
    }

    public List<String> addString(List<List<Integer>> places, int n) {
        List<String> res = new ArrayList<>();
        for (int i = 0; i < n;i ++) {
            StringBuilder sb = new StringBuilder();
            for (int j = 0; j < n; j ++) {
                if (j != places.get(i).get(1)) sb.append('.');
                else sb.append('Q');
            }
            res.add(sb.toString());
        }
        return res;
    }

    public void helper(int row, int n, List<List<Integer>> pos) {
        if (row == n) {
            store.add(addString(pos, n));
        } else {
            for (int col = 0; col < n; col ++) {
               boolean can = true;
               for (int i = 0; i < pos.size(); i ++) {
                    if (hit(pos.get(i).get(0), pos.get(i).get(1), row, col)) {
                        can = false;
                        break;
                    }
                }
                if (can) {
                    pos.add(new ArrayList<>(Arrays.asList(row, col)));
                    helper(row + 1, n, pos);
                    pos.remove(pos.size() - 1);
                }
                    
            
            }
        }
    }

    public List<List<String>> solveNQueens(int n) {
        helper(0, n, new ArrayList<>());
        return store;
    }

    public void print() {
        for (List<String> ans : store) {
            for (String str : ans) {
                System.out.println(str);
            }
            System.out.println();
        }
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        sol.helper(0, 9, new ArrayList<>());
        sol.print();



    }

}