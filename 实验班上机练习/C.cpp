#include<iostream>
#include<vector>
#include<queue>

using ll = long long;
using namespace std;
const ll INF = 1LL << 62;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, k;
    cin >> n >> m >> k;
    const int N = n + k;
    vector<ll> a(N + 1, 0);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    vector<int> head(N + 1, -1), nxt, to;
    vector<ll> wt;
    auto addEdge = [&](int u, int v, ll w) {
        to.push_back(v);
        wt.push_back(w);
        nxt.push_back(head[u]);
        head[u] = static_cast<int>(to.size()) - 1;
    };
    for(int i = 0; i < m; ++i) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        addEdge(u, v, w);
        addEdge(v, u, w);
    }
    for(int g = 1; g <= k; ++g) {
        int sz;
        cin >> sz;
        int gid = n + g;
        for(int i = 0; i < sz; ++i) {
            int x;
            cin >> x;
            addEdge(gid, x, 0);
            addEdge(x, gid, 0);
        }
    }
    vector<ll> dist(static_cast<size_t>(N + 1) * 4, INF);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    const ll a1 = a[1];
    const pair<ll, int> starts[4] = {{a1, 0}, {0, 2}, {2 * a1, 1}, {a1, 3}};
    for(const auto& st : starts) {
        int s0 = 1 * 4 + st.second;
        if (st.first < dist[s0]) {
            dist[s0] = st.first;
            pq.push({st.first, s0});
        }
    }
    const int target = n * 4 + 3;
    while(!pq.empty()) {
        auto [d, st] = pq.top();
        pq.pop();
        if(d > dist[st]) continue;
        if(st == target) break;
        int u = st >> 2;
        int flag = st & 3;
        int i = flag >> 1;
        int j = flag & 1;
        for(int e = head[u]; e != -1; e = nxt[e]) {
            int y = to[e];
            ll w = wt[e];
            if (y > n) {
                int ns = y * 4 + flag;
                ll nd = d + w;
                if (nd < dist[ns]) {
                    dist[ns] = nd;
                    pq.push({nd, ns});
                }
            } else {
                ll ay = a[y];
                for(int di = 0; di < 2 - i; ++di) {
                    for(int dj = 0; dj < 2 - j; ++dj) {
                        ll nd = d + w + (1 - di + dj) * ay;
                        int ns = y * 4 + ((i + di) * 2 + (j + dj));
                        if (nd < dist[ns]) {
                            dist[ns] = nd;
                            pq.push({nd, ns});
                        }
                    }
                }
            }
        }
    }
    cout << dist[target] << "\n";
    return 0;
}