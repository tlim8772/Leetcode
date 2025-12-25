#include <bits/stdc++.h>
using namespace std;

// simple problem, just simulate the process.

class Solution {
public:
    int n;
    vector<int> userMentions;
    vector<int> userOfflineTimes;

    vector<int> parseIdsString(const string& s) {
        vector<int> out;
        for(int i = 0; i < s.size();) {
            if (s[i] == ' ') {
                i++;
                continue;
            }

            int start = i + 2;
            int end = s.find(' ', start);
            if (end == string::npos) end = s.size();
            string sub = s.substr(start, end - start);
            int idx = stoi(sub);
            out.push_back(idx);
            
            i = end;
        }
        return out;
    }

    void processMessage(vector<string>& e) {
        int time = stoi(e[1]);
        
        if (e[2] == "HERE") {
            for (int i = 0; i < n; i++) {
                if (userOfflineTimes[i] + 60 <= time) userMentions[i]++;
            }
        } else if (e[2] == "ALL") {
            for (int& x : userMentions) x++;
        } else {
            vector<int> users = parseIdsString(e[2]);
            for (int u : users) userMentions[u]++;
        }
    }

    void processOffline(vector<string>& e) {
        int time = stoi(e[1]);
        int user = stoi(e[2]);
        userOfflineTimes[user] = time;
    }


    vector<int> countMentions(int numberOfUsers, vector<vector<string>>& events) {
        n = numberOfUsers;
        userMentions = vector(n, 0);
        userOfflineTimes = vector(n, -999999);
        
        sort(events.begin(), events.end(), [](const auto& e1, const auto& e2) {
            int t1 = stoi(e1[1]), t2 = stoi(e2[1]);
            if (t1 == t2) {
                return (e2[0] == "OFFLINE") ? false : true;
            }
            return stoi(e1[1]) < stoi(e2[1]); 
        });

        for (auto& e : events) {
            if (e[0] == "MESSAGE") {
                processMessage(e);
            } else if (e[0] == "OFFLINE") {
                processOffline(e);
            }
        }

        return userMentions;
    }
};

int main() {
    Solution sol;
    
    int n = 2;
    vector<vector<string>> events = {{"MESSAGE","10","id1 id0"},{"OFFLINE","11","0"},{"MESSAGE","71","HERE"}};

    vector<int> ans = sol.countMentions(n, events);
    for (int x : ans) cout << x << " ";
    cout << endl;
}