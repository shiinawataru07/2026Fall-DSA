#include<iostream>
#include<string>
#include<vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    string s;
    int casenum = 1;
    while (cin >> n) {
        if (n == 0) break;
        cin >> s;
        vector<int> pi(n, 0);
        for (int i = 1; i < n; ++i) {
            int j = pi[i - 1];
            while (j > 0 && s[i] != s[j]) j = pi[j - 1];
            if (s[i] == s[j]) ++j;
            pi[i] = j;
        }
        cout << "Test case #" << casenum++ << "\n";
        for (int i = 1; i < n; ++i) {
            int period = i + 1 - pi[i];
            if (period < i + 1 && (i + 1) % period == 0) {
                cout << i + 1 << " " << (i + 1) / period << "\n";
            }
        }
        cout << "\n";
    }
    return 0;
}