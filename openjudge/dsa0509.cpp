#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

struct Node {
    char c;
    int left = -1, right = -1;
};
vector<Node> tree;

int getH(int u) {
    if (u == -1) return 0;
    return max(getH(tree[u].left), getH(tree[u].right)) + 1;
}

void draw(int u, int d, int x, int h, vector<string>& canvas) {
    canvas[2 * d][x] = tree[u].c;
    if (tree[u].left == -1) return;
    int offset = 1 << (h - d - 2);
    canvas[2 * d + 1][x - 1] = '/';
    draw(tree[u].left, d + 1, x - offset, h, canvas);
    canvas[2 * d + 1][x + 1] = '\\';
    draw(tree[u].right, d + 1, x + offset, h, canvas);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    unordered_map<char, int> level = {{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}};
    unordered_map<char, int> val = {};
    string expr; cin >> expr;
    vector<char> postfix;
    stack<char> opstack;
    int valnum; cin >> valnum;
    while (valnum--) {
        char c; int v; cin >> c >> v;
        val[c] = v;
    }
    for (char c : expr) {
        if (val.count(c)) {
            postfix.push_back(c);
        } else {
            if (c == '(') {
                opstack.push(c);
            } else if (c == ')') {
                while (!opstack.empty() && opstack.top() != '(') {
                    postfix.push_back(opstack.top());
                    opstack.pop();
                }
                opstack.pop();
            } else {
                while (!opstack.empty() && opstack.top() != '(' && level[opstack.top()] >= level[c]) {
                    postfix.push_back(opstack.top());
                    opstack.pop();
                }
                opstack.push(c);
            }
        }
    }
    while (!opstack.empty()) {
        postfix.push_back(opstack.top());
        opstack.pop();
    }
    for (char c : postfix) cout << c;
    cout << '\n';
    stack<int> stk;
    for (char c : postfix) {
        int u = tree.size();
        tree.push_back({c, -1, -1});
        if (!val.count(c)) {
            tree[u].right = stk.top(); stk.pop();
            tree[u].left = stk.top(); stk.pop();
        }
        stk.push(u);
    }
    int root = stk.top();
    int h = getH(root);
    int w = (1 << h) - 1;
    vector<string> canvas(2 * h - 1, string(w, ' '));
    draw(root, 0, (1 << (h - 1)) - 1, h, canvas);
    for (string& s : canvas) {
        while (!s.empty() && s.back() == ' ') s.pop_back();
        cout << s << '\n';
    }
    stack<int> valstk;
    for (char c : postfix) {
        if (val.count(c)) {
            valstk.push(val[c]);
        } else {
            int b = valstk.top(); valstk.pop();
            int a = valstk.top(); valstk.pop();
            if (c == '+') valstk.push(a + b);
            else if (c == '-') valstk.push(a - b);
            else if (c == '*') valstk.push(a * b);
            else if (c == '/') valstk.push(a / b);
        }
    }
    cout << valstk.top() << '\n';
    return 0;
}