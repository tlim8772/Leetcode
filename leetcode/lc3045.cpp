#include <vector>
#include <iostream>
using namespace std;

// use KMP to find longest prefix that is also a suffix in a string but be careful KMP requires prefix to be 'proper' (cannot be entire string)
// must handle when 2 strings are identical using end count
// then use Trie to query

void print(const vector<int>& a) {
    for (int x : a) {
        cout << x << " ";
    }
    cout << endl;
}

vector<int> prefix_function(string& s) {
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
    vector<int> out = {(int) s.size()};
    int cnt = pi[n - 1];
    while (cnt > 0) {
        out.push_back(cnt);
        cnt = pi[cnt - 1];
    }
    return out;
}

class Trie {
public:
    char c;
    vector<Trie*> childs;
    int currCount;
    int endCount;

    Trie(char c) {
        this->c = c;
        childs = vector<Trie*>(26, nullptr);
        currCount = 0;
        endCount = 0;
    }

    // we actually need to find all the lengths of all possible prefix-suffix including the fact the prefix suffix is the entire word itself
    static void insert(Trie* node, string& s, int index, vector<int>& longestPrefixSuffixs) {
        int curr = longestPrefixSuffixs[longestPrefixSuffixs.size() - 1];
        char c = s[index];
        if (node->childs[c - 'a'] == nullptr) {
            node->childs[c - 'a'] = new Trie(c);
        }
        if (curr == index + 1) {
            node->childs[c - 'a']->currCount += 1;
            longestPrefixSuffixs.pop_back();
        }
        if (index < s.size() - 1) {
            insert(node->childs[c - 'a'], s, index + 1, longestPrefixSuffixs);
        }
    }

    static int search(Trie* node, string& s, int index) {
        Trie* t = node->childs[s[index] - 'a'];
        if (t == nullptr) {
            return 0;
        } else if (index == s.size() - 1) {
            return (t == nullptr) ? 0 : t->currCount + t->endCount;
        } else {
            return search(t, s, index + 1);
        }
    }

};

long long countPrefixSuffixPairs(vector<string>& words) {
    long long cnt = 0;
    Trie* root = new Trie('$');
    
    vector<int>&& longestPrefixSuffixs = prefix_function(words[words.size() - 1]);
    Trie::insert(root, words[words.size() - 1], 0, longestPrefixSuffixs);
    for (int i = words.size() - 2; i >= 0; i --) {
        int ans = Trie::search(root, words[i], 0);
        //cout << ans << endl;
        cnt += (long long) ans;
        vector<int>&& lens = prefix_function(words[i]);
        Trie::insert(root, words[i], 0, lens);
    }
    return cnt;
}

int main() {
    vector<string> words = {"a","aba","ababa","aa"};
    cout << countPrefixSuffixPairs(words);
    
    

}
