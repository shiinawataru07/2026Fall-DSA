#include<iostream>
#include<vector>
#include<stack>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<int> prices(n);
    for (int i = 0; i < n; ++i) cin >> prices[i];
    vector<int> best(n);
    stack<int> s;
    int ans = 0;
    for(int i = n - 1; i >= 0; --i) {
        int pos = i;
        while(!s.empty() && prices[s.top()] > prices[i]) {
            int k = s.top(); s.pop();
            if (prices[best[k]] > prices[pos]) pos = best[k];
        }
        best[i] = pos;
        if (pos > i) ans = max(ans, pos- i + 1);
        s.push(i);
    }
    cout << ans << "\n";
    return 0;
}