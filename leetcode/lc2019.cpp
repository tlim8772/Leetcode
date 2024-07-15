#include <vector>
#include <iostream>
#include <unordered_set>
#include <algorithm>
#include <numeric>
using namespace std;

template <typename T>
void print(vector<T> arr) {
    for (T t: arr) {
        cout << t << endl;
    }
    //cout << endl;
}




void print(unordered_set<int> set) {
    for (int x : set) {
        cout << x << " ";
    }
    cout << endl;
}

class Solution {
public:
    vector<vector<unordered_set<int>>> dp;
    
    //unordered_set<int> store;
    //vector<string> stack;
    
    vector<string> tokeniser(string& s) {
        vector<string> out;
        for_each(s.begin(), s.end(), [&out] (char c) -> void {out.push_back(string(1, c));});
        return out;
    }

    int doOp(string& op, string& oper1, string& oper2) {
        if (op == "+") {
            return stoi(oper1) + stoi(oper2);
        } else {
            return stoi(oper1) * stoi(oper2);
        }
    }

    int evalCorrect(string& s) {
        vector<string> tokens = tokeniser(s);
        vector<int> stack;
        stack.push_back(stoi(tokens[0]));
        for (int i = 1; i < tokens.size(); i += 2) {
            if (tokens[i] == "*") {
                int oper1 = stack.back();
                stack.pop_back();
                stack.push_back(oper1 * stoi(tokens[i + 1]));
            } else {
                stack.push_back(stoi(tokens[i + 1]));
            }
        }

        return accumulate(stack.begin(), stack.end(), 0, [](int a, int b) -> int {return a + b;});
    }

    void process(string& s) {
        dp = vector(s.size() / 2 + 1, vector(s.size() / 2 + 1, unordered_set<int>()));
    }

    // note the structure of the string, e.g "6+0*1"
    // every even index is a digit, every odd index is a operator
    // dp, so [s, e] means index 2 * s, 2 * e in string
    // we find all possible values by noticing the final operator splits the string into [s, m] and [m + 1, e]
    // try all possible splits
    // since 0 <= ans <= 1000, and only have + and * so ans can only increase
    
    unordered_set<int>& helper(string& str, int s, int e) {
        if (dp[s][e].size() != 0) {
            return dp[s][e];
        } else if (s == e) {
            dp[s][e].insert(str[2 * s] - '0');
            return dp[s][e];
        } else {
            for (int i = 2 * s + 1; i < 2 * e; i += 2) {
                char op = str[i];

                // invariant, only res <= 1000 are stored
                unordered_set<int>& l = helper(str, s, (i - 1) / 2);
                unordered_set<int>& r = helper(str, (i + 1) / 2, e);
                for (int le : l) {
                    //if (le > 1000) continue;
                    for (int re : r) {
                        //if (re > 1000) continue;
                        
                        int ans = (str[i] == '+') ? le + re : le * re;
                        if (ans <= 1000) dp[s][e].insert(ans);
                        
                    }
                }
            }
            return dp[s][e];
        }
    }

    /*int eval() {
        vector<string> stack2 = stack;
        while (stack2.size() > 1) {
            string op2 = stack2.back(); stack2.pop_back();
            string op = stack2.back(); stack2.pop_back();
            string op1 = stack2.back(); stack2.pop_back();
            stack2.push_back(to_string(doOp(op, op1, op2)));
        }
        return stoi(stack2[0]);
    }
    
    // except for index = 0, all index are odd, point to operators only
    // actually wrong
    void generateAll(vector<string>& tokens, int index) {
        if (index == tokens.size()) {
            store.insert(eval());
        } else if (stack.size() <= 1) {
            stack.push_back(tokens[index]);
            generateAll(tokens, index + 1);
            stack.pop_back();
        } else {
            string op1 = stack.back(); stack.pop_back();
            stack.push_back(to_string(doOp(tokens[index], op1, tokens[index + 1])));
            generateAll(tokens, index + 2);
            stack.pop_back(); // pop doOp res;
            stack.push_back(op1); // push back in op1
            stack.push_back(tokens[index]);
            stack.push_back(tokens[index + 1]);
            generateAll(tokens, index + 2);
            stack.pop_back(); // pop tokens[index]
            stack.pop_back(); // pop tokens[index + 1]
        }
    }*/



    int scoreOfStudents(string s, vector<int>& answers) {
        int correctAns = evalCorrect(s);
        vector<string> tokens = tokeniser(s);
        process(s);
        unordered_set<int>& store = helper(s, 0, s.size() / 2);
        
        int sum = 0;

        cout << correctAns << endl;
        print(store);
        
        for (int ans : answers) {
            if (ans == correctAns) sum += 5;
            else if (store.find(ans) != store.end()) sum += 2;
        }
        return sum;
        
    }


};

int main() {
    Solution sol;
    string s = "4+2*2+3*1+2";
    vector<int> answers = {42,17,13,66,32,547,21,90,13,33,45,66,34,21,13,13,13,46,21,177,18,13,18,16,16,678,13,42,66,13,18,18,777,21,924,13,268,13,13,13,25,62,45,33,888,779,13,206,48,13,34,17};
    cout << sol.scoreOfStudents(s, answers);
}

