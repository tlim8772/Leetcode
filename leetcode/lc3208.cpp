#include <bits/stdc++.h>
using namespace std;

// find all maximal alternating ranges
// if there exist a maximal group covering the entire circle
// then 2 cases, the 1st and last are alternating
// or both same color

// if it is full circle, with start, end also alternating the answer is the size of the colors array
// because we can start from any element
// otherwise answer is lengtg of maximal range - k + 1

class Solution {
public:

    int numberOfAlternatingGroups(vector<int>& colors, int k) {
        vector<tuple<int,int,int>> ranges;
        vector<bool> visited(colors.size(), false); // ranges stored in clockwise order

        for (int i = 0; i < colors.size(); i++) {
            if (visited[i]) continue;
            visited[i] = true;
            int start = i, end = i, cnt = 1;

            // we find the end first,
            // this will also handle the case when the entire circle (with start end also alternating)
            // is good
            
            while (true) {
                int next = (end + 1) % colors.size();
                if (colors[end] != colors[next]) {
                    cnt++;
                    end = next;
                    visited[next] = true;
                    
                    if (end == start) {
                        cnt--; // we count one more
                        break;
                    }
                } else {
                    break;
                }
            }
            
            if (start == end && cnt == colors.size()) {
                goto finally;
            }
            
            while (true) {
                int prev = ((start - 1) + colors.size()) % colors.size();
                if (colors[start] != colors[prev]) {
                    cnt++;
                    start = prev;
                    visited[prev] = true;
                } else {
                    break;
                }
            }

            finally:
                ranges.push_back(tuple{start, end, cnt});
        }

        int ans = 0;
        for (const auto& res : ranges) {
            const auto& [start, end, cnt] = res;
            //cout << start << " " << end << " " << cnt << endl;
            if (start == end && cnt == colors.size()) {
                ans = colors.size();
            } else {
                ans += (k > cnt) ? 0 : cnt - k + 1;
            }
            
        }

        return ans;
    }
};

int main() {
    Solution sol;

    vector<int> colors = {1,1,0,1};
    int k = 4;
    cout << sol.numberOfAlternatingGroups(colors, k) << endl;;
}