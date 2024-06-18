#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
public:
    
    bool isChar(char c) {
        return (0 <= c - 'a' && c - 'a' < 26);
    }

    vector<string>* add(vector<string>* a, vector<string>* b) {
       if (a->size() == 0) {
        return b;
       } else if (b->size() == 0) {
        return a;
       } else {
        vector<string>* out = new vector<string>();
        for (string s1 : *a) {
            out->push_back(s1);
        }
        for (string s2 : *b) {
            out->push_back(s2);
        }
        return out;
       }
    }

    vector<string>* mult(vector<string>* a, vector<string>* b) {
        vector<string>* out = new vector<string>();
        if (a->size() == 0) {
            return b;
        } else if (b->size() == 0) {
            return a;
        } else {
            for (string s1 : *a) {
                for (string s2 : *b) {
                    string s = s1 + s2;
                    out->push_back(s);
                }
            }
            return out;
        }
        
    }

    vector<int> pairUpBraces(string expr) {
        vector<int> stack;
        vector<int> out = vector(expr.size(), -1);
        for (int i = 0; i < expr.size(); i ++) {
            if (expr[i] == '{') {
                stack.push_back(i);
            } else if (expr[i] == '}') {
                int pair = stack.back();
                stack.pop_back();
                out[pair] = i;
                out[i] = pair;
            }
        }
        return out;
    }

    // prev means we have to multiply
    vector<string>* parse(int s, int e, string& expr, vector<string> *prev, vector<int>& bracesPair) {
        if (s > e) {
            return prev;
        } else if (expr[s] == '{') {
            int p = bracesPair[s];
            if (p == e) {
                vector<string>* res = parse(s + 1, e - 1, expr, new vector<string>(), bracesPair);
                return mult(prev, res);
            } else if (expr[p + 1] == '{') {
                vector<string>* res = parse(s + 1, p - 1, expr, new vector<string>(), bracesPair); 
                vector<string>* res2 = mult(prev, res);
                return parse(p + 1, e, expr, res2, bracesPair);
            } else if (expr[p + 1] == ',') {
                vector<string>* res = parse(s + 1, p - 1, expr, new vector<string>(), bracesPair); 
                vector<string>* res2 = parse(p + 2, e, expr, new vector<string>(), bracesPair);
                res = mult(prev, res);
                return add(res, res2);
            } else {
                // expr[p + 1] is char
                vector<string>* res = parse(s + 1, p - 1, expr, new vector<string>(), bracesPair);
                res = mult(prev, res);
                return parse(p + 1, e, expr, res, bracesPair);
            } 
        } else if (isChar(expr[s])) {
            vector<string>* res = new vector<string>({string(1, expr[s])});
            res = mult(prev, res);
            if (s == e) {
                return res;
            } else if (expr[s + 1] == ',') {
                vector<string>* res2 = parse(s + 2, e, expr, new vector<string>(), bracesPair);
                return add(res, res2);
            } else {
                // must be a '{'
                return parse(s + 1, e, expr, res, bracesPair);
            }
        }
        return nullptr;
    }

     vector<string> braceExpansionII(string expression) {
        vector<int> pairs = pairUpBraces(expression);
        vector<string>* ans = parse(0, expression.size() - 1, expression, new vector<string>(), pairs);
        sort(ans->begin(), ans->end());
        vector<string> out;
        for (int i = 0; i < ans->size(); i ++) {
            if (i == 0) {
                out.push_back((*ans)[i]);
            } else if ((*ans)[i] != (*ans)[i - 1]) {
                out.push_back((*ans)[i]);
            }
        }
        return out;
    }

};

void print(vector<string>* a) {
    for (string s : *a) {
        cout << s << " ";
    }
    cout << endl;
}

void print(vector<string> a) {
    for (string s : a) {
        cout << s << " ";
    }
    cout << endl;
}

int main() {
    string expr = "{{a,z},a{b,c},{ab,z}}";
    Solution sol;
    vector<string> ans = sol.braceExpansionII(expr);
    print(ans);
}

/*int main() {
    vector<string>* a1 = new vector<string>({"a", "b", "c"});
    vector<string>* a2 = new vector<string>({"x", "y", "z"});
    print(Solution().mult(a1, a2));

}*/