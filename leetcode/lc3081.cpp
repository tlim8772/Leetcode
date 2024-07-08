#include <vector>
#include <iostream>
#include <queue>
#include <functional>
using namespace std;


// if char a appear x times, the cost is 0 + 1 + 2 ... + x = xC2
// we want to add free char, the '?', such that sum of #char-of-iC2 is minimised
// then fill the free char using the smallest available char first
class Solution {
public:
    
    vector<int> collect(string& s) {
        vector<int> out(26, 0);
        for (int i = 0; i < s.size(); i ++) {
            if (s[i] != '?') {
                out[s[i] - 'a'] ++;
            }
        }
        return out;
    }

    int countWildCard(string& s) {
        int sum = 0;
        for (int i = 0; i < s.size(); i ++) {
            if (s[i] =='?') sum ++;
        }
        return sum;
    }

    void addedFreq(vector<int>& freq, int toAdd) {
        for (int i = 0; i < toAdd; i ++) {
            int c = findMin(freq);
            freq[c] ++;
        }
    }



    int findMin(vector<int>& f) {
        int cha = -1;
        int c = 999999999;
        for (int i = 0; i < f.size(); i ++) {
            if (f[i] < c) {
                cha = i;
                c = f[i];
            }
        }
        return cha;
    }

    
    
    string minimiseStringValue(string s) {
       vector<int> freq = collect(s);
       int toAdd = countWildCard(s);
       addedFreq(freq, toAdd);
       print(freq);
       for (int i = 0; i < s.size(); i ++) {
        if (s[i] != '?') {
            freq[s[i] - 'a'] --;
        } 
       }
       for (int i = 0; i < s.size(); i ++) {
        if (s[i] == '?') {
            for (int j = 0; j < freq.size(); j ++) {
                if (freq[j] > 0) {
                    freq[j] --;
                    s[i] = (char) (j + 'a');
                    break;
                }
            }
            //s[i] = (char) (j + 'a');
        }
       }
       return s;

    }

    void print(vector<int> a) {
        for (int x : a) {
            cout << x << " ";
        }
        cout << endl;
    }
};

int main() {
    string s = "abcdefghijklmnopqrstuvwxy??";
    cout << Solution().minimiseStringValue(s);
}