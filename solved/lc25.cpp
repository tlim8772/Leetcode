#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* makeIntList(int i, int lim) {
    if (i == lim) return nullptr;
    return new ListNode(i, makeIntList(i + 1, lim));
}

void printList(ListNode* node) {
    if (node == nullptr) {
        cout << endl;
        return;
    }
    cout <<  node->val << " ";
    printList(node->next);
}

class Solution {
public:
    static pair<ListNode*, ListNode*> reverse(ListNode* head) {
        ListNode* end = head;
        ListNode* start = nullptr;
        while (head != nullptr) {
            ListNode* curr = head;
            head = head->next;

            curr->next = start;
            start = curr;
        }
        return {start, end};
    }

    int len(ListNode* node) {
        return (node == nullptr) ? 0 : 1 + len(node->next);
    }


    ListNode* reverseKGroup(ListNode* head, int k) {
        int l = len(head); // bad, results in O(n^2) time complexity
        if (l < k) return head;

        ListNode* next = nullptr;
        ListNode* cut = head;
        for (int i = 0; i < k; i++) {
            if (i == k - 1) {
                next = reverseKGroup(cut->next, k);
                cut->next = nullptr;
            } else {
                cut = cut->next;
            }
        }
        
        auto [start, end] = reverse(head);
        end->next = next;
        return start;
        
    }
};

int main() {
    ListNode* ints = makeIntList(0, 10);
    printList(ints);

    //auto [s, e] = Solution::reverse(ints);
    Solution sol;
    printList(sol.reverseKGroup(ints, 3));
}