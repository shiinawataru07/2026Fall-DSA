
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v, w;
};

int parent[26];

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

int main() {
    int n;
    while (cin >> n && n != 0) {
        vector<Edge> edges;

        for (int i = 0; i < n; i++)
            parent[i] = i;

        for (int i = 0; i < n - 1; i++) {
            char u, v;
            int k, w;
            cin >> u >> k;

            while (k--) {
                cin >> v >> w;
                edges.push_back({u - 'A', v - 'A', w});
            }
        }

        sort(edges.begin(), edges.end(),
             [](const Edge& a, const Edge& b) {
                 return a.w < b.w;
             });

        int ans = 0, cnt = 0;

        for (auto [u, v, w] : edges) {
            int pu = find(u);
            int pv = find(v);

            if (pu != pv) {
                parent[pu] = pv;
                ans += w;
                cnt++;

                if (cnt == n - 1)
                    break;
            }
        }

        cout << ans << '\n';
    }

    return 0;
}
