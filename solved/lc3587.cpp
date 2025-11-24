#include <bits/stdc++.h>
using namespace std;

// use a doubly linked list
// e: even, o: odd
// suppose the final state is eoeoe
// and we have eeeoo
// the 1st index is wrong, we just have to find the earliest odd and shift it
// and this is optimal,simple to see why
// suppose you need to use 2nd odd, and 1st odd also shift left, the 1st odd can take the position 2nd odd goes to

// let cnode be the node we are taking away
// cnode only moves right
// so we iterate from left to right, if wrong parity, start from cnode, find the 1st correct node
// and switch

// using linked list mean we can remove nodes in O(1) and shift it to the right position
// and other nodes whose position is affected will be in the right position
struct Node {
    Node* prev = nullptr;
    Node* next = nullptr;
    int val;

    Node(int val): val(val) {}

    static Node* createList(const vector<int>& nums) {
        Node* start = new Node(nums[0]);
        Node* prev = start;

        for (int i = 1; i < nums.size(); i++) {
            Node* node = new Node(nums[i]);
            prev->next = node;
            node->prev = prev;
            prev = node;
        }

        return start;
    }

    ~Node() {
       delete next;
    }
};

class Solution {
public:
    int whichParity1st(const vector<int>& nums) {
        int e = 0, o = 0;
        for (int x : nums) {
            if (x % 2 == 0) {
                e++;
            } else {
                o++;
            }
        }

        if (abs(e - o) > 1) {
            return -1;
        } else if (e > o) {
            return 0;
        } else if (o > e) {
            return 1;
        } else {
            return 2;
        }
    } 

    int solve(const vector<int>& nums, int parity1st) {
        Node* lst = Node::createList(nums);
        
        Node* currNode = lst;
        
        int cidx = 0;
        Node* cnode = lst;

        int currPar = parity1st;

        int ans = 0;

        for (int i = 0; i < nums.size(); i++) {
            if (currNode->val % 2 == currPar) {
                currNode = currNode->next;
            } else {
               
                if (cidx <= i) {
                    cidx = i + 1;
                    cnode = currNode->next;
                }

                while (cnode != nullptr) {
                    if (cnode->val % 2 == currPar) {
                        Node* prev = cnode->prev;
                        Node* next = cnode->next;
                        
                        prev->next = next;
                        if (next != nullptr) {
                            next->prev = prev;
                        }
                        
                        ans += cidx - i;
                        
                        Node* prev2 = currNode->prev;
                        cnode->prev = prev2;
                        cnode->next = currNode;
                        if (prev2 != nullptr) {
                            prev2->next = cnode;
                        }

                        cidx++;
                        cnode = next;
                        
                        break;
                    } else {
                        cidx++;
                        cnode = cnode->next;
                    }
                }
            }

            currPar = !currPar;
        }

        // freeing memory means more time needed
        // delete lst;
        return ans;
    }

    int minSwaps(vector<int>& nums) {
        int parity1st = whichParity1st(nums);
        if (parity1st == -1) return -1;
        
        if (parity1st == 0) {
            return solve(nums, 0);
        } else if (parity1st == 1) {
            return solve(nums, 1);
        } else {
            int odd1st = solve(nums, 1);
            int even1st = solve(nums, 0);
            return min(odd1st, even1st);
        }
    }
};

int main() {
    Solution sol;

    vector<int> nums = {0,0,0,1,1,1,1,0};
    cout << sol.minSwaps(nums) << endl;
}

