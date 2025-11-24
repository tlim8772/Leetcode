#include <iostream>
using namespace std;
long long MAX = 0xffffffffffffffff;

long long  totalPrice(long long num, int x) {
    long long count = 0;
    for (int i = x; i <= 64; i += x) {
        //long long bm = 1 << (i - 1);
        int set = (num >> (i - 1)) & 1;
        //cout << set << endl;
        if (set == 1) {
            long long sameL = 1;
            long long lessL = ((num >> i) == 0) ? 0 : num >> i;
            long long sameR = (num & ((1 << (i - 1)) - 1)) + 1;
            //cout << sameR << endl;
            long long lessR = (1 << (i - 1));
            long long add = sameL * sameR + lessL * lessR;
            //cout << add << " " << "1" << endl;
            count += add;
        } else {
            if (i == 64) {
                continue;
            }
            //long long sameL = 0;
            long long lessL = ((num >> i) == 0) ? 0 : (num >> i);
            //cout << lessL << endl;
            //long long sameR = (num << (64 - i)) >> (64 - i);
            long long lessR = 1 << (i - 1);
            long long add = lessL * lessR;
            //cout << add <<" "<< "0" << endl;
            count += add;
        }
    }
    return count;
}

long long binarySearch(long long s, long long e, long long k, int x) {
    if (s >= e) {
        return s;
    } else {
        long long m = ((s + e) % 2 == 0) ? (s + e) / 2 : (s + e) /2 + 1;
        long long price = totalPrice(m, x);
        if (price <= k) {
            return binarySearch(m, e, k, x);
        } else {
            return binarySearch(s, m - 1, k, x);
        }
    }
}

int main() {
    //cout << totalPrice(999999, 2) << endl;
    cout << binarySearch(1, 999999, 7, 2);
}
