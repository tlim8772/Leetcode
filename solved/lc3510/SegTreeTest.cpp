#include <bits/stdc++.h>
#include "SegTree.hpp"


void test1() {
    SegTree st(10);

    st.insert(0, 0, st.len - 1, 1, 10);
    st.insert(0, 0, st.len - 1, 3, 5);
    st.insert(0, 0, st.len - 1, 5, 4);
    printf("%d %lld %d\n", st.tree[0].best.i, st.tree[0].best.v, st.tree[0].wrongOrderCnt);

    st.del(0, 0, st.len - 1, 3);
    printf("%d %lld %d\n", st.tree[0].best.i, st.tree[0].best.v, st.tree[0].wrongOrderCnt);
}

void test2() {
    vector<int> arr = {3,1,4,2,5,6};

    SegTree st(arr);
    printf("%d %lld %d\n", st.tree[0].best.i, st.tree[0].best.v, st.tree[0].wrongOrderCnt);
    

    st.insert(0, 0, st.len - 1, 0, 4);
    st.del(0, 0, st.len - 1, 1);
    printf("%d %lld %d\n", st.tree[0].best.i, st.tree[0].best.v, st.tree[0].wrongOrderCnt);

    st.insert(0, 0, st.len - 1, 2, 5);
    st.del(0, 0, st.len - 1, 3);
    printf("%d %lld %d\n", st.tree[0].best.i, st.tree[0].best.v, st.tree[0].wrongOrderCnt);
}

void test3() {
    vector<int> arr = {4,1,4,6,3,6,2};
    SegTree st(arr);

    st.del(0, 0, st.len - 1, 3);
    st.del(0, 0, st.len - 1, 4);
    cout << st.findNext(0, 0, st.len - 1, 2) << endl;

    st.del(0, 0, st.len - 1, 5);
    cout << st.findNext(0, 0, st.len - 1, 2) << endl;

    st.insert(0, 0, st.len - 1, 4, 2);
    cout << st.findNext(0, 0, st.len - 1, 2) << endl;
    printf("%d %lld %d\n", st.tree[0].best.i, st.tree[0].best.v, st.tree[0].wrongOrderCnt);

    cout << st.findNext(0, 0, st.len - 1, 1) << endl;

}

void test4() {
    vector<int> nums = {999999999, 999999998, 999999997, 999999996, 999999995};
    //vector<ll> nums2 = {9,8,7,6,5};
    SegTree st(nums);

    int cnt = 0;
    while (st.tree[0].wrongOrderCnt > 0) {
        Pair best = st.tree[0].best;
        st.insert(0, 0, st.len - 1, best.i, best.v);

        int next = st.findNext(0, 0, st.len - 1, best.i);
        st.del(0, 0, st.len - 1, next);
        printf("%d %lld %d\n", st.tree[0].best.i, st.tree[0].best.v, st.tree[0].wrongOrderCnt);
        cnt ++;
    }
    cout << cnt << endl;
}

int main() {
    test3();
}
