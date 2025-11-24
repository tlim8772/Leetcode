#include <bits/stdc++.h>
using namespace std;

// simple dp
// dp(i, prev) = min cost to make s[i..len - 1] a good caption, given that s[0..i-1] is already a good caption
// we make 3 consecutive characters at one time, or we can make s[i] the prev char

// problem comes when we have to compare lexicography with the case when we make only this char == prev
// or choose a new char to set the next 3 char with
// we kind of have to get the next 2 char for the 1st case
// interestingly ans is correct if prev <= takeNewChosen
// (here prev = prev char - 'a', takeNewChosen = take new char - 'a')

// the proof is simple
// 1st note that in this case prev == takeNewChosen, then
// the solution from setting the next 3 char is also a valid solution for when we set i to prev
// eg: here i is the leftmost char index
// a?????? (take prev)
// aaa???? (take new 3)
// clearly the solution for take new 3 is also a feasible solution for take prev
// so take prev can only be better by being lexicographically better

struct Route {
    int c = -1, l = -1, next = -1;
};

class Solution {
public:
    int str_len;
    vector<int> store;
    vector<Route> router;

    inline int coor(int i, int prev) {
        if (i >= str_len) return -1;
        return i * 26 + prev;
    }

    // s.size() - i >= 3
    inline int helper(char c, int i, const string& s) {
        int cost = 0;
        for (int j = i; j < min(i + 3, (int) s.size()); j++) {
            cost += abs(c - s[j]);
        }
        return cost;
    }

    string getNext2(int i, int prev) {
        int pos = coor(i, prev);
        string out = "";

        while (out.size() < 2) {
            const Route& r = router[pos];
            out.append(min(r.l, 2 - (int) out.size()), r.c + 'a');
            pos = r.next;
        }

        return out;
    }

    int dp(int i, int prev, const string& s) {
        if (i >= s.size()) {
            return 0;
        } 
        
        int pos = coor(i, prev);
        if (store[pos] != -1) {
            return store[pos];
        }

        if (s.size() - i < 3) {
            // must make these char == prev already
            store[pos] = helper('a' + prev, i, s);
            router[pos] = {.c = prev, .l = (int) s.size() - i, .next = -1};
        } else if (i == 0) {
            // if i == 0, we can choose any start char, prev does not matter;
            int best = 999999999;
            int chosen = -1;
            int next = -1;
            for (char c = 'a'; c != 'z' + 1; c++) {
                int cost = helper(c, i, s);
                int ans = cost + dp(i + 3, c - 'a', s);

                if (ans < best) {
                    best = ans;
                    chosen = c - 'a';
                    next = coor(i + 3, c - 'a');
                }
            }

            store[pos] = best;
            router[pos] = {.c = chosen, .l = 3, .next = next};
        } else {
            // case 1: take prev char
            int takePrev = abs(s[i] - prev - 'a') + dp(i + 1, prev, s);

            // case 2: take a new char
            int takeNew = 999999999;
            int takeNewChosen = -1;
            int takeNewNext = -1;
            for (char c = 'a'; c != 'z' + 1; c++) {
                int cost = helper(c, i, s);
                int ans = cost + dp(i + 3, c - 'a', s);

                if (ans < takeNew) {
                    takeNew = ans;
                    takeNewChosen = c - 'a';
                    takeNewNext = coor(i + 3, c - 'a');
                }
            }

            int whicOne = 0;
            //string takePrev3Chars = string(1, prev + 'a') + getNext2(i + 1, prev);
            //string takeNext3Chars = string(3, takeNewChosen + 'a');
            //cout << takePrev3Chars << endl;
            if (takePrev < takeNew || (takePrev == takeNew && prev <= takeNewChosen)) {
                store[pos] = takePrev;
                router[pos] = {.c = prev, .l = 1, .next = coor(i + 1, prev)};
            } else {
                store[pos] = takeNew;
                router[pos] = {.c = takeNewChosen, .l = 3, .next = coor(i + 3, takeNewChosen)};
            }

        }
        
        return store[pos];

       
    }


    string minCostGoodCaption(string caption) {
        if (caption.size() < 3) {
            return "";
        }

        str_len = caption.size();
        store = vector(caption.size() * 26, -1);
        router = vector<Route>(caption.size() * 26, Route());

        int ans = dp(0, 0, caption);
        //cout << ans << endl;
        string out;
        int curr = 0;
        while (curr != -1) {
            const Route r = router[curr];
            out.append(max(r.l, 0), r.c + 'a');
            curr = r.next;
        }

        return out;
    }
};

int main() {
    Solution sol;

    string caption = "cdcd";
    string ans = sol.minCostGoodCaption(caption);
    cout << ans << endl;
}