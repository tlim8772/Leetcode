#include <bits/stdc++.h>
using namespace std;

// build graph, do bfs from dest, then from resulting DAG build all shortest paths

class Solution {
public:
    unordered_map<string, vector<string>> adj;
    unordered_map<string, vector<string>> dagAdj;
    
    vector<vector<string>> result;
    vector<string> store;

    string dest;
    string src;

    bool isAdj(string& a, string& b) {
        int c = 0;
        for (int i = 0; i < a.size(); i ++) c += (a[i] != b[i]);
        return c == 1;
    }

    void buildGraph(vector<string>& wordList) {
        for (int i = 0; i < wordList.size(); i ++) {
            for (int j = 0; j < wordList.size(); j ++) {
                if (isAdj(wordList[i], wordList[j])) adj[wordList[i]].push_back(wordList[j]);
            }
        }
    }

    void buildDAG(string& dest) {
        unordered_map<string, bool> visited;
        unordered_map<string, bool> inQueue;
        visited[dest] = true;
        inQueue[dest] = true;
        queue<string> q;
        q.push(dest);

        while (!q.empty()) {
            int len = q.size();
            for (; len > 0; len --) {
                string word = q.front();
                q.pop();
                for (string& n : adj[word]) {
                    if (!visited[n]) dagAdj[n].push_back(word);
                    if (!inQueue[n]) {
                        inQueue[n] = true;
                        q.push(n);
                    }
                }
            }

            int len2 = q.size();
            for (; len2 > 0; len2 --) {
                string word = q.front(); q.pop();
                visited[word] = true;
                q.push(word);
            }
        }
    } 

    void getPaths(string& word) {
        if (word == dest) {
            store.push_back(word);
            result.push_back(store);
            store.pop_back();
        } else {
            store.push_back(word);
            for (string& next : dagAdj[word]) {
                getPaths(next);
            }
            store.pop_back();
        }
    }

    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        bool inside = accumulate(wordList.begin(), wordList.end(), false, [beginWord] (bool a, string& s) {return a || s == beginWord;});
        if (!inside) wordList.push_back(beginWord);
        
        buildGraph(wordList);
        

        buildDAG(endWord);
        /*for (auto const& [key, value] : dagAdj) {
            cout << key << endl;
            for (auto s : value) {
                cout << s << " ";
            }
            cout << endl;
            cout << endl;
        }*/

        dest = endWord;
        
        getPaths(beginWord);

        return result;
    }


};

int main() {
    string src = "hit";
    string dest = "cog";
    vector<string> wordList = {"hot","dot","dog","lot","log","cog"};
    Solution sol;

    vector<vector<string>>&& ans = sol.findLadders(src, dest, wordList);
    //cout << ans.size() << endl;
    for (vector<string>& lst : ans) {
        for (string& s : lst) {
            cout << s << endl;
        }
        cout << endl;
    }
}