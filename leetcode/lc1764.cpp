#include <vector>
#include <iostream>
using namespace std;

// use kmp to match all words in O(len(nums) + sum(len(group))) time
vector<int> prefix_function(vector<int>& s) {
    int n = s.size();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i-1];
        while (j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}

bool canFitAll(vector<int>& nums, vector<vector<int>>& groups, int g, int index) {
    if (g >= groups.size()) {
        return true;
    } else {
        vector<int>& group = groups[g];
        vector<int>&& kmp = prefix_function(group);
        int p1 = index;
        int p2 = 0;
        while (p1 < nums.size() && p2 < group.size()) {
            //cout << g << " " << index << " " << p1 << " " << p2 << endl;
            if (group[p2] == nums[p1]) {
                cout << group[p2] << " " << nums[p1] << endl;
                p2 ++;
                p1 ++;
            } else {
                if (p2 == 0) {
                    p1 ++;
                } else {
                    p2 = kmp[p2 - 1];
                }
            }
        }
        if (p2 == group.size()) {
            //cout << p1 << endl;
            return canFitAll(nums, groups, g + 1, p1);
        } else {
            return false;
        }

    }
}

void print(vector<int> a) {
    for (int x : a) {
        cout << x << " ";
    }
    cout << endl;
    
}



int main() {
    vector<vector<int>> groups = {{2,1}};
    vector<int> nums = {12,1};
    
    vector<int> prefix = prefix_function(nums);
    //print(prefix);
    cout << canFitAll(nums, groups, 0, 0);
}
