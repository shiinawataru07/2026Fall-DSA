#include<iostream>
#include<vector>
#include<numeric>
using namespace std;

vector<int> dsu;

int find(int a) {
    if (dsu[a] != a) dsu[a] = find(dsu[a]);
    return dsu[a];
}

void dsuunion(int a, int b) {
    a = find(a);
    b = find(b);
    if (a != b) dsu[a] = b;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while (t--) {
        int n, m; cin >> n >> m;
        dsu.resize(2 * n + 1);
        iota(dsu.begin(), dsu.end(), 0);
        while (m--) {
            char query; cin >> query;
            int a, b; cin >> a >> b;
            if (query == 'D') {
                dsuunion(a, b + n);
                dsuunion(b, a + n);
            } else {
                if (find(a) == find(b)) cout << "In the same gang.\n";
                else if (find(a) == find(b + n)) cout << "In different gangs.\n";
                else cout << "Not sure yet.\n";
            }
        }
    }
}