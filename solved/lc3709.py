'''
simple dynamic segment tree problem
'''

class Node:
    def __init__(self):
        self.sum = 0
        self.l, self.r = None, None

class SegmentTree:
    def __init__(self):
        self.root: Node | None = None
        self.s, self.e = 1, int(1e9)

    def insert(self, s: int, e: int, i: int, val: int, curr: Node) -> Node:
        if curr == None:
            curr = Node()

        if s == e:
            curr.sum += val
            return curr
        
        m = (s + e) >> 1
        if i <= m:
            curr.l = self.insert(s, m, i, val, curr.l)
        else:
            curr.r = self.insert(m + 1, e, i, val, curr.r)
        curr.sum = (0 if curr.l is None else curr.l.sum) + (0 if curr.r is None else curr.r.sum)
        
        if s == self.s and e == self.e:
            self.root = curr
        
        return curr
    
    def range_query(self, s: int, e: int, l: int, r: int, curr: Node) -> int:
        if curr == None:
            return 0
        elif s == e or (s == l and e == r):
            return curr.sum
        
        m = (s + e) >> 1
        if r <= m:
            return self.range_query(s, m, l, r, curr.l)
        elif l > m:
            return self.range_query(m + 1, e, l, r, curr.r)
        else:
            return self.range_query(s, m, l, m, curr.l) + self.range_query(m + 1, e, m + 1, r, curr.r)

        

class ExamTracker:

    def __init__(self):
        self.st = SegmentTree()
        

    def record(self, time: int, score: int) -> None:
        self.st.insert(self.st.s, self.st.e, time, score, self.st.root)
        

    def totalScore(self, startTime: int, endTime: int) -> int:
        return self.st.range_query(self.st.s, self.st.e, startTime, endTime, self.st.root)
        

