#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;

struct Node {
    int left, right;
    char val;
    bool tag = false;
};
vector<Node> tree;

void preorder(int u) {
    if (u == -1) return;
    cout << tree[u].val;
    preorder(tree[u].left);
    preorder(tree[u].right);
}

void postorder(int u) {
    if (u == -1) return;
    postorder(tree[u].left);
    postorder(tree[u].right);
    cout << tree[u].val;
}

void inorder(int u) {
    if (u == -1) return;
    inorder(tree[u].left);
    cout << tree[u].val;
    inorder(tree[u].right);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int treeNum; cin >> treeNum;
    while (treeNum--) {
        string str;
        stack<int> s;
        tree.clear();
        while (cin >> str && str != "0") {
            int depth = str.length() - 1;
            char c = str[depth];
            while (s.size() > depth) s.pop();
            if (c == '*') {
                tree[s.top()].tag = true;
                continue;
            }
            int u = tree.size();
            tree.push_back({-1, -1, c});
            if (!s.empty()) {
                int p = s.top();
                if (tree[p].tag) tree[p].right = u;
                else tree[p].left = u;
                tree[p].tag = true;
            }
            s.push(u);
        }
        preorder(0); cout << endl;
        postorder(0); cout << endl;
        inorder(0); cout << endl;
        if (treeNum) cout << endl;
    }
    return 0;
}