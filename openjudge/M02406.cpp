#include<iostream>
#include<string>
#include<vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    while (cin >> s) {
        if (s == ".") break;
        int n = s.length();
        vector<int> pi(n, 0);
        for (int i = 1; i < n; ++i) {
            int j = pi[i - 1];
            while (j > 0 && s[i] != s[j]) j = pi[j - 1];
            if (s[i] == s[j]) ++j;
            pi[i] = j;
        }
        int t = n - pi[n - 1];
        if (n % t == 0) {
            cout << n / t << "\n";
        } else {
            cout << 1 << "\n";
        }
    }
    return 0;
}