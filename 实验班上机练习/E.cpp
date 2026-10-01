#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<int> b(n + 1);
    for (int v = 1; v <= n; ++v) {
        long long a; cin >> a;
        b[v] = static_cast<int>(a & 1);
    }
    const int m = n - 1;
    vector<int> us(m), vs(m), deg(n + 2, 0), start(n + 2, 0);
    for (int e = 0; e < m; ++e) {
        cin >> us[e] >> vs[e];
        ++deg[us[e]]; ++deg[vs[e]];
    }
    for (int v = 1; v <= n; ++v) start[v + 1] = start[v] + deg[v];
    vector<int> fill_(start), adj(2 * m);
    for (int e = 0; e < m; ++e) {
        adj[fill_[us[e]]++] = vs[e];
        adj[fill_[vs[e]]++] = us[e];
    }
    vector<int> cnt(n + 1, 0);
    for (int u = 1; u <= n; ++u) {
        if (b[u]) continue;
        int c = 0;
        for (int t = start[u]; t < start[u + 1]; ++t) c += b[adj[t]];
        if (c == 0) { cout << "NO\n"; return 0; }
        cnt[u] = c;
    }
    vector<int> pending(n + 1, 0), parent(n + 1, 0), sz(n + 1, 0), comp, stk;
    vector<char> visited(n + 1, 0);
    for (int root = 1; root <= n; ++root) {
        if (!b[root] || visited[root]) continue;
        comp.clear();
        visited[root] = 1; parent[root] = 0;
        stk.assign(1, root);
        while (!stk.empty()) {
            int v = stk.back(); stk.pop_back();
            comp.push_back(v);
            for (int t = start[v]; t < start[v + 1]; ++t) {
                int w = adj[t];
                if (b[w] && !visited[w]) { visited[w] = 1; parent[w] = v; stk.push_back(w); }
            }
        }
        if (comp.size() % 2 == 0) { cout << "NO\n"; return 0; }
        for (int v : comp) sz[v] = 1;
        for (size_t idx = comp.size(); idx-- > 0; ) {
            int v = comp[idx], p = parent[v];
            if (p) sz[p] += sz[v];
        }
        for (int v : comp) {
            int p = parent[v];
            if (!p) continue;
            if (sz[v] & 1) ++pending[v];
            else           ++pending[p];
        }
    }
    vector<int> block(n + 1, 0), ptr(start);
    vector<char> deleted(n + 1, 0);
    auto uniqueLiveOdd = [&](int u) -> int {
        int i = ptr[u], end = start[u + 1];
        while (i < end) {
            int w = adj[i];
            if (b[w] && !deleted[w]) { ptr[u] = i; return w; }
            ++i;
        }
        ptr[u] = i;
        return 0;
    };
    for (int u = 1; u <= n; ++u) {
        if (!b[u] && cnt[u] == 1) ++block[uniqueLiveOdd(u)];
    }
    auto avail = [&](int v) -> bool {
        if (deleted[v]) return false;
        if (!b[v]) return (cnt[v] & 1) != 0;
        return pending[v] == 0 && block[v] == 0;
    };
    priority_queue<int, vector<int>, greater<int>> heap;
    for (int v = 1; v <= n; ++v) if (avail(v)) heap.push(v);
    vector<int> res;
    res.reserve(n);
    while (!heap.empty()) {
        int v = heap.top(); heap.pop();
        if (!avail(v)) continue;
        deleted[v] = 1;
        res.push_back(v);
        if (!b[v]) {
            if (cnt[v] == 1) {
                int z = uniqueLiveOdd(v);
                if (z) { --block[z]; if (avail(z)) heap.push(z); }
            }
        } else {
            for (int t = start[v]; t < start[v + 1]; ++t) {
                int w = adj[t];
                if (deleted[w]) continue;
                if (b[w]) {
                    --pending[w];
                    if (avail(w)) heap.push(w);
                } else {
                    --cnt[w];
                    if (cnt[w] == 1) {
                        int z = uniqueLiveOdd(w);
                        if (z) ++block[z];
                    }
                    if (avail(w)) heap.push(w);
                }
            }
        }
    }
    if (static_cast<int>(res.size()) == n) {
        cout << "YES\n";
        for (int i = 0; i < n; ++i) cout << res[i] << " \n"[i + 1 == n];
    } else {
        cout << "NO\n";
    }
    return 0;
}