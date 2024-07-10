

import java.util.*;
// for lc1896

class lc1896 {
    int findMinCost(int[] e1, int[] e2, char op) {
        if (op == '&') {
            if (e1[0] == 0 && e2[0] == 0) {
                return 1 + Math.min(e1[1], e2[1]);
            } else if (e1[0] == 0 && e2[0] == 1) {
                return 1;
            } else if (e1[0] == 1 && e2[0] == 0) {
                return 1;
            } else {
                return Math.min(e1[1], e2[1]);
            }
        } else {
            if (e1[0] == 0 && e2[0] == 0) {
                return Math.min(e1[1], e2[1]);
            } else if (e1[0] == 0 && e2[0] == 1) {
                return 1;
            } else if (e1[0] == 1 && e2[0] == 0) {
                return 1;
            } else {
                return 1 + Math.min(e1[1], e2[1]);
            }
        }
    }

    int eval(int[] e1, int[] e2, char op) {
        if (op == '&') {
            return e1[0] & e2[0];
        } else {
            return e1[0] | e2[0];
        }
    }

    int[] partnerBrackets(String str) {
        int[] out = new int[str.length()];
        ArrayList<Integer> stack = new ArrayList<>();
        for (int i = 0; i < str.length(); i ++) {
            if (str.charAt(i) == '(') {
                stack.add(i);
            } else if (str.charAt(i) == ')') {
                int partner = stack.get(stack.size() - 1);
                stack.remove(stack.size() - 1);
                out[partner] = i;
                out[i] = partner;
            }
        }
        return out;
    }

    int[] helper(String str, int s, int e, int[] store) {
        if (s == e) {
            // "1"
            return new int[] {str.charAt(e) - '0', 1};
        } else if (e == s + 1) {
            // "(0"
            return new int[] {str.charAt(e) - '0', 1};
        } else if (str.charAt(e) == ')') {
            int p = store[e];
            if (p == s) {
                // s = '(', e = ')', so can just remove
                return helper(str, s + 1, e - 1, store);
            } else {
                char op = str.charAt(p - 1);
                int[] e1 = helper(str, s, p - 2, store);
                int[] e2 = helper(str, p, e, store);
                int minCost = findMinCost(e1, e2, op);
                int res = eval(e1, e2, op);
                
                return new int[] {res, minCost};
            }
        } else {
            int[] e2 = new int[] {str.charAt(e) - '0', 1};
            char op = str.charAt(e - 1);
            int[] e1 = helper(str, s, e - 2, store);
            int minCost = findMinCost(e1, e2, op);
            int res = eval(e1, e2, op);
            //delete[] e1;
            //delete[] e2;
            return new int[] {res, minCost};
        }
    }

    public int minOperationsToFlip(String expression) {
        int[] store = partnerBrackets(expression);
        System.out.println(Arrays.toString(store));
        int[] res = helper(expression, 0, expression.length() - 1, store);
        return res[1];
    }

    public static void main(String[] args) {
        lc1896 s = new lc1896();
        String str = "1&(0|1)";
        int ans = s.minOperationsToFlip(str);
        System.out.println(ans);
    }

}