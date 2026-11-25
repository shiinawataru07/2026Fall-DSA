#include <iostream>
#include <string>
#include <stack>
using namespace std;

struct Node {
    char val;
    Node* left = nullptr;
    Node* right = nullptr;
    Node(char v) : val(v) {}
};

Node* build (const string& str, int& pos) {
    if (str[pos] == '*') {
        pos++;
        return nullptr;
    }
    Node* root = new Node(str[pos++]);
    if (pos < str.size() && str[pos] == '(') {
        root->left = build(str, ++pos);
        if (str[pos] == ',') root->right = build(str, ++pos);
        pos++;
    }
    return root;
}

void preorder(Node* root) {
    if (!root) return;
    cout << root->val;
    preorder(root->left);
    preorder(root->right);
}

void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->val;
    inorder(root->right);
}

void destroy(Node* root) {
    if (!root) return;
    destroy(root->left);
    destroy(root->right);
    delete root;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    while (n--) {
        string str; cin >> str;
        int pos = 0;
        Node* root = build(str, pos);
        preorder(root); cout << endl;
        inorder(root); cout << endl;
        destroy(root);
    }
}