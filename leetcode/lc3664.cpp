#include <bits/stdc++.h>
using namespace std;
// suppose x = 'a'
// case 1: the 2 cards have 'a' in different positions
// then one of them has to be 'aa'

// case 2: the 2 cards have 'a' in the same positions
// then the other char can be anything

// split into 2 groups
// 'aa', 'a?' and '?a'
// name them g1, g2, g3

// difficult greedy, i gave up
// consider the problem where we have to maximise pairs in a set where pairs cannot be of same element
// the ans is simple, find the elem that occurs the most. if it is <= size of set / 2, then ans is size / 2
// if not, then ans is size - # of elem that occurs the most
// proof
// 2nd case is easy
// for 1st case, suppose not
// then have some elems left, and they are of the same value
// since # of elem <= size / 2,
// number of pairs not using that elem is (size / 2) - (# of that elem - # of that elem left)
// and since # of that elem is <= half, suppose is == size / 2
// we get exactly (# of the elem left)
// then we can split these pairs to use the leftovers

// for all i in 0..g1
// add i of 'aa' to g1, then solve , then add remainder to g2 then solve

class Solution {
public:

    // counts contain the count of each elem, 0 can occur
    int pairUp(const vector<int>& counts) {
        int most = 0;
        int sum = 0;
        for (int x : counts) {
            most = max(most, x);
            sum += x;
        }

        if (most <= sum / 2) {
            return sum / 2;
        } else {
            return sum - most;
        }
    }


    int score(vector<string>& cards, char x) {
        int g1 = 0, g2 = 0, g3 = 0;
        vector<int> set2('j' - 'a' + 1, 0);
        vector<int> set3 = set2;

        for (const string& card : cards) {
            if (card[0] == x && card[1] == x) {
                g1++;
            } else if (card[0] == x) {
                set2[card[1] - 'a']++;
                g2++;
            } else if (card[1] == x) {
                set3[card[0] - 'a']++;
                g3++;
            }
        }

        int best = 0;
        for (int i = 0; i <= g1; i++) {
            set2.push_back(i);
            set3.push_back(g1 - i);

            int ans = pairUp(set2) + pairUp(set3);
            best = max(best, ans);

            set2.pop_back();
            set3.pop_back();
        }   

        return best;


      
    }
};

int main() {
    Solution sol;

    vector<string> cards = {"ab","aa","ab","bc","cc","bc","bb","ac","bc","bc","aa","aa","ba","bc","cb","ba","ac","bb","cb","ac","cb","cb","ba","bc","ca","ba","bb","cc","cc","ca","ab","bb","bc","ba","ac","bc","ac","ac","bc","bb","bc","ac","bc","aa","ba","cc","ac","bb","ba","bb"};
    char x = 'b';

    cout << sol.score(cards, x) << endl;
}