#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* makeInts(int i, int lim) {
    if (i == lim) return nullptr;
    return new ListNode(i, makeInts(i + 1, lim));
}

void printList(ListNode* node) {
    if (node == nullptr) {
        cout << endl;
        return;
    }
    cout << node->val << " ";
    printList(node->next);
}

pair<ListNode*, ListNode*> reverse(ListNode* node) {
    ListNode* start = nullptr, *end = node;
    while (node != nullptr) {
        ListNode* temp = node;
        node = node->next;
        temp->next = start;
        start = temp;
    }
    return {start, end};
}

int len(ListNode* node) {
    return (node == nullptr) ? 0 : 1 + len(node->next);
}

bool isLeqLen(ListNode* node, int l) {
    if (node == nullptr) {
        return l >= 0;
    } else if (l == 0) {
        return false;
    } else {
        return isLeqLen(node->next, l - 1);
    }

}

 
class Solution {
public:
    ListNode* helper(ListNode* head, int glen) {
        if (isLeqLen(head, glen)) {
            int l = len(head);
            if (l % 2 == 0) {
                auto [s, e] = reverse(head);
                return s;
            } else {
                return head;
            }
        }

        ListNode* cut = head, *next = nullptr;
        for (int i = 0; i < glen - 1; i++) cut = cut->next;

        next = helper(cut->next, glen + 1);
        cut->next =  nullptr;

        if (glen % 2 == 0) {
            auto [s, e] = reverse(head);
            e->next = next;
            return s;
        } else {
            cut->next = next;
            return head;
        }

        
    }
    
    ListNode* reverseEvenLengthGroups(ListNode* head) {
        return helper(head, 1);
    }
};

int main() {
    ListNode* ints = makeInts(0, 6);
    Solution sol;
    printList(sol.reverseEvenLengthGroups(ints));
}