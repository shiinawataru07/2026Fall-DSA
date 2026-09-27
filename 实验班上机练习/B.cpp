#include<iostream>
#include<string>
#include<vector>
using namespace std;

int ls, lt;
int pi[500001];
string s, t;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> ls >> lt;
    cin >> s >> t;
    for(int i = 1; i < lt; i++) {
        int j = pi[i - 1];
        while(j > 0 && t[i] != t[j]) j = pi[j - 1];
        if(t[i] == t[j]) j++;
        pi[i] = j;
    }
    int j = 0;
    vector<int> ans;
    for(int i = 0; i < ls + lt - 1; i++) {
        char ch = s[i % ls];
        while(j > 0 && ch != t[j]) j = pi[j - 1];
        if (ch == t[j]) j++;
        if (j == lt) {
            if (i - lt + 1 < ls) ans.push_back(i - lt + 2);
            j = pi[j - 1];
        }
    }
    cout << ans.size() << "\n";
    if (!ans.empty()) {
        for(int i = 0; i < ans.size(); i++) {
            cout << ans[i] << (i == ans.size() - 1 ? "\n" : " ");
        }
    }
    return 0;
}