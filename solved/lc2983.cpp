#include <bits/stdc++.h>
using namespace std;

// we reverse the 2nd half of the string.
// then for query A, B, C, D, convert, C, D to N - 1 - D, N - 1 - C

// case 1: the 2 intervals intersect
// let 1st_cut = min(A, C), we need to check if the substring s[0:1st_cut) and s[N/2:N/2+1st_cut) are the same.
// then from min(A, C) to max(A, C) we need to subtract the character frequency.
// same for min(B, D) + 1 to max(B, D).

// case 2: the 2 intervals do not intersect
// still convert C, D, but we need to check for string equality for the middle section, 
// i.e range [min(B,D) + 1, max(A,C)).

struct Helper {
    int len;
    vector<int> sa;
    vector<int> idx_to_pos;
    vector<int> lcp;
    vector<vector<int>> st;
    function<bool(array<int,3>&, array<int,3>&)> cmp = [] (array<int,3>& p1, array<int,3>& p2) { 
        return p1[1] == p2[1] ? p1[2] < p2[2] : p1[1] < p2[1];
    };

    Helper(const string& s) {
        get_sa(s);
        //for (int x : sa) cout << x << " ";
        //cout << endl;
        
        get_lcp(s);
        //for (int x : lcp) cout << x << " ";
        //cout << endl;
        
        get_sparse_table();
    }

    void radix_sort(vector<array<int,3>>& ranks) {
        static vector<vector<array<int,3>>> bins;
        
        bins.resize(max(26, (int) ranks.size() + 1));

        for (int i = 2; i > 0; i--) {
            for (auto it = ranks.rbegin(); it != ranks.rend(); it++) {
                bins[(*it)[i]].push_back(*it);
            }
            ranks.clear();
            for (auto& b : bins) {
                ranks.insert(ranks.end(),b.rbegin(), b.rend());
                b.clear();
            }
        }
    }

    void rerank(int p, vector<array<int,3>>& sorted_ranks) {
        static vector<int> idx_to_pos;
        static vector<int> temp;
        
        idx_to_pos.resize(sorted_ranks.size());
        temp.resize(sorted_ranks.size());
        
        for (int i = 0; i < sorted_ranks.size(); i++) {
            idx_to_pos[sorted_ranks[i][0]] = i;
        }

        temp[0] = 1;
        for (int i = 1; i < sorted_ranks.size(); i++) {
            auto &curr = sorted_ranks[i], &prev = sorted_ranks[i - 1];
            if (curr[1] == prev[1] && curr[2] == prev[2]) {
                temp[i] = temp[i - 1];
            } else {
                temp[i] = temp[i - 1] + 1;
            }
        }

        for (int i = 0; i < sorted_ranks.size(); i++) {
            auto& [idx, r1, r2] = sorted_ranks[i];
            r1 = temp[i];
            int next = (idx + (1 << (p - 1)));
            r2 = (next >= sorted_ranks.size()) ? 0 : temp[idx_to_pos[next]];
        }

        //sort(sorted_ranks.begin(), sorted_ranks.end(), cmp);
        radix_sort(sorted_ranks);
    }

    void get_sa(const string& s) {
        vector<array<int,3>> ranks;
        ranks.resize(s.size());
        for (int i = 0; i < s.size(); i++) {
            auto& [idx, r1, r2] = ranks[i];
            idx = i;
            r1 = s[i] - 'a';
            r2 = (i == s.size() - 1) ? 0 : s[i + 1] - 'a';
        }
        radix_sort(ranks);

        int p = 2;
        while (1) {
            rerank(p, ranks);
            if ((1 << p) >= s.size()) break;
            p++;
        }

        sa.resize(s.size());
        for (int i = 0; i < s.size(); i++) sa[i] = ranks[i][0];
    }

    void get_lcp(const string& s) {
        lcp.resize(s.size());

        idx_to_pos.resize(s.size());
        for (int i = 0; i < sa.size(); i++) idx_to_pos[sa[i]] = i;

        int h = 0;
        for (int i = 0; i < s.size(); i++) {
            int my_pos = idx_to_pos[i];
            if (my_pos == 0) continue;
            int prev_idx = sa[my_pos - 1];
            
            h = max(0, h - 1);
            int lim = min(s.size() - i, s.size() - prev_idx);
            for (; h < lim; h++) {
                if (s[i + h] != s[prev_idx + h]) break;
            }
            
            lcp[my_pos] = h;
        }
    }

    void get_sparse_table() {
        int max_len = 32 - __builtin_clz(lcp.size()) - 1;
        st = vector(sa.size(), vector(max_len + 1, 0));

        for (int i = 0; i < lcp.size(); i++) {
            st[i][0] = lcp[i];
        }

        for (int p = 1; p <= max_len; p++) {
            for (int i = 0; i < lcp.size(); i++) {
                int next = i + (1 << (p - 1));
                if (next >= lcp.size()) {
                    st[i][p] = st[i][p - 1];
                } else {
                    st[i][p] = min(st[i][p - 1], st[next][p - 1]);
                }
            }
        }
    }

