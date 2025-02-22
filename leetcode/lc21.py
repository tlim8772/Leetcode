from typing import Optional

class ListNode:
    def __init__(self, val=0, next=None):         
        self.val = val
        self.next = next
    
    
    def to_string(self):
        s = str(self.val)
        if self.next is None:
            return s
        s += ' ' + self.next.to_string()
        return s


class Solution:
    def mergeTwoLists(self, list1: Optional[ListNode], list2: Optional[ListNode]) -> Optional[ListNode]:
        if list1 is None:
            return list2
        elif list2 is None:
            return list1
        elif list1.val < list2.val:
            node = ListNode(list1.val)
            node.next = self.mergeTwoLists(list1.next, list2)
            return node
        else:
            node = ListNode(list2.val)
            node.next = self.mergeTwoLists(list1, list2.next)
            return node
        
def f(n):
    node = None
    for i in range(n, 0, -1):
        if i % 2 == 1:
            node2 = ListNode(i)
            node2.next = node
            node = node2
    return node

print(f(10).to_string())





