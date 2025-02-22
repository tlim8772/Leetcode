#include <vector>
#include <iostream>
using namespace std;

// {result before changing anything, min cost to flip result}
// basically parsing 
// suppose exp1 op exp2
// depending on result, exp1/2, op min cost depends on the min cost of flipping result of exp1/2
// recurse
// since we are parsing, its a tree, no need for dp
class Solution {

public:
    //vector<int> store;
    int findMinCost(int e1[], int e2[], char op) {
        if (op == '&') {
            if (e1[0] == 0 && e2[0] == 0) {
                return 1 + min(e1[1], e2[1]);
            } else if (e1[0] == 0 && e2[0] == 1) {
                return 1;
            } else if (e1[0] == 1 && e2[0] == 0) {
                return 1;
            } else {
                return min(e1[1], e2[1]);
            }
        } else {
            if (e1[0] == 0 && e2[0] == 0) {
                return min(e1[1], e2[1]);
            } else if (e1[0] == 0 && e2[0] == 1) {
                return 1;
            } else if (e1[0] == 1 && e2[0] == 0) {
                return 1;
            } else {
                return 1 + min(e1[1], e2[1]);
            }
        }
    }

    int eval(int e1[], int e2[], char op) {
        if (op == '&') {
            return e1[0] & e2[0];
        } else {
            return e1[0] | e2[0];
        }
    }

    vector<int> partnerBrackets(string& str) {
        vector<int> out = vector(str.size(), -1);
        vector<int> stack;
        for (int i = 0; i < str.size(); i ++) {
            if (str[i] == '(') {
                stack.push_back(i);
            } else if (str[i] == ')') {
                int partner = stack[stack.size() - 1];
                stack.pop_back();
                out[partner] = i;
                out[i] = partner;
            }
        }
        return out;
    }

    int* helper(string& str, int s, int e, vector<int>& store) {
        if (s == e) {
            // "1"
            return new int[2] {str[e] - '0', 1};
        } else if (e == s + 1) {
            // "(0"
            return new int[2] {str[e] - '0', 1};
        } else if (str[e] == ')') {
            int p = store[e];
            if (p == s) {
                // s = '(', e = ')', so can just remove
                return helper(str, s + 1, e - 1, store);
            } else {
                char op = str[p - 1];
                int* e1 = helper(str, s, p - 2, store);
                int* e2 = helper(str, p, e, store);
                int minCost = findMinCost(e1, e2, op);
                int res = eval(e1, e2, op);
                //delete[] e1;
                //delete[] e2;
                return new int[2] {res, minCost};
            }
        } else {
            int* e2 = new int[2] {str[e] - '0', 1};
            char op = str[e - 1];
            int* e1 = helper(str, s, e - 2, store);
            int minCost = findMinCost(e1, e2, op);
            int res = eval(e1, e2, op);
            //delete[] e1;
            //delete[] e2;
            return new int[2] {res, minCost};
        }
    }

    int minOperationsToFlip(string expression) {
        vector<int>&& store = partnerBrackets(expression);
        int* res = helper(expression, 0, expression.size() - 1, store);
        return res[1];
    }
};


template <typename T>
void print(vector<T> a) {
    for (T t : a) {
        cout << t << " ";
    }
    cout << endl;
}

int main() {
    string s = "(0&0)&(0&0&0)";
    Solution sol;
    //vector<int>&& res = sol.minOperationsToFlip(s);
    //print(res);
    int ans = sol.minOperationsToFlip(s);
    cout << ans;
}