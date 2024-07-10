#include <vector>
#include <iostream>
using namespace std;

template <typename T>

void printVector(vector<T> a) {
    for (int i = 0; i < a.size(); i ++) {
        cout << a[i] << " ";
    }
    cout << endl;
}


vector<int> zAlgo(string s) {
    vector<int> out = vector<int>(s.size(), 0);
    out[0] = s.size();
    int l = 1;
    int r = 0;
    int count = 1;
    while (count < s.size()) {
        if (l > r) {
            if (s[l] != s[0]) {
                out[l] = 0;
                count += 1;
                l += 1;
            } else {
                r = l;
                while (r + 1 < s.size() && s[r + 1] == s[r + 1 - l]) {
                    r += 1;
                }
                out[l] = r - l + 1;
                count += 1;
            }
        } else if (l == r) {
            l += 1;
        } else {
            int p = l + 1;
            while (true) {
                int len = out[p - l];
                if (p + len - 1 < r) {
                    out[p] = len;
                    count += 1;
                    p += 1;
                    if (p > r) {
                        l = p;
                        break;
                    }
                } else {
                    l = p;
                    while (r + 1 < s.size() && s[r + 1] == s[r + 1 - l]) {
                        r += 1;
                    }
                    out[l] = r - l + 1;
                    count += 1;
                    break;
                }
            }
        }
    }
    return out;
}

vector<int> beautifulIndexes(string s, string a) {
    string str = a + "#" + s;
    vector<int>&& z = zAlgo(str);
    //printVector(z);
    vector<int> out = vector<int>();
    for (int i = a.size() + 1; i < z.size(); i ++) {
        //cout << z[i] << " " << a.size() << endl;
        if (z[i] == a.size()) {
            out.push_back(i - a.size() - 1);
        }
    }
    //cout << out.size() << endl;
    return out;
}

vector<int> beautifulIndices(string s, string a, string b, int k) {
    vector<int>&& beauA = beautifulIndexes(s, a);
    vector<int>&& beauB = beautifulIndexes(s, b);
    if (beauA.size() == 0 || beauB.size() == 0) {
        return {};
    }
    printVector(beauA);
    printVector(beauB);
    
    vector<int> out = vector<int>();
    int pA = 0;
    int pB = 0;
    while (pA < beauA.size()) {
        int iA = beauA[pA];
        int iB = beauB[pB];
        if (abs(iA - iB) <= k) {
            out.push_back(iA);
            pA += 1;
        } else if (iA < iB) {
            pA += 1;
        } else {
            if (pB == beauB.size() - 1) {
                break;
            }
            pB += 1;
            //pA += 1;
        }
    }
    return out;        
}

int main() {
    //string s = "isawsquirrelnearmysquirrelhouseohmy";
    vector<int>&& ans = beautifulIndices("svpbvld", "d", "svpbv", 2);
    printVector(ans);
}