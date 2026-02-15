#include <bits/stdc++.h>
using namespace std;

// 2 pointer sliding window, because a subarray inside a subarray will always have a lesser difference
// between the min elem and max elem.
// use monotonic queue to get the range min and max.
// to get max xor for a range, use a trie.
// we insert the prefix xor, i.e for index i, we insert xor[0..i].
// when we search for index i to index j, we have a mask xor[0..i - 1].
// this allows us to search accordingly in the trie, i.e if mask[i] = 0, we take the
// 1 edge if possible, if mask[i] = 1, we take the 0 edge if possible.

struct Node {
    int cnt = 0;
    array<Node*, 2> nexts;
};

struct Trie {
    int LEN = 15;
    vector<Node> store;
    Node *root = nullptr;

    Trie() {
        store.reserve(1000000);
        root = make_node();
    }

    Node* make_node() {
        store.emplace_back();
        return &store.back();
    }

    void init(int& p, Node*& curr) {
        p = LEN - 1;
        curr = root;
    }

    void insert(int x, int p = -2, Node* curr = nullptr) {
        //if (p == -2) cout << "insert " << x << endl;
        if (p == -1) return;
        if (p == -2) init(p, curr);
        int digit = (x >> p) & 1;
        Node*& next = curr->nexts[digit];
        if (next == nullptr) next = make_node();
        next->cnt++;
        insert(x, p - 1, next);
    }  

    // user must ensure x is inside the trie
    void remove(int x, int p = -2, Node* curr = nullptr) {
        //if (p == -2) cout << "remove " << x << endl;
        if (p == -1) return;
        if (p == -2) init(p, curr);
        int digit = (x >> p) & 1;
        Node* next = curr->nexts[digit];
        remove(x, p - 1, next);
        next->cnt--;
    }

    int find_max(int mask, int p = -2, Node* curr = nullptr) {
        if (p == -1) return 0;
        if (p == -2) init(p, curr);
        int mask_digit = (mask >> p) & 1;
        if (auto a = curr->nexts[!mask_digit]; a != nullptr && a->cnt > 0) {
            return (1 << p) + find_max(mask, p - 1, a);
        } else if (auto b = curr->nexts[mask_digit]; b != nullptr && b->cnt > 0) {
            return find_max(mask, p - 1, b);
        } else {
            return 0;
        }
    }
};

template <typename T, typename Cmp>
struct MonotonicQueue{
    Cmp cmp;
    deque<pair<int, T>> que;

    MonotonicQueue() {}

    MonotonicQueue(Cmp cmp): cmp(cmp) {}

    void push(int i, T val) {
        while (!que.empty() && cmp(val, que.back().second)) que.pop_back();
        que.push_back({i, val});
    }

    void pop(int i) {
        if (!que.empty() && que.front().first == i) que.pop_front();
    }

    bool empty() {
        return que.empty();
    }

    optional<T> get_res() {
        return (!que.empty()) ? optional<T>(que.front().second) : optional<T>();
    }

};

class Solution {
public:
    int maxXor(vector<int>& nums, int k) {
        MonotonicQueue<int, less<int>> min_queue;
        MonotonicQueue<int, greater<int>> max_queue;
        Trie trie;
        vector<int> prefix_xor(nums.size(), 0);
        
        for (int store = 0, i = 0; i < nums.size(); i++) {
            prefix_xor[i] = store ^= nums[i];
        }

        int mi = nums[0], ma = nums[0];
        min_queue.push(0, nums[0]);
        max_queue.push(0, nums[0]);
        trie.insert(nums[0]);
        int s = 0, e = 1;
        int best = 0;
        for (int i = 0; i < nums.size(); i++) {
            while (e < nums.size()) {
                mi = min_queue.get_res().value_or(999999);
                ma = max_queue.get_res().value_or(-1);
                if (max(ma, nums[e]) - min(mi, nums[e]) > k) break;
                
                min_queue.push(e, nums[e]);
                max_queue.push(e, nums[e]);
                trie.insert(prefix_xor[e]);
                e++;
            }

            int mask = (i == 0) ? 0 : prefix_xor[i - 1];
            int ans = trie.find_max(mask);
            best = max(best, ans);

            min_queue.pop(i);
            max_queue.pop(i);
            trie.remove(prefix_xor[i]);
            


        }

        return best;  
    }
};

void test() {
    Trie trie;
    trie.insert(5);
    trie.insert(4);
    trie.insert(5);
    assert(trie.find_max(0) == 5);
    assert(trie.find_max(5) == 1);
    
    trie.remove(5);
    assert(trie.find_max(0) == 5);
    
    trie.remove(5);
    cout << trie.find_max(0) << endl;

    cout << trie.find_max(5) << endl;
}

void test2() {
    MonotonicQueue<int, greater<int>> mq;
    mq.push(0, 3);
    mq.push(1, 4);
    mq.push(2, 5);
    cout << mq.get_res().value() << endl;
    mq.pop(0);
    cout << mq.get_res().value() << endl;
    mq.push(3, 1);
    cout << mq.get_res().value() << endl;
    mq.pop(1);
    mq.pop(2);
    cout << mq.get_res().value() << endl;
}

int main() {
    //test();
    //test2();

    Solution sol;
    vector<int> nums = {0, 3};
    int k = 0;
    cout << sol.maxXor(nums, k) << endl;
}