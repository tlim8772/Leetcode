#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;

class Solution {
public:
     vector<vector<int>> findMatrix(vector<int>& nums) {
        unordered_map<int, int> freqMap;
        int maxCount = -1;
        for (int i = 0; i < nums.size(); i ++) {
            freqMap[nums[i]] += 1;
            maxCount = max(maxCount, freqMap[nums[i]]);
        }
        vector<vector<int>> out = vector(maxCount, vector(0, 0));
        for (auto it = freqMap.begin(); it != freqMap.end(); it ++) {
            int key = it->first;
            int count = it->second;
            for (int i = 0; i < count; i ++) {
                out[i].push_back(key);
            }
        }
        return out;
    }
};