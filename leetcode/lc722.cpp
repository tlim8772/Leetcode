#include <vector>
#include <iostream>
#include <string>
using namespace std;


template <typename T>
void print(vector<T> arr) {
    for (T t: arr) {
        cout << t << " ";
    }
    cout << endl;
}

class Solution {
public:
    vector<string> output;

    bool isBlockStart(string& s, int index) {
        return (index < s.size() - 1 && s.substr(index, 2) == "/*"); 
    }

    bool isBlockEnd(string& s, int index) {
        return (index < s.size() - 1 && s.substr(index, 2) == "*/");
    }

    bool isLineStart(string& s, int index) {
        return (index < s.size() - 1 && s.substr(index, 2) == "//");
    }


    void notInBlock(vector<string>& src, string& store, int ptr, int idx) {
        if (ptr == src.size()) return;
        else if (idx >= src[ptr].size()) {
            if (store != "") output.push_back(store);
            store.clear();
            notInBlock(src, store, ptr + 1, 0);
        } else if (isLineStart(src[ptr], idx)) {
            if (store != "") output.push_back(store);
            store.clear();
            notInBlock(src, store, ptr + 1, 0);
        } else if (isBlockStart(src[ptr], idx)) {
            inBlock(src, store, ptr, idx + 2);
        } else {
            store.append(1, src[ptr][idx]);
            notInBlock(src, store, ptr, idx + 1);
        }
    }
    
    // when this function is called, idx, is already in block
    // i.e when notInBlock encounter "/*"
    // idx is moved forward by 2
    // this will prevent problems from "/*/"
    void inBlock(vector<string>& src, string& store, int ptr, int idx) {
        if (ptr == src.size()) return;
        else if (idx >= src[ptr].size()) {
            inBlock(src, store, ptr + 1, 0);
        }
        else if (isBlockEnd(src[ptr], idx)) {
            notInBlock(src, store, ptr, idx + 2);
        } else {
            inBlock(src, store, ptr, idx + 1);
        }
    }

    vector<string> removeComments(vector<string>& source) {
        string store;
        if (isBlockStart(source[0], 0)) {
            // to maintain invariant, thats why we start at 2
            inBlock(source, store, 0, 2);
        } else {
            notInBlock(source, store, 0, 0);
        }
        return output;
    }

};

int main() {
    Solution sol;
    vector<string> source = {"a/*comment", "line", "more_comment*/b"};
    vector<string> src1 = {"/*Test program */", "int main()", "{ ", "  // variable declaration ", "int a, b, c;", "/* This is a test", "   multiline  ", "   comment for ", "   testing */", "a = b + c;", "}"};
    vector<string> src2 = {"a//*b/*/c","blank","d/*/e/*/f"};
    print(sol.removeComments(src1));
}