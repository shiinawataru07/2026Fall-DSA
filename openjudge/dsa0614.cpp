#include<iostream>
#include<vector>
#include<numeric>
using namespace std;

vector<int> dsu;

int find(int a) {
    if (dsu[a] != a) dsu[a] = find(dsu[a]);
    return dsu[a];
}

bool unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return false;
    dsu[a] = b;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, caseNum = 1;
    while (cin >> n >> m && (n || m)) {
        dsu.resize(n + 1);
        for (int i = 1; i <= n; ++i) dsu[i] = i;
        int ans = n;
        while (m--) {
            int a, b;
            cin >> a >> b;
            if (unite(a, b)) --ans;
        }
        cout << "Case " << caseNum++ << ": " << ans << "\n";
    }
}