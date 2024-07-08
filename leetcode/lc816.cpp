#include <bits/stdc++.h> 
using namespace std;

class Solution {
public:
    vector<string> generate(string s) {
        vector<string> possible;
        if (stod(s) == 0) {
            if (s.size() == 1) {
                possible.push_back("0");
            }
        } else if (s[0] == '0' && s[s.size() - 1] == '0') {
            //return possible;
        } else if (s[0] == '0') {
            string onlyOne = "";
            onlyOne += "0";
            onlyOne += ".";
            onlyOne += s.substr(1, s.size() - 1);
            possible.push_back(onlyOne);
        } else {
            possible.push_back(s);
            for (int i = 0; i < s.size() - 1; i ++) {
                string front = s.substr(0, i + 1);
                string back = s.substr(i + 1, s.size() - i - 1);
                if (stod(back) != 0 && s[s.size() - 1] != '0') {
                    front.append(".");
                    front.append(back);
                    possible.push_back(front);
                }
            }
        }
        return possible;
    }

     vector<string> ambiguousCoordinates(string s) {
        vector<string> out;
        for (int i = 0; i < s.size() - 1; i ++) {
            vector<string>&& first = generate(s.substr(0, i + 1));
            vector<string>&& second = generate(s.substr(i + 1, s.size() - i - 1));
            for (int i = 0; i < first.size(); i ++) {
                for (int j = 0; j < second.size(); j ++) {
                    string a = first[i];
                    string b = second[j];
                    string res = "(";
                    res.append(a);
                    res.append(",");
                    res.append(" ");
                    res.append(b);
                    res.append(")");
                    out.push_back(res);
                }
            }
        }
        return out;
    }
};

int main() {
    Solution sol;
    string s = "0110";
    vector<string>&& ans = sol.ambiguousCoordinates(s);
    for (int i = 0; i < ans.size(); i ++) {
        cout << ans[i] << endl;
    }
    return 0;
}