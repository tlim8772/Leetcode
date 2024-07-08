#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;


class Solution {
public:
    unordered_map<string, int> mapAll;

    Solution(): mapAll() {}

    void putAll(vector<string>& arr) {
        for (string& s : arr) {
            for (int i = 0; i < s.size(); i ++) {
                for (int j = 1; j <= s.size() - i; j ++) {
                    mapAll[s.substr(i, j)] ++;
                }
            }
        }
    }

    vector<string> shortestSubstrings(vector<string>& arr) {
        putAll(arr);
        vector<string> result;
        for (string& s : arr) {
            unordered_map<string, int> forOne;
            for (int i = 0; i < s.size(); i ++) {
                for (int j = 1; j <= s.size() - i; j ++) {
                    forOne[s.substr(i, j)] ++;
                }
            }
            string res = "";
            for (int i = 0; i < s.size(); i ++) {
                for (int j = 1; j <= s.size() - i; j ++) {
                    string curr = s.substr(i, j);
                    if (forOne[curr] == mapAll[curr]) {
                        if (res == "" || res.size() > curr.size() || (res > curr && res.size() == curr.size())) {
                            res = curr;
                        }
                    }
                }
            }
            result.push_back(res);

        }
        return result;
    }

    
};

void print(vector<string>& r) {
    for (string& s : r) {
        cout << s << " ";
    }
    cout << endl;
}

int main() {
    vector<string> arr = {"cab","ad","bad","c"};
    vector<string> result = Solution().shortestSubstrings(arr);
    print(result);
    

}

