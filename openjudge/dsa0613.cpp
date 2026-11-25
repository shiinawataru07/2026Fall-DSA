#include<iostream>
#include<vector>
#include<string>
using namespace std;

struct Node{
    vector<Node*> children;
};

struct BiNode {
    BiNode* left = nullptr;
    BiNode* right = nullptr;
};

void build(Node* root, BiNode* Biroot) {
    int childCount = root->children.size();
    if (!childCount) return;
    BiNode* cur = new BiNode();
    Biroot->left = cur;
    build(root->children[0], cur);
    for (int i = 1; i < childCount; ++i, cur = cur->right) {
        BiNode* newNode = new BiNode();
        cur->right = newNode;
        build(root->children[i], newNode);
    }
}

int h(BiNode* root) {
    if (!root) return 0;
    return 1 + max(h(root->left), h(root->right));
}

void clearTree(Node* root) {
    for (Node* child : root->children)
        clearTree(child);
    delete root;
}

void clearTree(BiNode* root) {
    if (!root) return;
    clearTree(root->left);
    clearTree(root->right);
    delete root;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    int caseNum = 1;
    while (cin >> line && line != "#") {
        Node* root = new Node();
        vector<Node*> stk;
        stk.push_back(root);
        int h1 = 0;
        for (char ch : line) {
            if (ch == 'd') {
                Node* newNode = new Node();
                stk.back()->children.push_back(newNode);
                stk.push_back(newNode);
                if (h1 < stk.size() - 1) h1 = stk.size() - 1;
            } else if (ch == 'u') {
                stk.pop_back();
            }
        }
        BiNode* Biroot = new BiNode();
        build(root, Biroot);
        int h2 = h(Biroot) - 1;
        cout << "Tree " << caseNum++ << ": " << h1 << " => " << h2 << "\n";
        clearTree(root);
        clearTree(Biroot);
    }
}