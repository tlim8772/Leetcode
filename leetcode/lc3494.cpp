#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <typename T>
void print(vector<T> arr) {
    for (T t : arr) {
        cout << t << " ";
    }
    cout << endl;
}

class Solution {
public:

    ll findEndTime(int idx, vector<ll>& prevEnd, vector<int>& skill, vector<int>& mana) {
        ll start = prevEnd[0] + skill[0] * mana[idx];
        for (int i = 1; i < skill.size(); i ++) {
            start = (start < prevEnd[i]) ? prevEnd[i] + skill[i] * mana[idx] : start + skill[i] * mana[idx];
        }
        return start;
    }

    ll minTime(vector<int>& skill, vector<int>& mana) {
        vector<ll> prevEnd = vector<ll>(skill.size(), 0);
        for (int i = 0; i < skill.size(); i ++) {
            if (i == 0) {
                prevEnd[0] = skill[0] * mana[0];
            } else {
                prevEnd[i] = skill[i] * mana[0] + prevEnd[i - 1];
            }
        }
        //print(prevEnd);

        ll ans = prevEnd.back();
        for (int i = 1; i < mana.size(); i ++) {
            ll end = findEndTime(i, prevEnd, skill, mana);
            //cout << end << endl;

            if (i == mana.size() - 1) ans = end;

            for (int j = skill.size() - 1; j >= 0; j --) {
                if (j == skill.size() - 1) {
                    prevEnd[j] = end; 
                } else {
                    prevEnd[j] = prevEnd[j + 1] - skill[j + 1] * mana[i];
                }
            }
            
            //print(prevEnd);
        }

        return ans;

        
    }


};

int main() {
    Solution sol;
    vector<int> skill = {1};
    vector<int> mana = {299};

    cout << sol.minTime(skill, mana) << endl;
}