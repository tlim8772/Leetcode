package leetcode;
import java.util.*;

class lc2791 {
    // chars in path (u, v) is bitMask[u] + bitMask[v] - 2bitMask[lca(u, v)];
    // bitMaask[u]: char mask from path (0, u)

    // now 2bitMask[lca(u, v)] is even, so it does not change the bitMask of bitMask[u] + bitMask[v];
    // bitMask[u] + bitMask[v] = all 0s, or power of 2
    // use hashmap to find accordingly
    
    int[] nodeBitMask;
    ArrayList<ArrayList<int[]>> adjList;

    void process(List<Integer> parent, String s) {
        adjList = new ArrayList<>();
        for (int i = 0; i < parent.size(); i ++) {
            adjList.add(new ArrayList<>());
        }
        for (int i = 0; i < parent.size(); i ++) {
            if (parent.get(i) != -1) {
                adjList.get(i).add(new int[] {parent.get(i), s.charAt(i) - 'a'});
                adjList.get(parent.get(i)).add(new int[] {i, s.charAt(i) - 'a'});
            }
        }
    }

    void processBM(int node, int parent, int prev) {
        nodeBitMask[node] = prev;
        ArrayList<int[]> childs = adjList.get(node);
        for (int i = 0; i < childs.size(); i ++) {
            if (childs.get(i)[0] != parent) {
                int[] child = childs.get(i);
                processBM(child[0], node, prev ^ (1 << child[1]));
            }
        }
    }

    public long countPalindromePaths(List<Integer> parent, String s) {
        nodeBitMask = new int[parent.size()];
        HashMap<Integer, Long> bitCount = new HashMap<>();
        process(parent, s);
        processBM(0, 0, 0);
        long count = 0;
        for (int i = nodeBitMask.length - 1; i >= 0; i --) {
            count += (bitCount.get(nodeBitMask[i]) == null) ? 0 : bitCount.get(nodeBitMask[i]);
            for (int c = 0; c < 26; c ++) {
                int xorMask = 1 << c;
                int pair = nodeBitMask[i] ^ xorMask;
                count += (bitCount.get(pair) == null) ? 0 : bitCount.get(pair); 
            }
            if (bitCount.get(nodeBitMask[i]) == null) {
                bitCount.put(nodeBitMask[i], 1L);
            } else {
                bitCount.put(nodeBitMask[i], bitCount.get(nodeBitMask[i]) + 1);
            }
        }
        return count;
        
    }

    public static void main(String[] args) {
        List<Integer> parent = new ArrayList<>(Arrays.asList(-1,0,0,1,1,2));
        String s = "acaabc";
        lc2791 sol = new lc2791();
        System.out.println(sol.countPalindromePaths(parent, s));
    }


    

}