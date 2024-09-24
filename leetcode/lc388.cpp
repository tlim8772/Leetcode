#include <bits/stdc++.h>
using namespace std;

// parse into directory tree, then do dfs

// forward declaration
struct Node;

struct Pair {
    Node *node;
    int lvl;

    Pair(Node* n, int lvl): node(n), lvl(lvl) {}
};


struct Node {
    string name;
    bool isFile;
    vector<Node*> children;

    inline static int ptr;

    Node(string str): name(str) {
        isFile = checkIsFile(str);
    }
    

    bool checkIsFile(string& str) {
        return accumulate(str.begin(), str.end(), false, [](bool b, char c) {return b || c == '.';});
    }

    // tokenise the input
    static vector<string> tokenizer(string& str) {
        int p1 = 0;
        vector<string> out;
        while (p1 < str.size()) {
            int p2 = p1;
            while (p2 < str.size() && str[p2] != '\n' && str[p2] != '\t') {
                p2 ++;
            }
            
            // str[p1] is '\n' or '\p'
            if (p2 == p1) {
                out.push_back(str.substr(p1, 1));
                p1 ++;
            } else {
                out.push_back(str.substr(p1, p2 - p1));
                p1 = p2;
            }
        }
        return out;
    }

    // ptr points to the name of a new folder we must create
    // after function ends, ptr points to the next folder of the same or lower level (i.e must create new folder)
    // lvl returns the level of the next folder, if lvl = -1 means that no new folder
    static Pair parse(vector<string>& tokens, int lvl) {
        Node* out = new Node(tokens[ptr]);

        int l = 0;
        ptr += 2;
        while (ptr < tokens.size() && tokens[ptr] == "\t") {
            ptr ++;
            l ++;
        }

        while (true) {
           if (l <= lvl) {
                return Pair(out, l);
            } else if (ptr >= tokens.size()) {
                return Pair(out, -1);
            } else {
                // this means ptr is now pointing to the next child
                Pair p = parse(tokens, lvl + 1);
                out->children.push_back(p.node);
                l = p.lvl;
                if (l <= lvl) return Pair(out, l);
            }
        }
    }
};


class Solution {
public:
    vector<Node*> nodes;
    
    int dfs1(Node *node) {
        int best = -1;
        for (int i = 0; i < node->children.size(); i ++) {
            int len = dfs1(node->children[i]);
            if (len > best) {
                best = len;
            }
        }

        if (best == -1) {
            return (node->isFile) ? node->name.size() : -999999999;
        } else {
            // +1 as we need to add /
            // since we start with -1, no problem if no files are added on
            return node->name.size() + 1 + best;
        }
        
    }

    int lengthLongestPath(string input) {
        vector<string>&& tokens = Node::tokenizer(input);
        Node::ptr = 0;
        while (Node::ptr < tokens.size()) {
            nodes.push_back(Node::parse(tokens, 0).node);
        }
        
        return accumulate(nodes.begin(), nodes.end(), 0, [&](int x, Node *node) {return max(x, dfs1(node));});
    }
};


















/*int main() {
    vector<string>&& test = Solution().tokenizer("dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext");
    for (string s : test) {
        if (s == "\n") {
            cout << "newline" << endl;
        } else if (s == "\t") {
            cout << "tab" << endl;
        } else {
            cout << s << endl;
        }
    }
}*/

int main() {
    string s = "file1.txt\nfile2.txt\nlongfile.txt";
    cout << Solution().lengthLongestPath(s) << endl;
    

 
}