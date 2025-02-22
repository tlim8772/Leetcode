#include <vector>
#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

class Solution {
public:
    string stack;
    vector<string> store;
    unordered_map<string, int> seen;
    int minDel = 999999;

    void generate(int index, int leftBracket, string& s) {
        if (index - stack.size() > minDel) return;
        if (index == s.size()) {
            if (leftBracket == 0 && seen.find(stack) == seen.end()) {
                store.push_back(stack);
                seen[stack] = 1;
                minDel = min(minDel, (int) s.size() - (int) stack.size());
            }
        } else if (s[index] == '(') {
            stack.push_back('(');
            generate(index + 1, leftBracket + 1, s);
            stack.pop_back();
            generate(index + 1, leftBracket, s);
        } else if (s[index] == ')') {
            if (leftBracket > 0) {
                stack.push_back(')');
                generate(index + 1, leftBracket - 1, s);
                stack.pop_back();
            }
            generate(index + 1, leftBracket, s);
        } else {
            stack.push_back(s[index]);
            generate(index + 1, leftBracket, s);
            stack.pop_back();
            generate(index + 1, leftBracket, s);
        }
    }

    int getMaxLen() {
        int res = -1;
        for (string& s : store) {
            res = max(res, (int) s.size());
        }
        return res;
    }

    vector<string> process() {
        int shortest = getMaxLen();
        vector<string> res;
        for (string& s : store) {
            if (s.size() == shortest) {
                res.push_back(s);
            }
        }
        return res;
    }

    vector<string> removeInvalidParentheses(string s) {
        generate(0, 0, s);
        return process();
    }


};

void print(vector<string>& arr) {
    for (string& s : arr) {
        cout << s << endl;
    }
}

int main() {
    Solution sol;
    string s =  "(a)())()";
    vector<string>&& ans = sol.removeInvalidParentheses(s);
    cout << ans.size() << endl;
    print(ans);
}