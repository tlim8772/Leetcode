package leetcode;

import java.util.*;

// classic 2 dfs for tree, for each vertex store the 2 furthest vertex

class Solution {
    ArrayList<ArrayList<int[]>> store;
    ArrayList<ArrayList<Integer>> adj;
    int[] result;

    void insert(ArrayList<int[]> arr, int v, int val) {
        arr.add(new int[] {v, val});
        Collections.sort(arr, (int[] x, int[] y) -> {return y[1] - x[1];});
        if (arr.size() > 2) {
            arr.remove(arr.size() - 1);
        }
    }


    int dfs1(int v, int p) {
        int max = 0;
        for (int c : adj.get(v)) {
            if (c == p) continue;
            
            int res = ((c % 2 == 0) ? 2 : 1) + dfs1(c, v);
            max = Math.max(res, max);
            insert(store.get(v), c, res);
        }
        return max;
    }

    void dfs2(int v, int p) {
        if (v == p) {
            if (store.get(v).size() == 0) result[v] = 0;
            else result[v] = store.get(v).get(0)[1];
        } else {
            int pRes = (p % 2 == 0) ? 2 : 1;
            if (store.get(p).size() == 1) {
                // only 1 child, which is v
                insert(store.get(v), p, pRes);
            } else if (store.get(p).get(0)[0] == v) {
                // 2 best, but 1st best is v itself
                pRes += store.get(p).get(1)[1];
                insert(store.get(v), p, pRes);
            } else {
                pRes += store.get(p).get(0)[1];
                insert(store.get(v), p, pRes);
            }
            result[v] = store.get(v).get(0)[1];
        }
        for (int c : adj.get(v)) {
            if (c == p) continue;
            dfs2(c, v);
        }
       
    }

    public int[] timeTaken(int[][] edges) {
        result = new int[edges.length + 1];
        
        adj = new ArrayList<>();
        for (int i = 0; i < edges.length + 1; i ++) adj.add(new ArrayList<>());

        store = new ArrayList<>();
        for (int i = 0; i < edges.length + 1; i ++) store.add(new ArrayList<>());

        for (int[] e : edges) {
            adj.get(e[0]).add(e[1]);
            adj.get(e[1]).add(e[0]);
        }

        dfs1(0, 0);
        dfs2(0, 0);
        return result;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        int[][] edges = {{1,0},{5,2},{7,1},{6,3},{3,1},{4,1},{8,7},{2,0}};
        System.out.println(Arrays.toString(sol.timeTaken((edges))));
    }


}