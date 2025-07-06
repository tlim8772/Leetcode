#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll NEG = -1e15;

// well tried using unique_ptr get MLE (and probably TLE later on)

struct Node {
    ll res = NEG;
    Node *l = nullptr, *r = nullptr;
};

// update: update idx i with value v
// query: get max value in range [l, r]
struct SegTree {
    int S = -1000100000, E = 1000000000;
    Node *root;

    void update(Node *&ptr, int s, int e, int i, ll v) {
        if (ptr == nullptr) {
            ptr = new Node();
        }

        if (s == e) {
            ptr->res = v;
            return;
        }

        int m = s + ((e - s) >> 1);
        if (i <= m) {
            update(ptr->l, s, m, i, v);
        } else {
            update(ptr->r, m + 1, e, i, v);
        }

        ll lsum = ptr->l == nullptr ? NEG : ptr->l->res;
        ll rsum = ptr->r == nullptr ? NEG : ptr->r->res;
        ptr->res = max(lsum, rsum);
    }

    // if [l, r] has no entries, return a very neg number
    ll query(Node *&ptr, int s, int e, int l, int r) {
        if (ptr == nullptr) {
            return NEG;
        } else if (s == e || (s == l && e == r)) {
            return ptr->res;
        }

        int m = s + ((e - s) >> 1);
        if (r <= m) {
            return query(ptr->l, s, m, l, r);
        } else if (l > m) {
            return query(ptr->r, m + 1, e, l, r);
        } else {
            ll lres = query(ptr->l, s, m, l, m);
            ll rres = query(ptr->r, m + 1, e, m + 1, r);
            return max(lres, rres);
        }
    }
};

class Solution {
public:
    long long maxBalancedSubsequenceSum(vector<int>& nums) {
        SegTree st;
        ll ans;

        st.update(st.root, st.S, st.E, nums[0], nums[0]);
        ans = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            ll best = st.query(st.root, st.S, st.E, st.S, nums[i] - i);
            ll myAns = max(best + nums[i], (ll) nums[i]);
            ans = max(ans, myAns);

            st.update(st.root, st.S, st.E, nums[i] - i, myAns);
        }

        return ans;
    }
};

int main() {
    Solution sol;

    vector<int> arr = {575620823,479033595,886887886,-852474608,-420672886,737934355,250403064,224283339,-384976809,-987461626,136509483,-129866226,-50565237,-154338484,371077418,272664294,-814150532,282117543,-674366550,980489639,478540645,524203028,441371360,931402588,631069517,-440061776,-349919062,-997020816,-673216767,-967823902,-147997697,657232417,-494078349,-992757880,-266413795,-777674117,368378534,-375023270,-254102878,622258046,812136726,129723835,385726066,967687286,413321239,893607725,-418185339,969104215,-210035992,106222252,-780639712,-453627658,408765,73492241,134247969,-43313029,458832315,-733286392,830315216,-46271051,-409056279,371769566,-377983919,-684016074,191191576,155393414,688854167,-862076015,85180768,-243038107,743938595,-342865814,292132080,-714507316,147251588,94112383,-358927530,700323565,-368012981,197539072,708268772,254071579,606822947,-489399226,-679189244,665305192,-769036220,430483104,-318526174,414100547,-297904159,480799012,-735010777,108672899,700609431,-161130210,869362253,-704822568,216612973,-260100677,-721625345,278757454,-584467200,-883426202,550827022,467127468,593877505,-881835983,-173050545,-364289198,36917255,527300781,176637416,-936500748,220839201,-529943007,699610346,490713426,-597641135,12258605,-817658657,898907036,-908524193,-275203042,-87568409,717950938,984379061,280574937,862009093,582974077,-323812156,176370,-292822669,-160968769,503188602,-914880597,-750451047,-304156511,-398869607,272163701,-927180124,352367475,25473538,-385461217,744034846,-979839284,655013553,324567817,-556275677,731850874,-191777741,351705580,205443907,742400276,-174827408,752240530,-953151888,-477679296,428916743,780568367,805817853,-764514879,923422290,-705001082,-594889405,-584548133,-789549180,746549311,-906594869,552042120,409194293,867152288};
    cout << sol.maxBalancedSubsequenceSum(arr) << endl;


}