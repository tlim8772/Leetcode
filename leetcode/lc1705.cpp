#include <vector>
#include <queue>
#include <iostream>
using namespace std;



class Solution {
public:
    // we always eat the apple that is going to rot first
    // suppose not
    // case 1 : i optimal solution, apple rot first eaten, some days later
    // we can switch with the apple we eaten on this day, still get optimal solution
    // case 2: in optimal solution , apple rot first not eaten
    // replace apple we ate on this day with apple rot first, still get optimal solution
    
    class Compare {
    public:
        bool operator() (vector<int>& x, vector<int>&y) {
            return x[1] > y[1];
        }
    };


    int eatenApples(vector<int>& apples, vector<int>& days) {
        priority_queue<vector<int>, vector<vector<int>>, Compare> pq;
        int day = 0;
        int count = 0;
        while (day < apples.size() || !pq.empty()) {
            if (day < apples.size()) {
                pq.push({apples[day], days[day] + day});
            }
            //day += 1;
            while (!pq.empty()) {
                vector<int> apple = pq.top();
                //pq.pop();
                //cout << apple[0] << endl;
                if (apple[1] > day && apple[0] > 0) {
                    pq.pop();
                    count += 1;
                    pq.push({apple[0] - 1, apple[1]});
                    break;
                }
                pq.pop();
            }
            day += 1;
        }
        return count;
    }
};

int main() {
    vector<int> apples = {3,0,0,0,0,2};
    vector<int> days = {3,0,0,0,0,2};
    Solution s;
    cout << s.eatenApples(apples, days) << endl;
}