    // given a string s, check if s[i,i+l-1] == s[j,j+l-1].
    // i != j
    bool query(int i, int j, int l) {
        int pos_i = idx_to_pos[i], pos_j = idx_to_pos[j];
        if (pos_i > pos_j) swap(pos_i, pos_j);
        pos_i++;

        int len = pos_j - pos_i + 1;
        int pow_2 = 32 - __builtin_clz(len) - 1;
        int mi = min(st[pos_i][pow_2], st[pos_j - (1 << pow_2) + 1][pow_2]);
        return mi >= l;
    }
};


class Solution {
public:
    vector<array<int,26>> prefix_sums;

    void get_prefix_sums(const string& s) {
        prefix_sums.resize(s.size());
        
        for (int c = 0; c < 26; c++) {
            if (c == s[0] - 'a') {
                prefix_sums[0][c] = 1;
            } else {
                prefix_sums[0][c] = 0;
            }
        }

        for (int i = 1; i < s.size(); i++) {
            for (int c = 0; c < 26; c++) {
                int prev = prefix_sums[i - 1][c], &curr = prefix_sums[i][c];
                if (c == s[i] - 'a') {
                    curr = prev + 1;
                } else {
                    curr = prev;
                }
            }
        }
    }

    array<int,26> query(int l, int r) {
        if (l == 0) return prefix_sums[r];

        auto &left = prefix_sums[l - 1], &right = prefix_sums[r];
        array<int,26> out;
        for (int c = 0; c < 26; c++) out[c] = right[c] - left[c];
        return out;
    }


    vector<bool> canMakePalindromeQueries(string s, vector<vector<int>>& queries) {
        int N = s.size();
        reverse(s.begin() + N / 2, s.end());
        
        Helper helper{s};
        get_prefix_sums(s);
        
        vector<bool> out(queries.size(), false);
    
        for (int pos = 0; pos < queries.size(); pos++) {
            auto& q = queries[pos];

            int l1 = q[0],  r1 = q[1];
            int l2 = N - 1 - q[3], r2 = N - 1 - q[2];

            int first_cut = min(l1, l2);
            if (first_cut > 0) {
                bool check = helper.query(0, N / 2, first_cut);
                if (!check) continue;
            }

            int last_cut = max(r1, r2);
            if (last_cut < N / 2 - 1) {
                bool check = helper.query(last_cut + 1, last_cut + 1 + N / 2, N / 2 - last_cut - 1);
                if (!check) continue;
            }

            

            array<int,26> prefix1 = query(l1, r1), prefix2 = query(N/2 + l2, N/2 + r2);
            
            // TODO: handle the case [l1, r1] and [l2, r2] are disjoint
            if (r1 < l2 || r2 < l1) {
                int middle_cut = min(r1, r2) + 1;
                int len = max(l1, l2) - middle_cut;
                bool check = (len == 0) ? true : helper.query(middle_cut, middle_cut + N/2, len);
                if (!check) continue;

                for (int i = l1; i <= r1; i++) {
                    int c = s[i + N/2] - 'a';
                    prefix1[c]--;
                }

                for (int i = l2; i <= r2; i++) {
                    int c = s[i] - 'a';
                    prefix2[c]--;
                }

                int i = 0;
                for (; i < 26; i++) {
                    int x1 = prefix1[i], x2 = prefix2[i];
                    if (x1 != 0 || x2 != 0) break;
                }
                out[pos] = i == 26;
                continue;
            }
            
            if (l1 < l2) {
                for (int i = l1; i < l2; i++) {
                    int c = s[i + N/2] - 'a';
                    prefix1[c]--;
                } 
            } else if (l1 > l2) {
                for (int i = l2; i < l1; i++) {
                    int c = s[i] - 'a';
                    prefix2[c]--;
                }
            }

            if (r1 < r2) {
                for (int i = r1 + 1; i <= r2; i++) {
                    int c = s[i] - 'a';
                    prefix2[c]--;
                }
            } else if (r1 > r2) {
                for (int i = r2 + 1; i <= r1; i++) {
                    int c = s[i + N/2] - 'a';
                    prefix1[c]--;
                }
            }

            int i = 0;
            for (;i < 26; i++) {
                int x1 = prefix1[i], x2 = prefix2[i];
                if (x1 < 0 || x2 < 0 || x1 != x2) break;
            }

            out[pos] = i == 26;
        }

        return out;
    }
};




int main() {
    string s = "bbccbb";
    vector<vector<int>> queries = {{2,2,5,5}};
   
    Solution sol;
    vector<bool> res = sol.canMakePalindromeQueries(s, queries);
    for (int b : res) cout << b << " ";
    cout << endl;
}