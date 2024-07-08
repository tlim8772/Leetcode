#include <vector>
#include <iostream>
using namespace std;

int main() {
    vector<vector<int>> arr= {{2,2,2}};
    vector<int> a1 = {1, 2, 3};
    arr[0] = a1;
    arr[0][0] = 69;
    cout << a1[0] << endl;
    cout << arr[0][0] << endl;

}