#include <bits/stdc++.h>
using namespace std;

// just bfs.

vector<string> generate_words(const string& s) {
    vector<string> out;
    for (int i = 0; i < s.size(); i++) {
        for (int j = 0; j < 26; j++) {
            string t = s;
            t[i] = (char) ('a' + j);
            out.push_back(t);
        }
    }
    return out;
}

class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> store(wordList.begin(), wordList.end());
        unordered_set<string> seen;

        if (!store.contains(endWord)) return 0;

        int wave = 1;
        deque<string> q;
        q.push_back(beginWord);

        while (!q.empty()) {
            for (int len = q.size(); len > 0; len--) {
                string word = q.front(); q.pop_front();
                if (seen.contains(word)) continue;
                //cout << wave << " " << word << endl;

                if (word == endWord) return wave;
                
                seen.insert(word);
                auto nexts = generate_words(word);
                for (string next : nexts) {
                    if (!store.contains(next) || seen.contains(next)) continue;
                    //cout << next << endl;
                    q.push_back(next);
                }
            }
            wave++;
        }

        return 0;
    }
};

int main() {
    Solution sol;
    string beginWord = "hit", endWord = "cog";
    vector<string> wordList = {"hot", "dot", "dog", "lot", "log", "cog"};

    int ans = sol.ladderLength(beginWord, endWord, wordList);
    cout << ans << endl;
}