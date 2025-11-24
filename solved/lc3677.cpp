#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// if we have 2 slots the length of the palindrome can be 3 or 4
// if we have k slots, the length can be 2k - 1 or 2k

// to get the maximum 1st half 
// we compare the left half and the right half
// to be clear is len is odd the 2 halfs are (111) 1 (111) 
// if it is even it is (1111) (1111)
// if after reversing the left half and it is smaller than right half, we cannot blindy copy 
// the left half
// we must substract 1
// eg 110 010 cannot have 110 011
// so substract 1, 110 - 1 = 101

// for odd case, if reversed left half is smaller
// make the left half now contain the middle bit, then substract one

class Solution {
public:
    string llToBinaryString(ll n) {
        string s;
        while (n > 0) {
            s += to_string(n & 1);
            n >>= 1;
        }
        reverse(s.begin(), s.end());
        return s;
    }

    ll helper(int idx, const string& binString) {
        if (idx == binString.size()) return 1;

        if (binString[idx] == '1') {
            int put1 = helper(idx + 1, binString);
            int put0 = 1 << (binString.size() - idx - 1);
            return put1 + put0;
        } else {
            return helper(idx + 1, binString);
        }
    }

    string maxHalf(const string& binString) {
        string leftHalfStr = binString.substr(0, binString.size() / 2);
        string leftHalfReversedStr = leftHalfStr;
        reverse(leftHalfReversedStr.begin(), leftHalfReversedStr.end());
        string rightHalfStr = binString.substr((binString.size() + 1) / 2, binString.size() / 2);

        ll leftHalfReversedVal = stoll(leftHalfReversedStr, nullptr, 2);
        ll rightHalfVal = stoll(rightHalfStr, nullptr, 2);

        if (leftHalfReversedVal > rightHalfVal) {
            if (binString.size() % 2 == 0) {
                ll newLeftHalfVal = stoll(leftHalfStr, nullptr, 2) - 1;
                string newLeftHalfStr = llToBinaryString(newLeftHalfVal);
                
                if (newLeftHalfStr.size() < leftHalfStr.size()) {
                    return "INVALID";
                }
                return newLeftHalfStr;
            } else {
                int mid = binString.size() / 2;
                leftHalfStr += string(1, binString[mid]);
                ll newLeftHalfVal = stoll(leftHalfStr, nullptr, 2) - 1;
                string newLeftHalfStr = llToBinaryString(newLeftHalfVal);

                if (newLeftHalfStr.size() < leftHalfStr.size()) {
                    return "INVALID";
                }
                return newLeftHalfStr;

            }
        } else {
            if (binString.size() % 2 == 0) {
                return leftHalfStr;
            } else {
                return leftHalfStr + string(1, binString[binString.size() / 2]);
            }
        }

        
        
    }


    int countBinaryPalindromes(long long n) {
        if (n == 0) return 1;
        if (n == 1) return 2;

        string binString = llToBinaryString(n);
        ll cnt = 1; // include '0'

        int len = binString.size() - 1;
        int lim = (len + 1) / 2;
        for (int i = 1; i <= lim; i++) {
            if (i == lim) {
                if (i * 2 == len) {
                    cnt += 2 * (1 << (i - 1));
                } else {
                    cnt += 1 << (i - 1);
                }
            } else {
                cnt += 2 * (1 << (i - 1));
            }
        }
        //cout << cnt << endl;
        
        string halfStr = maxHalf(binString);
        int toAdd = (halfStr == "INVALID") ? 0 : helper(1, halfStr);
        //cout << halfStr << endl;
        //cout << toAdd << endl;
        cnt += toAdd;

        return cnt;
    }
};

int main() {
    Solution sol;
    
    cout << sol.countBinaryPalindromes(200) << endl;
}