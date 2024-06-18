#include <vector>
#include <iostream>
#include <string>
using namespace std;
#define ll long long

void print(vector<string> arr) {
    for (string s : arr) {
        cout << s << " ";

    }
    cout << endl;
}

class Solution {
public:
    vector<string> ops = {"+", "-", "*"};
    vector<string> stack;
    vector<string> stack2;
    vector<string> store;
    ll target;

    void addSol() {
        string ans = "";
        for (string& s : stack2) {
            ans.append(s);
        }
        store.push_back(ans);
    }

    ll doOp(ll lhs, ll rhs, string op) {
        if (op == "+") {
            return lhs + rhs;
        } else if (op == "-") {
            return lhs - rhs;
        } else {
            return lhs * rhs;
        }
    }

    // no "*" operators, they are executed immediately;
    ll eval() {
        ll res = stoll(stack[0]);
        for (int i = 2; i < stack.size(); i += 2) {
            string op = stack[i - 1];
            res = doOp(res, stoi(stack[i]), op);
        }
        return res;
    }

    void helper(int index, string& str, bool first) {
        if (index >= str.size()) {
            ll res = eval();
            if (res == target) addSol();
        } else if (first) {
            if (str[index] == '0') {
                stack.push_back("0");
                stack2.push_back("0");
                helper(index + 1, str, false);
                stack.pop_back();
                stack2.pop_back();
            } else {
                for (int i = 1; i <= str.size(); i ++) {
                    stack.push_back(str.substr(index, i));
                    stack2.push_back(str.substr(index, i));
                    helper(i, str, false);
                    stack.pop_back();
                    stack2.pop_back();
                }
            }
        } 
        
        
        else if (str[index] == '0') {
            
            // now doing "*"
            string prev = stack.back();
            stack.pop_back();
            stack.push_back("0");
            stack2.push_back("*");
            stack2.push_back("0");
            helper(index + 1, str, first);
            stack.pop_back();
            stack.push_back(prev);
            stack2.pop_back();
            stack2.pop_back();

            for (int i = 0; i <= 1; i ++) {
                stack.push_back(ops[i]);
                stack2.push_back(ops[i]);
                stack.push_back(string(1, str[index]));
                stack2.push_back(string(1, str[index]));
                helper(index + 1, str, first);
                stack.pop_back();
                stack2.pop_back();
                stack.pop_back();
                stack2.pop_back();
            }
        } else {
            
            string prev = stack.back();
            ll lhs = stoll(prev);
            stack.pop_back();
            stack2.push_back("*");
            for (int j = 1; j <= str.size() - index; j ++) {
                string rhsStr = str.substr(index, j);
                ll rhs = stoll(rhsStr);
                ll ans = lhs * rhs;
                stack.push_back(to_string(ans));
                stack2.push_back(rhsStr);
                helper(index + j, str, false);
                stack.pop_back();
                stack2.pop_back();
            }
            stack.push_back(prev);
            stack2.pop_back();

            for (int i = 0; i <= 1; i ++) {
                stack.push_back(ops[i]);
                stack2.push_back(ops[i]);
                for (int j = 1; j <= str.size() - index; j ++) {
                    stack.push_back(str.substr(index, j));
                    stack2.push_back(str.substr(index, j));
                    helper(index + j, str, false);
                    stack.pop_back();
                    stack2.pop_back();
                }
                stack.pop_back();
                stack2.pop_back();
            }
        }
    } 

    vector<string> addOperators(string num, int target) {
        this->target = target;
        helper(0, num, true);
        return store;
    }

};



int main() {
    Solution sol;
   
    print(sol.addOperators("2147483647", 2147483647));
     cout << sol.store.size() << endl;
}